
# vs_gen v0.10

# Log file based summary generator for Vintage Story
# Copyright Anmon 2025 All Rights Reserved

#!/usr/bin/env python3
import argparse
import glob
import os
import re
import json
import logging
from datetime import datetime, timedelta
from collections import Counter, defaultdict
from dataclasses import dataclass, field
from typing import List, Set, Dict, Optional, Tuple

logging.basicConfig(
    level=logging.INFO,
    format="%(asctime)s [%(levelname)s] %(message)s"
)
logger = logging.getLogger(__name__)

# Date formats
DATE_FORMAT = "%d.%m.%Y %H:%M:%S"
TIMEONLY_FORMAT = "%H:%M:%S"

# Default mappings and thresholds
DEFAULT_CUSTOM_MESSAGE_MAP: Dict[str, str] = {
    "fell from a high place": "falling",
    "burned to death": "burning to death",
    "drowned": "drowning",
    "got bitten to death": "getting bitten to death",
    "thought he could fly": "falling",
    "suffered a grizzly death": "bear rape",
    "got pancaked": "falling rocks",
    "got horned to death": "horned animal",
    "got rammed to death": "getting rammed to death",
    "got trampled by a bighorn sheep": "sheep",
    "messed around with a boar": "boar",
    "was torn limb from limb": "getting torn apart",
    "was bitten to death": "getting bitten to death",
    "had a too close encounter with a wolf": "getting mauled by wolves",
    "was wolf bait": "being eaten by wolves",
    "unwisely poked a bear": "bear",
    "forgot to eat": "being poor"
}
DEFAULT_CUSTOM_ENEMY_MAP: Dict[str, str] = {
    "game:drifter-normal": "normal drifter",
    "game:drifter-corrupt": "corrupted drifter",
    "game:drifter-deep": "deep drifter",
    "game:drifter-tainted": "tainted drifter",
    "game:shiver-surface": "surface shiver",
    "game:pig-wild-male": "wild boar",
    "game:pig-wild-female": "wild sow",
    "game:wolf-male": "male wolf",
    "game:wolf-female": "female wolf",
    "game:fox-male-red": "red fox",
    "game:bowtorn-surface": "surface bowtorn",
    "game:bowtorn-deep": "deep bowtorn",
    "game:chicken-roosterpoult": "young rooster",
    "game:bear-male-black": "male bear",
    "game:bear-female-black": "female bear",
    "game:salmon": "salmon",
    "game:chicken-henpoult": "chicken",
    "game:chicken-hen": "chicken",
    "game:chicken-rooster": "rooster",
    "game:deer-water-female-adult": "female deer",
    "game:deer-water-male-adult": "male deer",
    "game:deer-moose-male-adult": "male moose",
    "game:deer-moose-female-adult": "female moose",
    "game:raccoon-male": "male coon",
    "game:raccoon-female": "female coon",
    "game:hare-female-gold": "female gold hare",
    "game:hare-male-gold": "male gold hare",
    "game:hare-female-ashgrey": "female grey hare",
    "game:hare-male-ashgrey": "male grey hare",
    "game:fox-female-red": "female fox",
    "game:fox-male-red": "male fox",
    "primitivesurvival:landcrab": "crab"
}
DEFAULT_METALS: List[str] = [
    "copper", "bismuth", "bronze", "gold", "lead", "silver",
    "cassiterite", "sphalerite", "zinc"
]
DEFAULT_LARGE_METAL_THRESHOLD: int = 100

# Default narrative templates
DEFAULT_OUTPUT_TEMPLATES: Dict[str, str] = {
    "player_story": "**{player}** {phrases}.",
    "single_death": "died to {causes}",
    "double_death": "got killed by {causes}",
    "multiple_deaths": "was undone **{count}** times by {causes}",
    "single_kill": "only got a single kill, namely {kills}",
    "double_kill": "managed two whole kills - {kills} ...please clap",
    "multiple_kills": "murdered **{count}** enemies, notably {kills}",
    "unscathed": "remained unscathed.",
    "storm_occurred": (
        "A **shitstorm** occurred, beginning at **{start}** and lasted "
        "for **{duration}** minutes."
    ),
    "storm_start": "[**WARNING**] A **shitstorm** is imminent [**WARNING**]",
    "storm_soon": (
        "A **shitstorm** is approaching, expected to start at **{start}**."
    ),
    "storm_ending": "A **shitstorm** is ending at **{end}**.",
    "no_events": "Nothing ever happens\n<:chudover:1352366576317501461>",
    "chunk_summary": "**{count}** new map chunk(s) were added."
}

# Precompiled regular expressions
RE_TIMESTAMP: re.Pattern = re.compile(r"^(\d{1,2}\.\d{1,2}\.\d{4} \d{2}:\d{2}:\d{2})")
RE_EVENT_TYPE: re.Pattern = re.compile(r"\[(.*?)\]")
RE_QUANTITY: re.Pattern = re.compile(r"(\d+)x")
RE_DEATH_PREFIX: re.Pattern = re.compile(r"^(got killed by|died)\s+", re.I)

# Regex for offthread map chunks events (only messages like "Offthread save of ... map chunks done")
OFFTHREAD_MAP_CHUNK_REGEX: re.Pattern = re.compile(r"^offthread save of (\d+)\s+map\s+chunks done", re.I)


def compile_player_prefix(player: str) -> re.Pattern:
    return re.compile(r"^player\s+" + re.escape(player) + r"[\s:,-]+", re.I)


def apply_custom_mapping(text: str, mapping: Dict[str, str]) -> str:
    for key, replacement in mapping.items():
        text = text.replace(key, replacement)
    return text


def grammatical_join(items: List[str]) -> str:
    if not items:
        return ""
    if len(items) == 1:
        return items[0]
    if len(items) == 2:
        return f"{items[0]} and {items[1]}"
    return ", ".join(items[:-1]) + ", and " + items[-1]


def clean_death_message(message: str, player: str, custom_mapping: Dict[str, str]) -> str:
    player_prefix = compile_player_prefix(player)
    message = player_prefix.sub("", message).strip()
    message = RE_DEATH_PREFIX.sub("", message).strip()
    message = message.rstrip(".").strip()
    message = apply_custom_mapping(message, custom_mapping)
    return message if message and message.lower() != "died" else "unknown causes"


def parse_timestamp(timestamp_str: str) -> Optional[datetime]:
    try:
        return datetime.strptime(timestamp_str, DATE_FORMAT)
    except Exception as e:
        logger.error(f"Timestamp parsing error for '{timestamp_str}': {e}")
        return None


def parse_time_range(time_str: str) -> Optional[timedelta]:
    match = re.match(r"(\d+)([mhd])$", time_str.strip().lower())
    if match:
        value = int(match.group(1))
        unit = match.group(2)
        if unit == "m":
            return timedelta(minutes=value)
        elif unit == "h":
            return timedelta(hours=value)
        elif unit == "d":
            return timedelta(days=value)
    return None


@dataclass
class LogEvent:
    timestamp: datetime
    event_type: str
    message: str

    @staticmethod
    def from_line(line: str) -> Optional["LogEvent"]:
        timestamp_match = RE_TIMESTAMP.match(line)
        if not timestamp_match:
            return None
        timestamp = parse_timestamp(timestamp_match.group(1))
        if not timestamp:
            return None
        event_type_match = RE_EVENT_TYPE.search(line)
        event_type = event_type_match.group(1).strip() if event_type_match else ""
        end_index = line.find("]")
        message = line[end_index + 1 :].strip() if end_index != -1 else ""
        return LogEvent(timestamp, event_type, message)


def is_interesting_audit_event(text: str) -> bool:
    lower_text = text.lower()
    return (
        "died" in lower_text
        or "death message" in lower_text
        or "killed" in lower_text
        or ("fire" in lower_text and "spread" in lower_text)
    )


def extract_player_name(text: str) -> Optional[str]:
    tokens = text.split()
    if not tokens:
        return None
    first = tokens[0].strip(":").lower()
    return tokens[1] if first in ("player", "client") and len(tokens) > 1 else tokens[0]


@dataclass
class PlayerData:
    death_details: List[str] = field(default_factory=list)
    kills: List[str] = field(default_factory=list)
    large_metals: Set[str] = field(default_factory=set)


class EventAggregator:
    def __init__(self,
                 custom_message_map: Dict[str, str],
                 custom_enemy_map: Dict[str, str],
                 metals: List[str],
                 large_metal_threshold: int):
        self.custom_message_map = custom_message_map
        self.custom_enemy_map = custom_enemy_map
        self.metals = metals
        self.large_metal_threshold = large_metal_threshold
        self.players: Dict[str, PlayerData] = defaultdict(PlayerData)
        self.storm_events: List[LogEvent] = []
        # Track the latest cumulative map chunks and the timestamp of that event.
        self.chunk_count: int = 0
        self.last_map_chunk_timestamp: Optional[datetime] = None

    def process_event(self, event: LogEvent) -> None:
        lower_message = event.message.lower()
        if event.event_type == "Audit":
            if is_interesting_audit_event(event.message) or (
                any(metal in lower_message for metal in self.metals)
                and any(word in lower_message for word in ["moved", "took", "put"])
            ):
                self._process_audit_event(event, lower_message)
        elif event.event_type == "Notification" and "temporal storm" in lower_message:
            self.storm_events.append(event)
        # Process only offthread map chunk save events.
        if event.event_type == "Event":
            match = OFFTHREAD_MAP_CHUNK_REGEX.search(lower_message)
            if match:
                try:
                    count = int(match.group(1))
                    # Update only if this event is more recent than the last recorded.
                    if self.last_map_chunk_timestamp is None or event.timestamp > self.last_map_chunk_timestamp:
                        self.last_map_chunk_timestamp = event.timestamp
                        self.chunk_count = count
                except ValueError as e:
                    logger.error("Error parsing chunk count from message '%s': %s", event.message, e)

    def _process_audit_event(self, event: LogEvent, lower_message: str) -> None:
        player = extract_player_name(event.message)
        if not player or player.lower() == "player":
            return
        player_lower = player.lower()
        if "died" in lower_message or "death message" in lower_message:
            death_match = re.search(r"death message:\s*(.*)", event.message, re.I)
            cause_text = death_match.group(1).strip() if death_match else event.message
            cause_clean = clean_death_message(cause_text, player, self.custom_message_map)
            self.players[player_lower].death_details.append(cause_clean)
        if "killed" in lower_message:
            kill_match = re.search(r"killed\s+(?!by)(?:a\s+|an\s+)?([\w:.-]+)", event.message, re.I)
            if kill_match:
                enemy = kill_match.group(1)
                enemy_mapped = self.custom_enemy_map.get(enemy, enemy)
                enemy_mapped = apply_custom_mapping(enemy_mapped, self.custom_message_map)
                self.players[player_lower].kills.append(enemy_mapped)
        if any(word in lower_message for word in ["moved", "took", "put"]):
            for metal in self.metals:
                if metal in lower_message:
                    quantities = RE_QUANTITY.findall(event.message)
                    if quantities and max(int(q) for q in quantities) >= self.large_metal_threshold:
                        self.players[player_lower].large_metals.add(metal)

    def aggregate_storm_times(self) -> Tuple[Optional[datetime], Optional[datetime], Optional[datetime]]:
        storm_soon: Optional[datetime] = None
        storm_start: Optional[datetime] = None
        storm_waning: Optional[datetime] = None
        for event in self.storm_events:
            lower_msg = event.message.lower()
            if "temporal storm is approaching" in lower_msg:
                if storm_soon is None or event.timestamp < storm_soon:
                    storm_soon = event.timestamp
            if "temporal storm is imminent" in lower_msg:
                if storm_start is None or event.timestamp < storm_start:
                    storm_start = event.timestamp
            if "temporal storm seems to be waning" in lower_msg:
                if storm_waning is None or event.timestamp > storm_waning:
                    storm_waning = event.timestamp
        return storm_soon, storm_start, storm_waning

    def get_complete_storms(self) -> List[Tuple[datetime, datetime]]:
        storms = []
        current_storm_start = None
        sorted_events = sorted(self.storm_events, key=lambda e: e.timestamp)
        for event in sorted_events:
            msg_lower = event.message.lower()
            if "temporal storm is imminent" in msg_lower:
                current_storm_start = event.timestamp
            elif current_storm_start and "temporal storm seems to be waning" in msg_lower:
                storms.append((current_storm_start, event.timestamp))
                current_storm_start = None
        return storms

    def get_player_data(self) -> Dict[str, PlayerData]:
        return self.players


class NarrativeGenerator:
    def __init__(self, output_templates: Dict[str, str], brief: bool = False):
        self.templates = output_templates
        self.brief = brief

    def _summarize_top(self, items: List[str], n: int = 3) -> Tuple[str, int]:
        if not items:
            return "", 0
        counter = Counter(items)
        top_items = counter.most_common(n)
        items_list = [item for item, _ in top_items]
        return grammatical_join(items_list), sum(counter.values())

    def generate_player_summary(self, players: Dict[str, PlayerData]) -> List[Dict]:
        summaries = []
        for player, data in sorted(players.items()):
            death_count = len(data.death_details)
            kill_count = len(data.kills)
            if self.brief:
                if death_count == 0 and kill_count == 0:
                    story = f"**{player.capitalize()}**: unscathed."
                else:
                    story = f"**{player.capitalize()}**: {death_count} death(s), {kill_count} kill(s)."
            else:
                if death_count == 1:
                    death_phrase = self.templates["single_death"].format(causes=grammatical_join(data.death_details))
                elif death_count == 2:
                    death_phrase = self.templates["double_death"].format(causes=grammatical_join(data.death_details))
                elif death_count >= 3:
                    top_deaths, _ = self._summarize_top(data.death_details)
                    death_phrase = self.templates["multiple_deaths"].format(count=death_count, causes=top_deaths)
                else:
                    death_phrase = ""
                if kill_count == 1:
                    kill_phrase = self.templates["single_kill"].format(kills=grammatical_join(data.kills))
                elif kill_count == 2:
                    kill_phrase = self.templates["double_kill"].format(kills=grammatical_join(data.kills))
                elif kill_count >= 3:
                    top_kills, _ = self._summarize_top(data.kills)
                    kill_phrase = self.templates["multiple_kills"].format(count=kill_count, kills=top_kills)
                else:
                    kill_phrase = ""
                metal_phrase = ""
                if data.large_metals:
                    metal_phrase = "They moved a large sum of " + grammatical_join(sorted(list(data.large_metals)))
                phrases = [phrase for phrase in (death_phrase, kill_phrase) if phrase]
                if phrases:
                    combined_phrases = " and ".join(phrases)
                    if metal_phrase:
                        combined_phrases = ". ".join([combined_phrases, metal_phrase])
                    story = self.templates["player_story"].format(player=player.capitalize(), phrases=combined_phrases)
                else:
                    story = f"**{player.capitalize()}** did nothing"
            summaries.append({
                "name": player.capitalize(),
                "death_count": death_count,
                "kill_count": kill_count,
                "story": story
            })
        return summaries

    def generate_story(self, players: Dict[str, PlayerData]) -> str:
        player_summaries = self.generate_player_summary(players)
        if player_summaries:
            return "\n".join(player["story"] for player in player_summaries)
        else:
            return self.templates.get("no_events", "Nothing ever happens")

    def generate_storm_summary(self, storms: List[Tuple[datetime, datetime]], fallback: Tuple[Optional[datetime], Optional[datetime], Optional[datetime]]) -> str:
        if storms and len(storms) > 1:
            n = len(storms)
            total_duration = sum((waning - imminent).total_seconds() / 60 for (imminent, waning) in storms)
            avg_duration = round(total_duration / n)
            return f"{n} temporal storms occurred, with an average duration of {avg_duration} minutes"
        elif storms and len(storms) == 1:
            imminent, waning = storms[0]
            duration = int((waning - imminent).total_seconds() / 60)
            return self.templates["storm_occurred"].format(start=imminent.strftime(TIMEONLY_FORMAT), duration=duration)
        else:
            storm_soon, storm_start, storm_waning = fallback
            if storm_start and storm_waning:
                duration = int((storm_waning - storm_start).total_seconds() / 60)
                return self.templates["storm_occurred"].format(start=storm_start.strftime(TIMEONLY_FORMAT), duration=duration)
            elif storm_start:
                return self.templates["storm_start"]
            elif storm_soon:
                return self.templates["storm_soon"].format(start=storm_soon.strftime(TIMEONLY_FORMAT))
            elif storm_waning:
                return self.templates["storm_ending"].format(end=storm_waning.strftime(TIMEONLY_FORMAT))
            return ""

    def generate_chunk_summary(self, count: int) -> str:
        if count > 0:
            return self.templates["chunk_summary"].format(count=count)
        else:
            return ""


def load_config(config_file: Optional[str]) -> Tuple[Dict[str, str], Dict[str, str], Dict[str, str]]:
    custom_message_map = DEFAULT_CUSTOM_MESSAGE_MAP.copy()
    custom_enemy_map = DEFAULT_CUSTOM_ENEMY_MAP.copy()
    output_templates = DEFAULT_OUTPUT_TEMPLATES.copy()
    if config_file:
        try:
            with open(config_file, "r", encoding="utf-8") as f:
                config = json.load(f)
            custom_message_map.update(config.get("custom_message_map", {}))
            custom_enemy_map.update(config.get("custom_enemy_map", {}))
            output_templates.update(config.get("output_templates", {}))
            logger.info("Configuration loaded successfully from %s", config_file)
        except Exception as e:
            logger.error("Failed to load configuration from %s: %s", config_file, e)
    return custom_message_map, custom_enemy_map, output_templates


def main() -> None:
    parser = argparse.ArgumentParser(description="Parse game logs and generate a narrative summary.")
    parser.add_argument("--log-dir", "-l", required=True, help="Directory containing .log files")
    parser.add_argument("--output-file", "-o", default="summary.txt", help="Output summary file")
    parser.add_argument("--state", "-s", default="state.json", help="State file (JSON) for last timestamp and chunk count")
    parser.add_argument("--recursive", "-r", action="store_true", help="Recursively search for log files in subdirectories")
    parser.add_argument("--char-limit", "-c", type=int, default=0, help="Maximum character limit for output message (0 for no limit)")
    parser.add_argument("--config", "-C", help="Optional JSON configuration file for custom mappings and templates")
    parser.add_argument("--force-full", "-f", action="store_true", help="Force a full search ignoring the state file")
    parser.add_argument("--delete-state", "-d", action="store_true", help="Delete the state file for a reset before processing")
    parser.add_argument("--time-range", "-t", help="Force search of events within a set time period from the last message's timestamp (e.g., '30m', '2h', '1d')")
    parser.add_argument("--brief", action="store_true", help="Generate less verbose output")
    args = parser.parse_args()

    custom_message_map, custom_enemy_map, output_templates = load_config(args.config)

    # Load or initialize state (last timestamp and last chunk count)
    if args.delete_state:
        if os.path.exists(args.state):
            try:
                os.remove(args.state)
                logger.info("State file deleted for reset.")
            except Exception as e:
                logger.error("Error deleting state file: %s", e)
        last_timestamp = datetime.min
        last_chunk_count = 0
    else:
        if os.path.exists(args.state):
            try:
                with open(args.state, "r", encoding="utf-8") as f:
                    state_data = json.load(f)
                last_timestamp = parse_timestamp(state_data.get("last_timestamp", ""))
                last_chunk_count = state_data.get("last_chunk_count", 0)
                if last_timestamp is None:
                    raise ValueError("Invalid timestamp in state file.")
            except Exception as e:
                logger.warning("State file issue: %s. Processing all messages.", e)
                last_timestamp = datetime.min
                last_chunk_count = 0
        else:
            logger.info("State file not found. Processing all messages.")
            last_timestamp = datetime.min
            last_chunk_count = 0

    if args.force_full:
        logger.info("Force full search enabled; ignoring state file timestamp.")
        last_timestamp = datetime.min

    if args.recursive:
        pattern = os.path.join(args.log_dir, '**', '*.log')
    else:
        pattern = os.path.join(args.log_dir, '*.log')
    log_files = glob.glob(pattern, recursive=args.recursive)

    logger.info("Processing %d log file(s).", len(log_files))

    if args.time_range:
        time_delta = parse_time_range(args.time_range)
        if time_delta is None:
            logger.warning("Invalid time range specified. Ignoring --time-range option.")
        else:
            max_ts = datetime.min
            for log_file in log_files:
                try:
                    with open(log_file, "r", encoding="utf-8") as file:
                        for line in file:
                            line = line.strip()
                            if not line:
                                continue
                            event = LogEvent.from_line(line)
                            if event and event.timestamp > max_ts:
                                max_ts = event.timestamp
                except Exception as e:
                    logger.error("Error processing file %s during time range: %s", log_file, e)
            if max_ts == datetime.min:
                logger.warning("No valid timestamps found in logs for time range. Ignoring --time-range option.")
            else:
                new_lower_bound = max_ts - time_delta
                logger.info("Time range option active: processing events from %s (max timestamp %s minus %s)",
                            new_lower_bound.strftime(DATE_FORMAT), max_ts.strftime(DATE_FORMAT), args.time_range)
                last_timestamp = new_lower_bound

    aggregator = EventAggregator(custom_message_map, custom_enemy_map, DEFAULT_METALS, DEFAULT_LARGE_METAL_THRESHOLD)
    max_timestamp_in_run = last_timestamp

    for log_file in log_files:
        try:
            with open(log_file, "r", encoding="utf-8") as file:
                for line in file:
                    line = line.strip()
                    if not line:
                        continue
                    event = LogEvent.from_line(line)
                    if not event or event.timestamp <= last_timestamp:
                        continue
                    if event.timestamp > max_timestamp_in_run:
                        max_timestamp_in_run = event.timestamp
                    aggregator.process_event(event)
        except Exception as e:
            logger.error("Error processing file %s: %s", log_file, e)

    # If no new offthread map chunk event was processed, keep the previous chunk count.
    if aggregator.last_map_chunk_timestamp is None:
        aggregator.chunk_count = last_chunk_count

    # Calculate new map chunks added
    added_chunks = aggregator.chunk_count - last_chunk_count
    if added_chunks < 0:
        added_chunks = 0

    narrative_gen = NarrativeGenerator(output_templates, brief=args.brief)
    player_story = narrative_gen.generate_story(aggregator.get_player_data())
    complete_storms = aggregator.get_complete_storms()
    fallback_storms = aggregator.aggregate_storm_times()
    storm_summary = narrative_gen.generate_storm_summary(complete_storms, fallback_storms)
    chunk_summary = narrative_gen.generate_chunk_summary(added_chunks)
    parts = []
    if args.time_range:
        match = re.match(r"(\d+)([mhd])$", args.time_range.strip().lower())
        if match:
            value = int(match.group(1))
            unit = match.group(2)
            if unit == "m":
                unit_desc = "minute(s)"
            elif unit == "h":
                unit_desc = "hour(s)"
            elif unit == "d":
                unit_desc = "day(s)"
            else:
                unit_desc = ""
            range_message = f"In the last {value} {unit_desc}..."
            parts.append(range_message)
    parts.append(player_story)
    if storm_summary:
        parts.append(storm_summary)
    if chunk_summary:
        parts.append(chunk_summary)
    full_summary = "\n".join(parts)

    if args.char_limit and args.char_limit > 0 and len(full_summary) > args.char_limit:
        full_summary = full_summary[:args.char_limit - 3] + "..." if args.char_limit > 3 else full_summary[:args.char_limit]

    try:
        with open(args.output_file, "w", encoding="utf-8") as output_file:
            output_file.write(full_summary)
        with open(args.state, "w", encoding="utf-8") as state_file:
            json.dump({
                "last_timestamp": max_timestamp_in_run.strftime(DATE_FORMAT),
                "last_chunk_count": aggregator.chunk_count
            }, state_file)
        logger.info("Narrative summary written to %s", args.output_file)
    except Exception as e:
        logger.error("Error writing output: %s", e)


if __name__ == "__main__":
    main()
