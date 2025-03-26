#ifndef MZN_LIB_H
#define MZN_LIB_H

#define MZN_LOG_ENABLE
#define MZN_LIB_IMPLEMENTATION

/* @LIB-COPYRIGHT ************************************************************/
/*                                                                           */
/* Copyright 2024 Maj Zalaznik Novak. All Rights Reserved.                   */
/*                                                                           */
/*****************************************************************************/

/* @LIB-INFO *****************************************************************/
/*                                                                           */
/* This is a single header C89 library for interactive audio-visual programs */
/* There are no advanced features, only the bare minimum for quick           */
/* prototyping                                                               */
/*                                                                           */
/*****************************************************************************/

/* @LIB-INCLUDES *************************************************************/

#include "stdint.h"
#include "stdarg.h"

#ifdef _WIN64
#define MZN_PLATFORM_WIN64
#define MZN_PLATFORM_WINDOWS
#elif _WIN32
#define MZN_PLATFORM_WIN32
#define MZN_PLATFORM_WINDOWS
#elif __APPLE__
#define MZN_PLATFORM_OSX
#elif __linux__
#define MZN_PLATFORM_LINUX
#else
#define MZN_PLATFORM_UNKNOWN
#endif

#ifdef MZN_PLATFORM_WINDOWS
#define ELIMINATE_GCC_WARNING = 0 /* remove noise when using Wextra */
#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#define NOMINMAX
#define NOMCX
#define NODEFERWINDOWPOS
#define NOKANJI
#define NODRAWTEXT
#define NOSERVICE
#define NOTEXTMETRIC
#define NOCOMM
#define NOHELP
#define NONLS
#include <windows.h>
#include <initguid.h>
#include <shellapi.h>
#include <avrt.h>
#include <mmreg.h>
#include <mmdeviceapi.h>
#include <audioclient.h>
#include <intrin.h>
#endif /* MZN_PLATFORM_WINDOWS */

/* @LIB-READ-ONLY-DATA *******************************************************/

typedef enum mznVirtualKeys {
  KEY_LBUTTON = 0x01, KEY_RBUTTON    = 0x02, KEY_CANCEL     = 0x03,
  KEY_MBUTTON = 0x04, KEY_XBUTTON1   = 0x05, KEY_XBUTTON2   = 0x06,
  KEY_BACK    = 0x08, KEY_TAB        = 0x09, KEY_CLEAR      = 0x0C,
  KEY_RETURN  = 0x0D, KEY_SHIFT      = 0x10, KEY_CONTROL    = 0x11,
  KEY_MENU    = 0x12, KEY_PAUSE      = 0x13, KEY_CAPITAL    = 0x14,
  KEY_KANA    = 0x15, KEY_HANGUL     = 0x15, KEY_JUNJA      = 0x17,
  KEY_FINAL   = 0x18, KEY_HANJA      = 0x19, KEY_KANJI      = 0x19,
  KEY_ESCAPE  = 0x1B, KEY_CONVERT    = 0x1C, KEY_NONCONVERT = 0x1D,
  KEY_ACCEPT  = 0x1E, KEY_MODECHANGE = 0x1F, KEY_SPACE      = 0x20,
  KEY_PRIOR   = 0x21, KEY_NEXT       = 0x22, KEY_END        = 0x23,
  KEY_HOME    = 0x24, KEY_LEFT       = 0x25, KEY_UP         = 0x26,
  KEY_RIGHT   = 0x27, KEY_DOWN       = 0x28, KEY_SELECT     = 0x29,
  KEY_PRINT   = 0x2A, KEY_RUN        = 0x2B, KEY_SNAPSHOT   = 0x2C,
  KEY_INSERT  = 0x2D, KEY_DELETE = 0x2E, KEY_HELP = 0x2F,
  KEY_0 = 0x30, KEY_1 = 0x31, KEY_2 = 0x32,
  KEY_3 = 0x33, KEY_4 = 0x34, KEY_5 = 0x35,
  KEY_6 = 0x36, KEY_7 = 0x37, KEY_8 = 0x38,
  KEY_9 = 0x39, KEY_A = 0x41, KEY_B = 0x42,
  KEY_C = 0x43, KEY_D = 0x44, KEY_E = 0x45,
  KEY_F = 0x46, KEY_G = 0x47, KEY_H = 0x48,
  KEY_I = 0x49, KEY_J = 0x4A, KEY_K = 0x4B,
  KEY_L = 0x4C, KEY_M = 0x4D, KEY_N = 0x4E,
  KEY_O = 0x4F, KEY_P = 0x50, KEY_Q = 0x51,
  KEY_R = 0x52, KEY_S = 0x53, KEY_T = 0x54,
  KEY_U = 0x55, KEY_V = 0x56, KEY_W = 0x57,
  KEY_X = 0x58, KEY_Y = 0x59, KEY_Z = 0x5A,
  KEY_LWIN    = 0x5B, KEY_RWIN      = 0x5C, KEY_APPS     = 0x5D,
  KEY_SLEEP   = 0x5F, KEY_NUMPAD0   = 0x60, KEY_NUMPAD1  = 0x61,
  KEY_NUMPAD2 = 0x62, KEY_NUMPAD3   = 0x63, KEY_NUMPAD4  = 0x64,
  KEY_NUMPAD5 = 0x65, KEY_NUMPAD6   = 0x66, KEY_NUMPAD7  = 0x67,
  KEY_NUMPAD8 = 0x68, KEY_NUMPAD9   = 0x69, KEY_MULTIPLY = 0x6A,
  KEY_ADD     = 0x6B, KEY_SEPARATOR = 0x6C, KEY_SUBTRACT = 0x6D,
  KEY_DECIMAL = 0x6E, KEY_DIVIDE    = 0x6F, KEY_F1       = 0x70,
  KEY_F2  = 0x71, KEY_F3  = 0x72, KEY_F4      = 0x73,
  KEY_F5  = 0x74, KEY_F6  = 0x75, KEY_F7      = 0x76,
  KEY_F8  = 0x77, KEY_F9  = 0x78, KEY_F10     = 0x79,
  KEY_F11 = 0x7A, KEY_F12 = 0x7B, KEY_F13     = 0x7C,
  KEY_F14 = 0x7D, KEY_F15 = 0x7E, KEY_F16     = 0x7F,
  KEY_F17 = 0x80, KEY_F18 = 0x81, KEY_F19     = 0x82,
  KEY_F20 = 0x83, KEY_F21 = 0x84, KEY_F22     = 0x85,
  KEY_F23 = 0x86, KEY_F24 = 0x87, KEY_NUMLOCK = 0x90,
  KEY_SCROLL   = 0x91, KEY_LSHIFT       = 0xA0, KEY_RSHIFT          = 0xA1,
  KEY_LCONTROL = 0xA2, KEY_RCONTROL     = 0xA3, KEY_LMENU           = 0xA4,
  KEY_RMENU    = 0xA5, KEY_BROWSER_BACK = 0xA6, KEY_BROWSER_FORWARD = 0xA7,
  KEY_BROWSER_REFRESH   = 0xA8, KEY_BROWSER_STOP        = 0xA9,
  KEY_BROWSER_SEARCH    = 0xAA, KEY_BROWSER_FAVORITES   = 0xAB,
  KEY_BROWSER_HOME      = 0xAC, KEY_VOLUME_MUTE         = 0xAD,
  KEY_VOLUME_DOWN       = 0xAE, KEY_VOLUME_UP           = 0xAF,
  KEY_MEDIA_NEXT_TRACK  = 0xB0, KEY_MEDIA_PREV_TRACK    = 0xB1,
  KEY_MEDIA_STOP        = 0xB2, KEY_MEDIA_PLAY_PAUSE    = 0xB3,
  KEY_LAUNCH_MAIL       = 0xB4, KEY_LAUNCH_MEDIA_SELECT = 0xB5,
  KEY_LAUNCH_APP1       = 0xB6, KEY_LAUNCH_APP2         = 0xB7,
  KEY_OEM_1             = 0xBA, KEY_OEM_PLUS            = 0xBB,
  KEY_OEM_COMMA         = 0xBC, KEY_OEM_MINUS           = 0xBD,
  KEY_OEM_PERIOD        = 0xBE, KEY_OEM_2               = 0xBF,
  KEY_OEM_3             = 0xC0, KEY_OEM_4               = 0xDB,
  KEY_OEM_5  = 0xDC, KEY_OEM_6   = 0xDD, KEY_OEM_7      = 0xDE,
  KEY_OEM_8  = 0xDF, KEY_OEM_102 = 0xE2, KEY_PROCESSKEY = 0xE5,
  KEY_PACKET = 0xE7, KEY_ATTN    = 0xF6, KEY_CRSEL      = 0xF7,
  KEY_EXSEL  = 0xF8, KEY_EREOF   = 0xF9, KEY_PLAY       = 0xFA,
  KEY_ZOOM   = 0xFB, KEY_NONAME  = 0xFC, KEY_PA1        = 0xFD,
  KEY_OEM_CLEAR = 0xFE
} mznVirtualKeys;

/* @LIB-TYPEDEFS *************************************************************/

#if 0
typedef int8_t     int8, i8;
typedef uint8_t   uint8, u8;
#else
typedef char                 int8, i8;
typedef unsigned char       uint8, u8;
#endif
typedef float     real32, r32;
typedef double    real64, r64;
typedef int16_t   int16, i16;
typedef int32_t   int32, i32;
typedef int64_t   int64, i64;
typedef uint16_t   uint16, u16;
typedef uint32_t   uint32, u32;
typedef uint64_t   uint64, u64;
typedef unsigned long ulong;
typedef unsigned long ushort;
typedef int32 MZNEVENT;
typedef int32 MZNRET;
typedef int32 MZNARG;
typedef void* MZNPTR;
typedef void* MZNVOID;

/* @LIB-DEFINES **************************************************************/

#define MZN_GLOBAL static
#define MZN_INT_32_MAX 2147483647
#define MZN_INT_32_MIN -2147483648
#define MZN_INT_16_MAX 32767
#define MZN_INT_24_MAX 8388607
#define MZN_FLT_16_MAX 32767.0f
#define MZN_FLT_24_MAX 8388607.0f
#define MZN_PI 				 3.14159265358979323846
#define MZN_PI_OVER_2  1.57079632679489661923
#define MZN_2_OVER_PI  0.63661977236758134308  /* 2/π */
#define MZN_TAU    6.2831853071795862
#define MZN_EU     2.7182818284590452
#define MZN_ERROR -1

#define MZN_MIN(_a, _b)                                 (((_a)<(_b))?(_a):(_b))
#define MZN_MAX(_a, _b)                                 (((_a)>(_b))?(_a):(_b))
#define MZN_MIX(_a, _b, _t)                       (((1.0-(_t))*(_a))+(_t)*(_b))
#define MZN_ABS(__a)                               ((__a < 0) ? (-__a) : (__a))
#define MZN_FABS(__x)                              ((__x) < 0 ? -(__x) : (__x))
#define MZN_MODF(_x, _y)                     ((_x) - (i32)((_x) / (_y)) * (_y))
#define MZN_LERP(_v1, _v2, _w)            ((1.0 - (_w)) * (_v1) + (_w) * (_v2))
#define MZN_SWAP(_x_, _y_, _temp_)        _temp_ = _x_; _x_ = _y_; _y_ = _temp_
#define MZN_CLAMP(_a, _l, _h)            ((MZN_MIN(MZN_MAX((_a), (_l)), (_h))))
#define MZN_BOUNDS(x, y, a, b, c, d)     ((x)>=(a)&&(x)<(c)&&(y)>=(b)&&(y)<(d))
#define MZN_INDEX(_c, _p, _x, _y)                     ((_c) + ((_x)+(_y)*(_p)))
#define MZN_INC_DECIMAL(_m)              ((_m < 10) ? 2 : ((_m < 100) ? 3 : 4))
#define MZN_ALPHA_BLEND(_bg, _fg)                                             \
  (  ((uint8)((((_fg >> 24))*((_fg>>0x10)&0xFF) +                           	\
    (256 - (_fg >> 24))*((_bg>>0x10)&0xFF))>>8) << 0x10)               				\
  | ((uint8)((((_fg >> 24))*((_fg>>0x08)&0xFF) +                           		\
    (256 - (_fg >> 24))*((_bg>>0x08)&0xFF))>>8) << 0x08)               				\
  | ((uint8)((((_fg >> 24))*((_fg>>0x00)&0xFF) +                            	\
    (256 - (_fg >> 24))*((_bg>>0x00)&0xFF))>>8) << 0x00))
#define MZN_ARGB(a, r, g, b)     (((a) << 24) | ((r) << 16) | ((g) << 8) | (b))

#undef    TRUE
#define   TRUE 	1
#undef    FALSE
#define   FALSE 0

#define MZN_NORTH               0x1
#define MZN_SOUTH               0x2
#define MZN_EAST                0x4
#define MZN_WEST                0x8
#define MZN_TOP                 0x01
#define MZN_BOTTOM              0x02
#define MZN_LEFT                0x04
#define MZN_RIGHT               0x08
#define MZN_MIDDLE              0x10

#define MZN_KEY_IDLE            0x00
#define MZN_KEY_PRESSED         0x01
#define MZN_KEY_HELD            0x02
#define MZN_KEY_RELEASED        0x04
#define MZN_KEY_REPEAT          0x08


#define MZN_FILE_DATA_MAX_NAME 	0xFF
#define MZN_FILE_DATA_MAX_EXT 	0x08

#define MZN_FILE_DATA_SCRATCH_SIZE 32

#define MZN_IS_FILE 0
#define MZN_IS_DIR 	1

#if 1 /* set to zero if not compiling with gcc */
#define MZN_INF      	__builtin_inf()
#define MZN_NAN       __builtin_nan("")
#define MZN_IS_INF    __builtin_isinf
#define MZN_IS_NAN    __builtin_isnan
#else
#define MZN_INF       0
#define MZN_NAN       0
#define MZN_IS_INF    0
#define MZN_IS_NAN    0
#endif

#define MZN_MAX_KEYS 												256
#define MZN_MAX_STRING 											1024

#define MZN_QUAD_HD_SIZE 										2560*1440
#define MZN_FULL_HD_SIZE 										1920*1080
#define MZN_STD_HD_SIZE    									1280*720
#define MZN_SVGA_SIZE       								800*600
#define MZN_VGA_SIZE        								640*480

#define MZN_AUDIO_REFTIMES_PER_SEC        	10000000
#define MZN_AUDIO_REFTIMES_PER_MILLISEC    	10000
#define MZN_AUDIO_SHARED                  	AUDCLNT_SHAREMODE_SHARED
#define MZN_AUDIO_EXCLUSIVE               	AUDCLNT_SHAREMODE_EXCLUSIVE

#ifdef MZN_PLATFORM_WINDOWS
#define int128                 __m128i
#define i128                   __m128i
#define r128                   __m128
#define MZN_MM_zeroReal128     _mm_setzero_ps
#define MZN_MM_zeroInt128      _mm_setzero_si128
#define MZN_MM_r128Broad       _mm_set_ps1
#define MZN_MM_i128Broad       _mm_set1_epi32
#define MZN_MM_r128            _mm_set_ps
#define MZN_MM_i128            _mm_set_epi32
#define MZN_MM_addReal128      _mm_add_ps
#define MZN_MM_addInt128       _mm_add_epi32
#define MZN_MM_subReal128      _mm_sub_ps
#define MZN_MM_subInt128       _mm_sub_epi32
#define MZN_MM_mulReal128      _mm_mul_ps
#define MZN_MM_divReal128      _mm_div_ps
#define MZN_MM_mulInt128U      _mm_mul_epu32
#define MZN_MM_sqrt128         _mm_sqrt_ps
#define MZN_MM_rsqrt128        _mm_rsqrt_ps
#define MZN_MM_rcp128          _mm_rcp_ps
#define MZN_MM_castToReal128   _mm_castsi128_ps
#define MZN_MM_castToInt128    _mm_castps_si128
#define MZN_MM_maxReal128      _mm_max_ps
#define MZN_MM_minReal128      _mm_min_ps
#define MZN_MM_shfReal128      _mm_shuffle_ps
#define MZN_MM_extractLow128   _mm_cvtss_f32
#define MZN_MM_shf(z, y, x, w)                                               	\
 (((z) << 6) |                                                               	\
  ((y) << 4) |                                                               	\
  ((x) << 2) | (w))
#define MZN_MM_r128Index(p, i)                                               	\
	_mm_cvtss_f32(_mm_shuffle_ps(p, p, MZN_MM_shf(i, i, i, i)))
#define MZN_GET_SCREEN_X SM_CXSCREEN
#define MZN_GET_SCREEN_Y SM_CYSCREEN
#endif

#define MZN_COLOURED_PRINTF

/* @LIB-LOGGING **************************************************************/

#define LOG_ERROR 0
#define LOG_BASIC 1
#define LOG_INFO  2
#define LOG_DEBUG 3
#define LOG_WARN  4

#define MZN_ASSERT(_x_) if(!(_x_))\
	{ mzn_printf("%s - %d: %s = %d\n", __FILE__, __LINE__, #_x_, (_x_)); }

#define COL_BLK   "\33[0;30m"
#define COL_RED   "\33[0;31m"
#define COL_GRN   "\33[0;32m"
#define COL_YEL   "\33[0;33m"
#define COL_BLU   "\33[0;34m"
#define COL_MAG   "\33[0;35m"
#define COL_CYN   "\33[0;36m"
#define COL_WHT   "\33[0;37m"
#define COL_HBLK  "\33[0;90m"
#define COL_HRED  "\33[0;91m"
#define COL_HGRN  "\33[0;92m"
#define COL_HYEL  "\33[0;93m"
#define COL_HBLU  "\33[0;94m"
#define COL_HMAG  "\33[0;95m"
#define COL_HCYN  "\33[0;96m"
#define COL_HWHT  "\33[0;97m"
#define COL_RESET "\33[0m"

#ifdef MZN_LOG_ENABLE


i32 mzn_vsnprintf(i8* dst, size_t len, size_t n, const i8* fmt, va_list args);
i32 mzn_snprintf(i8* dst, size_t len, size_t n, const i8* fmt, ...);
i32 mzn_printf(const i8* fmt, ...);
i32 mzn_puts(const i8* str);
i32 mzn_putc(const i8 c);
i32 mzn_memset(void* mem, uint8 v, size_t n);

MZN_GLOBAL int MZN_CUR_LINE 				= 0;
MZN_GLOBAL const int8* MZN_CUR_FILE = 0;
MZN_GLOBAL const int8* MZN_CUR_FUNC = 0;
MZN_GLOBAL uint8 			 MZN_MODE			= LOG_DEBUG;

#define MZN_MAX_LOG 1024
MZN_GLOBAL int8 MZN_LOG_BUFFER[MZN_MAX_LOG];

#define MZN_LOGPREFIX_WARNING mzn_printf(                                     \
  COL_YEL "WARNING "                                                      		\
  COL_HYEL "%s %d %s"                                                       	\
  COL_YEL " ~ " COL_YEL,                                                    	\
  MZN_CUR_FILE, MZN_CUR_LINE, MZN_CUR_FUNC)

#define MZN_LOGPREFIX_DEBUG mzn_printf(                                       \
  COL_HYEL "DEBUG "                                                       		\
  COL_HBLU "%s %d %s"                                                       	\
  COL_HYEL " ~ " COL_HYEL,                                                  	\
  MZN_CUR_FILE, MZN_CUR_LINE, MZN_CUR_FUNC)

#define MZN_LOGPREFIX_ERROR mzn_printf(                                       \
  COL_HRED "ERROR "                                                       		\
  COL_HBLU "%s %d %s"                                                       	\
  COL_HRED " ~ " COL_HRED,                                                  	\
  MZN_CUR_FILE, MZN_CUR_LINE, MZN_CUR_FUNC)

#define MZN_LOGPREFIX_INFO mzn_printf(                                        \
  COL_YEL  "INFO  "                                                       		\
  COL_HBLU "%s %d %s"                                                       	\
  COL_YEL  " ~ " COL_YEL,                                                   	\
  MZN_CUR_FILE, MZN_CUR_LINE, MZN_CUR_FUNC)

#define MZN_LOGPREFIX_BASIC mzn_printf(                                       \
  COL_GRN  "Z " COL_HBLU "%s" COL_GRN " ~ " COL_RESET, MZN_CUR_FUNC)

MZNRET mzn_debug_log(uint8 mode, const int8* format, ...);
MZNRET mzn_debug_none(uint8 mode, const char* format, ...);

#ifdef MZN_LIB_IMPLEMENTATION
MZNRET mzn_debug_log(uint8 mode, const char* format, ...) {
  if(mode <= MZN_MODE) {
    va_list args;
    mzn_memset(MZN_LOG_BUFFER, 0, MZN_MAX_LOG);
    va_start(args, format);
		mzn_vsnprintf(MZN_LOG_BUFFER, MZN_MAX_LOG, MZN_MAX_LOG, format, args);
    va_end(args);
    switch (mode) {
    case(LOG_ERROR): { MZN_LOGPREFIX_ERROR;  break; }
    case(LOG_DEBUG): { MZN_LOGPREFIX_DEBUG;  break; }
    case(LOG_INFO): { MZN_LOGPREFIX_INFO;   break; }
    case(LOG_BASIC): { MZN_LOGPREFIX_BASIC;  break; }
    case(LOG_WARN): { MZN_LOGPREFIX_WARNING;  break; }
    default: { break; }
    }
    mzn_puts(MZN_LOG_BUFFER);
    mzn_putc('\n');
  }
  return 0;
}

#endif /* MZN_LIB_IMPLEMENTATION */

#define MZN_LOG                                                               \
MZN_CUR_FILE = __FILE__;                                                			\
MZN_CUR_FUNC = "->"; /* change to __FUNCTION__ if compiler supports */				\
MZN_CUR_LINE = __LINE__;                                                			\
mzn_debug_log

#else

#ifdef MZN_LIB_IMPLEMENTATION

MZNRET mzn_debug_none(uint8 mode, const char* format, ...) { return 0; }

#define MZN_LOG mzn_debug_none

#endif /* MZN_LIB_IMPLEMENTATION */

#endif /* MZN_LOG_ENABLE */

/* @LIB-GENERATED ************************************************************/

#ifdef MZN_LIB_IMPLEMENTATION

#define _PP_CAT2(a, b) a##b
#define _PP_CAT3(a, b, c) a##b##c
#define _PP_MEM2(type) type x;type y;
#define _PP_MEM3(type) type x;type y;type z;
#define _PP_MEM4(type) type x;type y;type z;type w;
#define _PP_MEM5(type) type x;type y;type z;type w;type t;
#define _P2(type) type x,type y
#define _P3(type) type x,type y,type z
#define _P4(type) type x,type y,type z,type w
#define _P5(type) type x,type y,type z,type w,type t
#define _PP_CP2(op) ret.x op x;ret.y op y;
#define _PP_CP3(op) ret.x op x;ret.y op y;ret.z op z;
#define _PP_CP4(op) ret.x op x;ret.y op y;ret.z op z;ret.w op w;
#define _PP_CP5(op) ret.x op x;ret.y op y;ret.z op z;ret.w op w;ret.t op t;
#define _PP_SP2(op) x.x op y;x.y op y;
#define _PP_SP3(op) x.x op y;x.y op y;x.z op y;
#define _PP_SP4(op) x.x op y;x.y op y;x.z op y;x.w op y;
#define _PP_SP5(op) x.x op y;x.y op y;x.z op y;x.w op y;x.t op y;
#define _PP_EQ2(op)                                                           \
(x.x op y.x)&&(x.y op y.y)
#define _PP_EQ3(op)                                                           \
(x.x op y.x)&&(x.y op y.y)&&(x.z op y.z)
#define _PP_EQ4(op)                                                           \
(x.x op y.x)&&(x.y op y.y)&&(x.z op y.z)&&(x.w op y.w)
#define _PP_EQ5(op)                                                           \
(x.x op y.x)&&(x.y op y.y)&&(x.z op y.z)&&(x.w op y.w)&&(x.t op y.t)
#define _PP_OP2(op)                                                           \
ret.x=x.x op y.x;                                                            	\
ret.y=x.y op y.y;
#define _PP_OP3(op)                                                           \
ret.x=x.x op y.x;                                                            	\
ret.y=x.y op y.y;                                                            	\
ret.z=x.z op y.z;
#define _PP_OP4(op)                                                           \
ret.x=x.x op y.x;                                                            	\
ret.y=x.y op y.y;                                                            	\
ret.z=x.z op y.z;                                                            	\
ret.w=x.w op y.w;
#define _PP_OP5(op)                                                           \
ret.x=x.x op y.x;                                                            	\
ret.y=x.y op y.y;                                                            	\
ret.z=x.z op y.z;                                                            	\
ret.w=x.w op y.w;                                                            	\
ret.t=x.t op y.t;
#define _PP_NAME(x, y, z) x##y##z
#define _PP_FNM(ret, prefix, name, proc) ret _PP_CAT3(prefix##_, name, proc)
#define _PP_CNM(ret, prefix, name) ret _PP_CAT2(prefix##_, name)
#define _PP_FUNCX(prefix, type, name, num, pfx, proc, op)                     \
_PP_FUNC(prefix, type, _PP_NAME(name, num, pfx), num, proc, op)
#define _PP_SCALX(prefix, type, name, num, pfx, proc, op)                     \
_PP_SCAL(prefix, type, _PP_NAME(name, num, pfx), num, proc, op)
#define _PP_CONSX(prefix, type, name, num, pfx)                               \
_PP_CONS(prefix, type, _PP_NAME(name, num, pfx), num)
#define _PP_EQX(prefix, type, name, num, pfx)                                 \
_PP_EQ(prefix, type, _PP_NAME(name, num, pfx), num)
#define _PP_STRC(type, name, num, pfx)\
typedef struct _PP_NAME(tag_##name, num, pfx)\
{_PP_MEM##num(type)}_PP_NAME(name, num, pfx);
#define _PP_CONS(prefix, type, name, num)\
  _PP_CNM(name, prefix, name)\
(_P##num(type)){name ret;_PP_CP##num(=)return ret;}
#define _PP_EQ(prefix, type, name, num)\
  _PP_FNM(i32, prefix, name, _eq)\
(_P2(name)){return (_PP_EQ##num(==));}
#define _PP_FUNC(prefix, type, name, num, proc, op)\
_PP_FNM(name, prefix, name, proc)\
(_P2(name)){name ret;_PP_OP##num(op)return ret;}
#define _PP_SCAL(prefix, type, name, num, proc, op)\
  _PP_FNM(name, prefix, name, proc)\
(name x, type y){_PP_SP##num(op)return x;}
#define _PP_DEF_FLT_OPS(type, name, num, pfx)                                 \
_PP_STRC(type, name, num, pfx)                                                \
_PP_CONSX(mzn, type, name, num, pfx)                                          \
_PP_FUNCX(mzn, type, name, num, pfx, _add, +)                                 \
_PP_FUNCX(mzn, type, name, num, pfx, _sub, -)                                 \
_PP_FUNCX(mzn, type, name, num, pfx, _mul, *)                                 \
_PP_FUNCX(mzn, type, name, num, pfx, _div, /)                                 \
_PP_SCALX(mzn, type, name, num, pfx, _add_s, +=)                              \
_PP_SCALX(mzn, type, name, num, pfx, _sub_s, -=)                              \
_PP_SCALX(mzn, type, name, num, pfx, _mul_s, *=)                              \
_PP_SCALX(mzn, type, name, num, pfx, _div_s, /=)
#define _PP_DEF_INT_OPS(type, name, num, pfx)                                 \
_PP_STRC(type, name, num, pfx)                                                \
_PP_EQX(mzn, type, name, num, pfx)                                            \
_PP_CONSX(mzn, type, name, num, pfx)                                          \
_PP_FUNCX(mzn, type, name, num, pfx, _add, +)                                 \
_PP_FUNCX(mzn, type, name, num, pfx, _sub, -)                                 \
_PP_FUNCX(mzn, type, name, num, pfx, _mul, *)                                 \
_PP_FUNCX(mzn, type, name, num, pfx, _div, /)                                 \
_PP_SCALX(mzn, type, name, num, pfx, _add_s, +=)                              \
_PP_SCALX(mzn, type, name, num, pfx, _sub_s, -=)                              \
_PP_SCALX(mzn, type, name, num, pfx, _mul_s, *=)                              \
_PP_SCALX(mzn, type, name, num, pfx, _div_s, /=)
#define _PP_DEF_FLT_DIMENSIONS(type, name, pfx)                               \
_PP_DEF_FLT_OPS(type, name, 2, pfx)                                           \
_PP_DEF_FLT_OPS(type, name, 3, pfx)                                           \
_PP_DEF_FLT_OPS(type, name, 4, pfx)                                           \
_PP_DEF_FLT_OPS(type, name, 5, pfx)
#define _PP_DEF_INT_DIMENSIONS(type, name, pfx)                               \
_PP_DEF_INT_OPS(type, name, 2, pfx)                                           \
_PP_DEF_INT_OPS(type, name, 3, pfx)                                           \
_PP_DEF_INT_OPS(type, name, 4, pfx)                                           \
_PP_DEF_INT_OPS(type, name, 5, pfx)

_PP_DEF_FLT_DIMENSIONS(float, vec, f)
_PP_DEF_FLT_DIMENSIONS(double, vec, d)
_PP_DEF_INT_DIMENSIONS(int, vec, i)
_PP_DEF_INT_DIMENSIONS(unsigned int, vec, u)
_PP_DEF_INT_DIMENSIONS(char, vec, c)
_PP_DEF_INT_DIMENSIONS(uint8, vec, b)

#endif /* STD_LIB_IMPLEMENTATION */

/* @LIB-STRUCTURE-DECLARATIONS ***********************************************/

typedef struct mznAudioContext_t 	mznAudioContext;
typedef struct mznWindowContext_t mznWindowContext;

/* @LIB-STRUCTURES ***********************************************************/

typedef enum mznPixelFormat_e {
	MZN_PIX_RGBA,
	MZN_PIX_RGB,
	MZN_PIX_FLOAT,
	MZN_PIX_INDEX
} mznPixelFormat;

typedef struct mznFramebuffer_t {
	void* data;
	uint32 size;
	uint32 width;
	uint32 height;
	mznPixelFormat format;
} mznFramebuffer;

typedef struct mznRenderContext_t {
	mznFramebuffer* bank;
	uint32 active;
	uint32 count;
	uint32 max;
} mznRenderContext;

typedef struct mznAudioFormat_t {
	uint32 bitRate;
	uint32 sampleRate;
	uint32 channels;
	uint32 type;
} mznAudioFormat;

typedef struct mznFileData_t {
	int8 filename[MZN_FILE_DATA_MAX_NAME];
	int8 extension[MZN_FILE_DATA_MAX_EXT];
	uint64 timeLastModified;
	uint64 timeCreated;
	uint32 attributes;
	uint32 flags;
} mznFileData;

typedef struct mznContext_t {
	mznWindowContext* window;
	mznAudioContext* audio;
	mznRenderContext* render;
} mznContext;

/* @PLATFORM-CALLBACKS *******************************************************/

typedef MZNRET (*PFEVENTPROC) (MZNPTR h, MZNEVENT e, MZNARG a, MZNARG b);
typedef MZNRET (*PFAUDIOPROC) (void *buf, mznAudioFormat fmz, void* dat);
typedef MZNRET (*PFFILELIST) (mznFileData* fileData, void* args);

/* @PLATFORM-INTERFACE *******************************************************/

MZNPTR mzn_sys_window_create(mznWindowContext* c, void* data);
MZNRET mzn_sys_window_close(mznWindowContext* c);
MZNRET mzn_sys_window_update(mznWindowContext* c);
MZNRET mzn_sys_window_minimize(mznWindowContext* c);
MZNRET mzn_sys_window_restore(mznWindowContext* c);
MZNRET mzn_sys_window_maximize(mznWindowContext* c);
MZNRET mzn_sys_window_blit(mznWindowContext* c, MZNPTR buf, i32 w, i32 h);

MZNRET mzn_sys_is_dir(const int8* path);
MZNRET mzn_sys_scan_dir(const char *dir, PFFILELIST proc, void* args);

MZNRET mzn_sys_fputc(void* handle, i8 c);
MZNRET mzn_sys_fputs(MZNPTR handle, const i8* str);
MZNRET mzn_sys_fputsn(MZNPTR handle, const i8* str, size_t len);

MZNRET mzn_sys_putc(i8 c);
MZNRET mzn_sys_puts(const i8* str);
MZNRET mzn_sys_putsn(const i8* str, size_t len);

MZNRET mzn_sys_window_context_init(
		mznWindowContext* context,
		const int8* title,
		int32 width,
		int32 height);

MZNRET mzn_sys_audio_context_init(
		mznAudioContext* context,
		i32 bitRate,
		i32 sampleRate,
		i32 channels,
		i32 bufferSize,
		i32 sleepPeriod,
		i32 mode);


MZNRET mzn_sys_audio_init(mznAudioContext* context);
MZNRET mzn_sys_audio_play(mznAudioContext* context);
MZNRET mzn_sys_audio_stop(mznAudioContext* context);
MZNRET mzn_sys_audio_finalize(mznAudioContext* context);
MZNRET mzn_sys_audio_update(mznAudioContext* c, PFAUDIOPROC pf, void* data);

MZNPTR mzn_sys_alloc(size_t size);
MZNRET mzn_sys_free(MZNPTR ptr);

MZNRET mzn_sys_fclose(MZNPTR file);
MZNPTR mzn_sys_fopen(const i8* filename, const i8* format);
MZNRET mzn_sys_fwrite(MZNPTR file, MZNPTR mem, size_t len);
MZNRET mzn_sys_fread(MZNPTR file, MZNPTR mem, size_t len, size_t amt);
MZNRET mzn_sys_scan_dir(const char *dir, PFFILELIST proc, void* args);

i64 mzn_sys_clock(void);
i64 mzn_sys_clock_frequency(void);

#define MZN_AUDIO_EXCLUSIVE AUDCLNT_SHAREMODE_EXCLUSIVE
#define MZN_AUDIO_SHARED AUDCLNT_SHAREMODE_SHARED

#define MZN_AUDIO_REFTIMES_PER_SEC        10000000
#define MZN_AUDIO_REFTIMES_PER_MILLISEC   10000
#define MZN_AUDIO_PCM 	0x0
#define MZN_AUDIO_FLOAT 0x1

#define MZN_AUD_SAFE_RELEASE(punk) 																						\
	if((punk) != NULL) { (punk)->lpVtbl->Release(punk); (punk) = NULL; }
#define MZN_AUD_ERROR(hres)                                         					\
	if(FAILED(hres)){ printf("[ERR]<%d> 0x%X\n",__LINE__, (uint32)hres); }

/* @PLATFORM-GLOBALS *********************************************************/

MZN_GLOBAL mznFileData MZN_FILE_DATA_SCRATCH[MZN_FILE_DATA_SCRATCH_SIZE];

/* @PLATFORM-WIN32 ***********************************************************/

struct mznAudioContext_t {
	mznAudioFormat format;
	BYTE* data;
	IMMDeviceEnumerator* deviceEnum;
  IMMDevice* device;
  IAudioClient* client;
  IAudioRenderClient* clientRender;
	WAVEFORMATEX* pwfx;
 	HANDLE handleEvent;
  HANDLE handleTask;
  HANDLE signalFill;
  HANDLE signalInit;
  HANDLE signalAPI;
  HANDLE handleThread;
  DWORD threadID;
	UINT32 bufferFrameCount;
	uint32 bufferSize;
	uint32 running;
	uint32 mode;
	uint32 threadSleepMs;
	real64 globalPhase;
	uint64 playbackCursor;
};

struct mznWindowContext_t {
	int32 width;
	int32 height;
	int32 terminate;
	int32 titleSize;
	int32 borderSize;
	const int8* title;
	void* hwnd;
};

/* @PLATFORM-INTERFACE-WIN32 *************************************************/

LRESULT CALLBACK mzn_sys_event_callback(HWND h, UINT m, WPARAM w, LPARAM l);

/* @PLATFORM-IMPLEMENTATION-WIN32 ********************************************/

#ifdef MZN_LIB_IMPLEMENTATION

/* @PLATFORM-CONTEXT-WIN32 ***************************************************/

MZNRET mzn_sys_window_context_init(
		mznWindowContext* c, const int8* title, int32 width, int32 height) {
	mzn_memset(c, 0, sizeof(mznWindowContext));
	c->width = width;
	c->height = height;
	c->title = title;
	c->titleSize = 22;
	c->borderSize = 4;
	return TRUE;
}

MZNRET mzn_sys_audio_context_init(
		mznAudioContext* c, i32 br, i32 sr, i32 ch, i32 bs, i32 sms, i32 mode) {
	mzn_memset(c, 0, sizeof(mznAudioContext));
	c->format.bitRate = br;
	c->format.sampleRate = sr;
	c->format.channels = ch;
	c->threadSleepMs = sms;
	c->bufferSize = bs;
	c->mode = mode;
	return TRUE;
}

/* @PLATFORM-WINDOW-WIN32 ****************************************************/

mznContext* mzn_sys_get_context_ptr(HWND hwnd) {
	LONG_PTR ptr = GetWindowLongPtr(hwnd, GWLP_USERDATA);
	mznContext* pState = (mznContext*)ptr;
	return pState;
}

LRESULT CALLBACK mzn_sys_event_callback(
		HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
  RECT wndRect;
	mznContext* pState;
	CREATESTRUCT* pCreate;
  int32 title = 22;
	int32 border = 4;
	i32 htMx = (i32)LOWORD(lParam);
  i32 htMy = (i32)HIWORD(lParam);
 	GetWindowRect(hwnd, &wndRect);
	if(msg == WM_CREATE) {
		pCreate = (CREATESTRUCT*)lParam;
		pState = (mznContext*)pCreate->lpCreateParams;
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pState);
	} else {
		pState = mzn_sys_get_context_ptr(hwnd);
	}
	if(pState) {
		title = pState->window->titleSize;
		border = pState->window->borderSize;
	}
	switch(msg) {
		case WM_KEYDOWN: {
			if (wParam == VK_ESCAPE) {
				PostQuitMessage(0);
      }
    	break;
		}
  	case(WM_NCHITTEST): {
    	htMx -= wndRect.left;
    	htMy -= wndRect.top;
    	if(1) {
      	if(htMx > (wndRect.right - wndRect.left) - border - title * 3
        	&& htMy < title) {
        	return HTCLIENT;
      	}
    	}
    	if(
      	htMx >= 0 &&
      	htMx <= wndRect.right - wndRect.left &&
      	htMy > 0 && htMy <= title) {
      	return HTCAPTION;
    	} else if (
      	htMx >= wndRect.right - wndRect.left - border * 2 &&
      	htMy >= wndRect.bottom - wndRect.top - border * 2) {
      	return HTBOTTOMRIGHT;
    	} else if(htMx >= wndRect.right - wndRect.left - border) {
      	return HTRIGHT;
    	} else if(htMy >= wndRect.bottom - wndRect.top - border) {
      	return HTBOTTOM;
    	} else if(
      	htMx < wndRect.right && htMx > wndRect.left &&
      	htMy < wndRect.bottom && htMy > wndRect.top) {
      	return HTCLIENT;
    	} else {
				break;
			}
  	}
    case WM_ERASEBKGND: {

			break;
		}
    case WM_DESTROY: {
      PostQuitMessage(0);
      break;
		}
    default: {
      return DefWindowProc(hwnd, msg, wParam, lParam);
		}
  }
  return 0;
}

MZNRET mzn_sys_window_blit(
		mznWindowContext* c, MZNPTR buffer, i32 srcWidth, i32 srcHeight) {
  RECT wRect;
  BITMAPINFO bitmapInfo;
  bitmapInfo.bmiHeader.biSize = sizeof(bitmapInfo.bmiHeader);
  bitmapInfo.bmiHeader.biWidth = srcWidth;
  bitmapInfo.bmiHeader.biHeight = -srcHeight;
  bitmapInfo.bmiHeader.biPlanes = 1;
  bitmapInfo.bmiHeader.biBitCount = 32;
  bitmapInfo.bmiHeader.biCompression = BI_RGB;
  if(!buffer) { return FALSE; }
  if(!GetWindowRect(c->hwnd, &wRect)) {
    MZN_LOG(LOG_ERROR, "GetWindowRect error: %ld", GetLastError());
  }
  if(StretchDIBits(
    GetDC(c->hwnd),
    0, 0, wRect.right - wRect.left, wRect.bottom - wRect.top, 0, 0,
    srcWidth, srcHeight, buffer,
    &bitmapInfo, DIB_RGB_COLORS, SRCCOPY) != 0) {
    return TRUE;
  }
  else {
    MZN_LOG(LOG_ERROR, "StretchDIBits error: %ld", GetLastError());
    Sleep(100);
    return FALSE;
  }
}

MZNPTR mzn_sys_window_create(mznWindowContext* c, void* data) {
	ATOM regRet;
	MZNPTR ret = NULL;
	MZNPTR instance = GetModuleHandle(NULL);
	int32 screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int32 screenHeight = GetSystemMetrics(SM_CYSCREEN);
	WNDCLASS wc = { 0 };
	wc.lpszClassName = c->title;
	wc.lpfnWndProc = mzn_sys_event_callback;
	wc.hInstance = instance;
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	regRet = RegisterClass(&wc);
  if(regRet) {
		ret = CreateWindow(
				c->title,
				c->title,
				WS_POPUP | WS_MINIMIZEBOX,
				screenWidth/2 - c->width/2,
				screenHeight/2 - c->height/2,
				c->width,
				c->height,
				0,
				0,
				instance,
				data);
	} else {
		MZN_LOG(LOG_ERROR, "Window registration Failed!");
		return FALSE;
	}
	ShowWindow(ret, SW_SHOW);
	UpdateWindow(ret);
  MZN_LOG(LOG_INFO, "Initialized window - %d x %d", c->width, c->height);
	return ret;
}

MZNRET mzn_sys_window_close(mznWindowContext* c) {
  if(c->hwnd) { DestroyWindow(c->hwnd); }
  return TRUE;
}

MZNRET mzn_sys_window_update(mznWindowContext* c) {
  MSG msg;
  DragAcceptFiles(c->hwnd, TRUE);
  while(PeekMessage(&msg, c->hwnd, 0, 0, PM_REMOVE)) {
    if(msg.message == WM_QUIT) {
			return FALSE;
		}
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
	UpdateWindow(c->hwnd);
  return msg.message != WM_QUIT;
}

MZNRET mzn_sys_window_minimize(mznWindowContext* c) {
  SendMessage(c->hwnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
  return TRUE;
}

MZNRET mzn_sys_window_restore(mznWindowContext* c) {
  SendMessage(c->hwnd, WM_SYSCOMMAND, SC_RESTORE, 0);
  return TRUE;
}

MZNRET mzn_sys_window_maximize(mznWindowContext* c) {
  SendMessage(c->hwnd, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
  return TRUE;
}

/* @PLATFORM-MEMORY-WIN32 ****************************************************/

MZNPTR mzn_sys_alloc(size_t size) {
  return VirtualAlloc(NULL, size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
}

MZNRET mzn_sys_free(MZNPTR base) {
  return VirtualFree(base, 0, MEM_RELEASE);
}

/* @PLATFORM-TIMING-WIN32 ****************************************************/

i64 mzn_sys_clock(void) {
  LARGE_INTEGER i;
  QueryPerformanceCounter(&i);
  return i.QuadPart;
}

i64 mzn_sys_clock_frequency(void) {
  LARGE_INTEGER i;
  QueryPerformanceFrequency(&i);
  return i.QuadPart;
}

/* @PLATFORM-FILES-WIN32 *****************************************************/

MZNRET mzn_sys_is_dir(const int8* path) {
  DWORD at = GetFileAttributesA(path);
  return (at != INVALID_FILE_ATTRIBUTES && (at & FILE_ATTRIBUTE_DIRECTORY));
}

MZNPTR mzn_sys_fopen(const i8* filename, const i8* fmt) {
  u32 type = GENERIC_READ;
  u32 cr = OPEN_EXISTING;
  i8 c = 0;
  while((c = *fmt++)) {
    switch (c) {
    case('w'): { type = GENERIC_WRITE; break; }
    case('r'): { type = GENERIC_READ; break; }
    case('*'): { type = GENERIC_READ | GENERIC_WRITE; break; }
    case('n'): { cr = CREATE_NEW; break; }
    case('a'): { cr = OPEN_ALWAYS; break; }
    case('e'): { cr = OPEN_EXISTING; break; }
    case('t'): { cr = TRUNCATE_EXISTING; break; }
    default: { break; }
    }
  }
  MZN_LOG(LOG_INFO, "Opening file: \"%s\"", filename);
  return CreateFile(filename, type, 0, 0, cr, FILE_ATTRIBUTE_NORMAL, NULL);
}

MZNRET mzn_sys_fclose(MZNPTR file) {
  return CloseHandle(file);
}

MZNRET mzn_sys_fread(
		MZNPTR file, MZNPTR mem, size_t len, size_t count) {
  ulong bytesRead = 0;
  ReadFile(file, mem, len * count, &bytesRead, NULL);
  if(bytesRead) {
    return len / bytesRead;
  }
  else {
    return 0;
  }
}

MZNRET mzn_sys_fwrite(MZNPTR file, MZNPTR mem, size_t len) {
  ulong bytesWrote = 0;
  WriteFile(file, mem, len, &bytesWrote, NULL);
  return bytesWrote;
}

MZNRET mzn_sys_fputc(void* handle, i8 c) {
  return WriteFile(handle, &c, 1, NULL, 0);
}

MZNRET mzn_sys_fputs(MZNPTR handle, const i8* str) {
  return WriteFile(handle, str, strlen(str), NULL, 0);
}

MZNRET mzn_sys_fputsn(MZNPTR handle, const i8* str, size_t len) {
  size_t slen = strlen(str);
  return WriteFile(handle, str, len < slen ? len : slen, NULL, 0);
}

MZNRET mzn_sys_putc(i8 c) {
  MZNPTR handle = GetStdHandle(STD_OUTPUT_HANDLE);
  return WriteConsole(handle, &c, 1, NULL, 0);
}

MZNRET mzn_sys_puts(const i8* str) {
  MZNPTR handle = GetStdHandle(STD_OUTPUT_HANDLE);
  return WriteConsole(handle, str, strlen(str), NULL, 0);
}

MZNRET mzn_sys_putsn(const i8* str, size_t len) {
  size_t slen = strlen(str);
  MZNPTR handle = GetStdHandle(STD_OUTPUT_HANDLE);
  return WriteConsole(handle, str, len < slen ? len : slen, NULL, 0);
}

MZNRET mzn_sys_scan_dir(const char *dir, PFFILELIST proc, void* args) {
  int32 i;
	int8 c;
	int8 spec[MAX_PATH];
  WIN32_FIND_DATAA fd;
	mznFileData* ud;
  HANDLE h;
	ULARGE_INTEGER ul;
	int32 len;
	int32 ext = TRUE;
 	int32 extLen = 0;
	mzn_snprintf(spec, sizeof(spec), sizeof(spec), "%s\\*", dir);
  if((h = FindFirstFileA(spec, &fd)) == INVALID_HANDLE_VALUE) { return FALSE; }
  do {
  	if((
					!strncmp(fd.cFileName, ".", 255) ||
					!strncmp(fd.cFileName, "..", 255))) {
			continue;
		}
		len = strnlen(fd.cFileName, MZN_FILE_DATA_MAX_NAME);
		ud = &MZN_FILE_DATA_SCRATCH[0];
		mzn_memset(ud, 0, sizeof(mznFileData));
		if(!len) { return FALSE; }
		for(i = len - 1; i >= 0; i++) {
			c = fd.cFileName[i];
			if(ext) {
				extLen++;
			} else {
				ud->filename[i] = c;
			}
			if(c == '.') {
				ext = FALSE;
			}
		}
		for(i = 0; i < extLen; i++) {
			ud->extension[i] = fd.cFileName[len - extLen];
		}
		if(fd.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY) {
      ud->attributes |= MZN_IS_DIR;
		} else {
      ud->attributes |= MZN_IS_FILE;
		}
		ul.LowPart = fd.ftLastWriteTime.dwLowDateTime;
		ul.HighPart = fd.ftLastWriteTime.dwHighDateTime;
		ud->timeLastModified = ul.QuadPart;
		ul.LowPart = fd.ftCreationTime.dwLowDateTime;
		ul.HighPart = fd.ftCreationTime.dwHighDateTime;
		ud->timeCreated = ul.QuadPart;
		if(proc) { proc(ud, args); }
		mzn_memset(ud, 0, sizeof(mznFileData));
  } while (FindNextFileA(h, &fd));
	FindClose(h);
	return TRUE;
}

/* @PLATFORM-AUDIO-WIN32 *****************************************************/

MZNRET mzn_sys_audio_init(mznAudioContext* context) {
	HRESULT hr;
	if(!context) { return MZN_ERROR; }
	mzn_memset(context, 0, sizeof(mznAudioContext));
	/* Initialize COM. */
	hr = CoInitialize(NULL);
	if(FAILED(hr)) { return MZN_ERROR; }
	/* Create device enumerator. */
	hr = CoCreateInstance(&CLSID_MMDeviceEnumerator, NULL, CLSCTX_ALL,
		&IID_IMMDeviceEnumerator, (void**)&context->deviceEnum);
	if(FAILED(hr)) {
		CoUninitialize();
		return MZN_ERROR;
	}
	/* Get the default audio endpoint (render, console). */
	hr = context->deviceEnum->lpVtbl->GetDefaultAudioEndpoint(
			context->deviceEnum, eRender, eConsole, &context->device);
	if(FAILED(hr)) {
		MZN_AUD_SAFE_RELEASE(context->deviceEnum);
		CoUninitialize();
		return MZN_ERROR;
	}
	/* Activate the IAudioClient interface on the endpoint. */
	hr = context->device->lpVtbl->Activate(
			context->device,
			&IID_IAudioClient,
			CLSCTX_ALL,
			NULL,
			(void**)&context->client);
	if(FAILED(hr)) {
		MZN_AUD_SAFE_RELEASE(context->device);
		MZN_AUD_SAFE_RELEASE(context->deviceEnum);
		CoUninitialize();
		return MZN_ERROR;
	}
	/* Get the device's mix format. */
	hr = context->client->lpVtbl->GetMixFormat(context->client, &context->pwfx);
	if(FAILED(hr)) {
		MZN_AUD_SAFE_RELEASE(context->client);
		MZN_AUD_SAFE_RELEASE(context->device);
		MZN_AUD_SAFE_RELEASE(context->deviceEnum);
		CoUninitialize();
		return MZN_ERROR;
	}
	/* Determine the audio format. */
	if(context->pwfx->wFormatTag == WAVE_FORMAT_EXTENSIBLE) {
		WAVEFORMATEXTENSIBLE *wfex = (WAVEFORMATEXTENSIBLE*)context->pwfx;
		if(IsEqualGUID(&wfex->SubFormat, &KSDATAFORMAT_SUBTYPE_PCM)) {
			context->format.type = MZN_AUDIO_PCM;
			context->format.bitRate = wfex->Format.wBitsPerSample;
		} else if(IsEqualGUID(
					&wfex->SubFormat, &KSDATAFORMAT_SUBTYPE_IEEE_FLOAT)) {
			context->format.type = MZN_AUDIO_FLOAT;
			context->format.bitRate = 32;
		} else {
			MZN_AUD_SAFE_RELEASE(context->client);
			MZN_AUD_SAFE_RELEASE(context->device);
			MZN_AUD_SAFE_RELEASE(context->deviceEnum);
			CoTaskMemFree(context->pwfx);
			CoUninitialize();
			return MZN_ERROR;
		}
	} else if(context->pwfx->wFormatTag == WAVE_FORMAT_IEEE_FLOAT) {
		context->format.type = MZN_AUDIO_FLOAT;
		context->format.bitRate = 32;
	} else if(context->pwfx->wFormatTag == WAVE_FORMAT_PCM) {
		context->format.type = MZN_AUDIO_PCM;
		context->format.bitRate = context->pwfx->wBitsPerSample;
	} else {
		MZN_AUD_SAFE_RELEASE(context->client);
		MZN_AUD_SAFE_RELEASE(context->device);
		MZN_AUD_SAFE_RELEASE(context->deviceEnum);
		CoTaskMemFree(context->pwfx);
		CoUninitialize();
		return MZN_ERROR;
	}
	context->format.channels = context->pwfx->nChannels;
	context->format.sampleRate = context->pwfx->nSamplesPerSec;
	/* Initialize the audio client in shared mode with a 1-second buffer. */
	hr = context->client->lpVtbl->Initialize(context->client,
		AUDCLNT_SHAREMODE_SHARED, 0, 10000000, 0, context->pwfx, NULL);
	if(FAILED(hr)) {
		MZN_AUD_SAFE_RELEASE(context->client);
		MZN_AUD_SAFE_RELEASE(context->device);
		MZN_AUD_SAFE_RELEASE(context->deviceEnum);
		CoTaskMemFree(context->pwfx);
		CoUninitialize();
		return LOG_ERROR;
	}
	hr = context->client->lpVtbl->GetBufferSize(
			context->client, &context->bufferFrameCount);
	if(FAILED(hr)) {
		MZN_AUD_SAFE_RELEASE(context->client);
		MZN_AUD_SAFE_RELEASE(context->device);
		MZN_AUD_SAFE_RELEASE(context->deviceEnum);
		CoTaskMemFree(context->pwfx);
		CoUninitialize();
		return MZN_ERROR;
	}
	hr = context->client->lpVtbl->GetService(context->client,
		&IID_IAudioRenderClient, (void**)&context->clientRender);
	if(FAILED(hr)) {
		MZN_AUD_SAFE_RELEASE(context->client);
		MZN_AUD_SAFE_RELEASE(context->device);
		MZN_AUD_SAFE_RELEASE(context->deviceEnum);
		CoTaskMemFree(context->pwfx);
		CoUninitialize();
		return MZN_ERROR;
	}
	hr = context->client->lpVtbl->Start(context->client);
	if(FAILED(hr)) {
		MZN_AUD_SAFE_RELEASE(context->clientRender);
		MZN_AUD_SAFE_RELEASE(context->client);
		MZN_AUD_SAFE_RELEASE(context->device);
		MZN_AUD_SAFE_RELEASE(context->deviceEnum);
		CoTaskMemFree(context->pwfx);
		CoUninitialize();
		return MZN_ERROR;
	}
	return TRUE;
}

MZNRET mzn_sys_audio_finalize(mznAudioContext* context) {
	if(!context) { return FALSE; }
	if(context->client) {
		context->client->lpVtbl->Stop(context->client);
	}
	if(context->pwfx) {
		CoTaskMemFree(context->pwfx);
	}
	MZN_AUD_SAFE_RELEASE(context->clientRender);
	MZN_AUD_SAFE_RELEASE(context->client);
	MZN_AUD_SAFE_RELEASE(context->device);
	MZN_AUD_SAFE_RELEASE(context->deviceEnum);
	CoUninitialize();
	return TRUE;
}

MZNRET mzn_sys_audio_internal_update(
		mznAudioContext* c, void* b, uint32 f, PFAUDIOPROC p, void* d);
MZNRET mzn_sys_audio_internal_update(
		mznAudioContext* context, void* buffer, uint32 frames,
		PFAUDIOPROC proc, void* data) {
	uint32 j;
	uint8* sample;
  if(proc) {
  	sample = (uint8*)buffer;
  	for(j = 0; j < frames; j++) {
			proc(sample, context->format, data);
    	sample += context->format.channels * (context->format.bitRate / 8);
			context->globalPhase +=
				2 * 3.14159265358979323846 / context->format.sampleRate;
			context->playbackCursor++;
  	}
		return TRUE;
	} else {
		return FALSE;
	}
}

MZNRET mzn_sys_audio_update(
		mznAudioContext* context, PFAUDIOPROC proc, void* data) {
	HRESULT hr;
	UINT32 framesToWrite;
	UINT32 padding;
	BYTE* pData;
	if(!context) { return MZN_ERROR; }
	hr = S_OK;
	padding = 0;
	hr = context->client->lpVtbl->GetCurrentPadding(context->client, &padding);
	if(FAILED(hr)) { return MZN_ERROR; }
	if(context->bufferFrameCount > padding) {
		framesToWrite = context->bufferFrameCount - padding;
		pData = NULL;
		hr = context->clientRender->lpVtbl->GetBuffer(
				context->clientRender, framesToWrite, &pData);
		if(FAILED(hr)) { return MZN_ERROR; }
		/* Invoke the user callback to fill the buffer. */
		mzn_sys_audio_internal_update(context, pData, framesToWrite, proc, data);
		hr = context->clientRender->lpVtbl->ReleaseBuffer(
				context->clientRender, framesToWrite, 0);
		if(FAILED(hr)) { return MZN_ERROR; }
	}
	return TRUE;
}

MZNRET mzn_sys_audio_play(mznAudioContext* context) {
  return context->client->lpVtbl->Start(context->client);
}

MZNRET mzn_sys_audio_stop(mznAudioContext* context) {
  return context->client->lpVtbl->Stop(context->client);
}

#endif /* MZN_LIB_IMPLEMENTATION */

/* @LIB-STDLIB ***************************************************************/

/* @LIB-STDLIB-INTERFACE *****************************************************/

r64 mzn_pow(i32 b, i32 e);
r32 mzn_round(r32 n, i32 p);
r64 mzn_fac(i32 n);
r64 mzn_powf(double x, int n);
r32 mzn_cos(r32 x);
r32 mzn_sin(r32 x);
r64 mzn_fma(r64 a, r64 b, r64 s);
r64 mzn_copysign(r64 a, r64 b);
r64 mzn_atan(r64 x);
r64 mzn_tan(double x);
r32 mzn_atan2(r32 y, r32 x);
r64 mzn_exp(r64 x);
r64 mzn_log(r64 x);
r64 mzn_sqrt(r64 x);

i32 mzn_memclr(void* mem, size_t size);
i32 mzn_memset(void* mem, u8 v, size_t size);
i32 mzn_memcpy(void* dst, size_t dstSize, void* src, size_t srcSize);

size_t mzn_strlen(const i8* str);
i32 mzn_strcmp(const i8* s1, const i8* s2);
i8* mzn_strcpy(i8* dest, size_t size, const i8* src);
i8* mzn_strncpy(i8* dest, size_t size, const i8* src, size_t max);
i8* mzn_strchr(const i8* str, int32 c);
i8* mzn_strrchr(const i8* str, int32 c);
i8* mzn_strrev(i8* str);

i32 mzn_is_alpha(const i8 c);
i32 mzn_is_numeric(const i8 c);
i32 mzn_is_hex(const i8 c);
i32 mzn_is_whitespace(int8 c);
i32 mzn_is_whitespace_ex(int8 c);
i32 mzn_is_alphanumeric(const i8 c);
i32 mzn_is_readable(const i8 c);
i32 mzn_is_readable_ex(const i8 c);

i32 mzn_nlen(i32 n, i32 base);

i32 mzn_ftoa(real32 fr, int32 prec, i8* buf, size_t size);
i32 mzn_dtoa(real64 fr, int32 prec, i8* buf, size_t size);
i32 mzn_itoa(i32 num, i32 base, i32 lower, i8* buf, size_t size);

r32 mzn_atof(const i8* s);
i32 mzn_atoi(const i8* s);
i32 mzn_xtoi(const i8* s);
u32 mzn_cxtou(i8 chr);

i32 mzn_putc(i8 c);
i32 mzn_puts(const i8* str);
i32 mzn_putsn(const i8* str, size_t len);

i32 mzn_fputc(void* handle, i8 c);
i32 mzn_fputs(void* handle, const i8* str);
i32 mzn_fputsn(void* handle, const i8* str, size_t len);

i8* mzn_sputc(i8* mem, i8 c);
i8* mzn_sputs(i8* mem, size_t len, const i8* str);
i8* mzn_sputsn(i8* mem, size_t s, const i8* str, u32 len);

i32 mzn_vsprintf(i8* dest, size_t len, const i8* format, va_list* args);
i32 mzn_vsnprintf(i8* dst, size_t len, size_t n, const i8* fmt, va_list args);
i32 mzn_vprintf(const i8* format, va_list* args);
i32 mzn_sprintf(i8* dest, size_t len, const i8* format, ...);
i32 mzn_printf(const i8* format, ...);
i32 mzn_vfprintf(void* dest, const i8* format, va_list* args);
i32 mzn_fprintf(void* dest, const i8* format, ...);

/* @LIB-STDLIB-IMPLEMENTATION ************************************************/

#ifdef MZN_LIB_IMPLEMENTATION

int32 mzn_memclr(void* mem, size_t size) {
	uint8* at = NULL;
	size_t i = 0;
	if(mem) {
		at = (uint8*)mem;
		while(i++ < size) { *at++ = 0; }
		return TRUE;
	} else {
		return FALSE;
	}
}

int32 mzn_memset(void* mem, u8 v, size_t size) {
	uint8* at = NULL;
	size_t i = 0;
	if(mem) {
		at = (uint8*)mem;
		while(i++ < size) { *at++ = v; }
		return TRUE;
	} else {
		return FALSE;
	}
}

int32 mzn_memcpy(void* dest, size_t destSize, void* src, size_t srcSize) {
	uint8* atSrc = NULL;
	uint8* atDest = NULL;
	size_t i = 0;
	if(src && dest && destSize >= srcSize) {
		atSrc = (uint8*)src;
		atDest = (uint8*)dest;
		while(i++ < destSize) { *atDest++ = *atSrc++; }
		return TRUE;
	} else {
		return FALSE;
	}
}

static int round_nearest(double x) {
	int i = (int)x;  /* Truncate toward zero */
	if (x >= 0.0) {
		if ((x - i) >= 0.5) { return i + 1; } else { return i; }
	} else {
		if ((-x + i) >= 0.5) { return i - 1; } else { return i; }
	}
}

static void reduce_to_pi_over_2(double x, int *n, double *r) {
	double k = x * MZN_2_OVER_PI;
	*n = round_nearest(k);
	*r = x - (*n) * MZN_PI_OVER_2;
}

static double sin_poly(double r) {
	const double r2 = r * r;
	const double S1 = -1.66666666666666324348e-01;
	const double S2 =  8.33333333332248946124e-03;
	const double S3 = -1.98412698298579493134e-04;
	const double S4 =  2.75573137070700676789e-06;
	const double S5 = -2.50507602534068634195e-08;
	const double S6 =  1.58969099521155010221e-10;
	return r + r*r2*(S1 + r2*(S2 + r2*(S3 + r2*(S4 + r2*(S5 + r2*S6)))));
}

static double cos_poly(double r) {
	double r2 = r * r;
	const double C1 = -0.5;
	const double C2 =  4.16666666666666019037e-02;
	const double C3 = -1.38888888888741095749e-03;
	const double C4 =  2.48015872894767294178e-05;
	const double C5 = -2.75573143513906633035e-07;
	const double C6 =  2.08757232129817482790e-09;
	return 1.0 + r2 *(C1 + r2*(C2 + r2*(C3 + r2*(C4 + r2*(C5 + r2*C6)))));
}

double mzn_sind(double x) {
	int quadrant;
	double r, result;
	if (x != x) { return x; }
	reduce_to_pi_over_2(x, &quadrant, &r);
	quadrant = quadrant & 3;  /* equivalent to quadrant mod 4 */
	switch (quadrant) {
		case 0:
			result = sin_poly(r);
			break;
		case 1:
			result = cos_poly(r);
			break;
		case 2:
			result = - sin_poly(r);
			break;
		case 3:
			result = - cos_poly(r);
			break;
		default:
			result = 0.0;
			break;
	}
	return result;
}

double mzn_cosd(double x) {
	int quadrant;
	double r, result;
	if (x != x) { return x; }
	reduce_to_pi_over_2(x, &quadrant, &r);
	quadrant = quadrant & 3;  /* quadrant mod 4 */

	switch (quadrant) {
		case 0:
			result = cos_poly(r);
			break;
		case 1:
			result = - sin_poly(r);
			break;
		case 2:
			result = - cos_poly(r);
			break;
		case 3:
			result = sin_poly(r);
			break;
		default:
			result = 0.0;
			break;
	}
	return result;
}

real32 mzn_sin(real32 x) { return (real32)mzn_sind((real32)x); }
real32 mzn_cos(real32 x) { return (real32)mzn_cosd((real32)x); }

int32 mzn_strcmp(const char* p1, const char* p2) {
  register const uint8* s1 = (const uint8*) p1;
  register const uint8* s2 = (const uint8*) p2;
  uint8 c1, c2;
  do {
		c1 = (uint8)*s1++;
    c2 = (uint8)*s2++;
    if(c1 == '\0') { return c1 - c2; }
  } while(c1 == c2);
  return c1 - c2;
}

int8* mzn_strcpy(char *dest, size_t size, const char *src) {
  size_t i;
  if(size != 0 && src != NULL && dest != NULL) {
	  for(i = 0; i < size - 1 && src[i] != '\0'; i++) { dest[i] = src[i]; }
  	dest[i] = '\0';
	}
  return dest;
}

int8* mzn_strncpy(char *dest, size_t size, const char *src, size_t max) {
  size_t i;
	size_t n = size < max ? size : max;
	if(max > 0 && size > 0 && src != NULL && dest != NULL) {
	  for(i = 0; i < n - 1 && src[i] != '\0'; i++) { dest[i] = src[i]; }
  	dest[i] = '\0';
	}
  return dest;
}

size_t mzn_strlen(const char* str) {
	size_t len = 0;
	if(str != NULL) {
		while(*str++ != '\0') {
			if((len = len + 1) >= MZN_MAX_STRING) { return 0; }
		}
	}
	return len;
}


int8* mzn_strchr(const char* s, int32 c) {
	char ch = (char)c;
	size_t len = 0;
	if(s != NULL) {
		while(*s != '\0') {
    	if(*s == ch) { return (char*)s; }
			if((len = len + 1) >= MZN_MAX_STRING) { return 0; }
    	s++;
  	}
  	if(ch == '\0') { return (char*)s; }
 	}
  return NULL;
}

int8* mzn_strrchr(const char* s, int32 c) {
	size_t len = 0;
  char* last = NULL;
  char ch = (char)c;
  /* Iterate through the string */
  while(*s) {
    if(*s == ch) { last = (char*)s; }
		if((len = len + 1) >= MZN_MAX_STRING) { return NULL; }
    s++;
  }
  if(ch == '\0') { return (char*)s; }
  return last;
}

int8* mzn_strrev(char *str) {
  int32 i, j;
  char temp;
  if(str != NULL) {
    j = mzn_strlen(str) - 1;
    i = 0;
    while(i < j) {
      temp = str[i];
      str[i] = str[j];
      str[j] = temp;
      i++;
      j--;
    }
  }
  return str;
}

i32 mzn_is_whitespace_ex(int8 c) {
  return (c != '\0' && c <= ' ') || (c == (char)0x7F);
}

i32 mzn_is_whitespace(int8 c) {
    return (c == ' ' || c == '\t' || c == '\n' ||
            c == '\v' || c == '\f' || c == '\r');
}

i32 mzn_is_alpha(const i8 c) {
	return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

i32 mzn_is_numeric(const i8 c) {
	return (c >= '0' && c <= '9');
}

i32 mzn_is_alphanumeric(const i8 c) {
	return mzn_is_alpha(c) || mzn_is_numeric(c);
}

i32 mzn_is_readable(const i8 c) {
	return (c >= ' ' && c <= '~');
}

i32 mzn_is_readable_ex(const i8 c) {
	return (c >= ' ' && c <= '~') || ((u8)c >= 0x80 && (u8)c <= 0xFE);
}

i32 mzn_is_hex(const i8 c) {
  return
    (c >= '0' && c <= '9') ||
    (c >= 'a' && c <= 'f') ||
    (c >= 'A' && c <= 'F');
}

u32 mzn_cxtou(i8 chr) {
  if(mzn_is_numeric(chr)) { return chr - '0'; }
  else if(chr >= 'A') { return chr - 'A' + 10; }
  else if(chr >= 'a') { return chr - 'a' + 10; }
  return 0;
}

i32 mzn_nlen(i32 n, i32 base) {
    i32 i = 0;
    if (base < 2) { return 0; }
    if (n == 0) { return 1; }
    if(n < 0) {
			n = -n;
			i++;
		}
    while(n != 0) {
    	n /= base;
      i++;
    }
    return i;
}

#define MZN_TOA_INT_BUF_SIZE 32
#define MZN_TOA_BASE_10 10.0
#define MZN_TOA_ROUNDING_FACTOR 0.5
#define MZN_TOA_ZERO_CHAR '0'
#define MZN_TOA_DECIMAL_POINT '.'
#define MZN_TOA_LOWERCASE_OFFSET ('a' - 10)
#define MZN_TOA_UPPERCASE_OFFSET ('A' - 10)

int32 mzn_dtoa(real64 n, int32 prec, int8* res, size_t size) {
  int32 i, j, k, digit;
  int32 precision = prec;
  int8 *ptr = res;
  uint32 intPart;
  real64 fraction, rounding;
  int8 intStr[MZN_TOA_INT_BUF_SIZE];
  if(!size || res == NULL || size + 1 < (size_t)precision) { return 0; }
  if(n < 0) {
    *ptr++ = '-';
    n = -n;
  }
  rounding = MZN_TOA_ROUNDING_FACTOR;
  for(i = 0; i < precision; i++){
    rounding /= MZN_TOA_BASE_10;
  }
  n += rounding;
  intPart = (uint32)n;
  fraction = n - (real64)intPart;
  k = 0;
  if(intPart == 0){
    intStr[k++] = MZN_TOA_ZERO_CHAR;
  } else{
    while(intPart > 0){
      intStr[k++] = (int8)(MZN_TOA_ZERO_CHAR + (intPart % 10));
      intPart /= 10;
    }
    for(i = 0, j = k -1; i < j; i++, j--){
      int8 tmp = intStr[i];
      intStr[i] = intStr[j];
      intStr[j] = tmp;
    }
  }
  intStr[k] = '\0';
  for(i = 0; intStr[i] != '\0'; i++) { *ptr++ = intStr[i]; }
  *ptr++ = MZN_TOA_DECIMAL_POINT;
  for(i = 0; i < precision; i++){
    fraction *= MZN_TOA_BASE_10;
    digit = (int32)fraction;
    *ptr++ = (int8)(MZN_TOA_ZERO_CHAR + digit);
    fraction -= digit;
  }
  *ptr = '\0';
	return precision;
}

int32 mzn_ftoa(real32 n, int32 prec, int8* res, size_t size) {
  int32 i, j, k, digit;
  int32 precision = prec;
  int8 *ptr = res;
  uint32 intPart;
  real32 fraction, rounding;
  int8 intStr[MZN_TOA_INT_BUF_SIZE];
  if(!size || res == NULL || size + 1 < (size_t)precision) { return 0; }
	if(n < 0) {
    *ptr++ = '-';
    n = -n;
  }
  rounding = MZN_TOA_ROUNDING_FACTOR;
  for(i = 0; i < precision; i++){
    rounding /= MZN_TOA_BASE_10;
  }
  n += rounding;
  intPart = (uint32)n;
  fraction = n - (real32)intPart;
  k = 0;
  if(intPart == 0) {
    intStr[k++] = MZN_TOA_ZERO_CHAR;
  } else {
    while(intPart > 0) {
      intStr[k++] = (int8)(MZN_TOA_ZERO_CHAR + (intPart % 10));
      intPart /= 10;
    }
    for(i = 0, j = k -1; i < j; i++, j--){
      int8 tmp = intStr[i];
      intStr[i] = intStr[j];
      intStr[j] = tmp;
    }
  }
  intStr[k] = '\0';
  for(i = 0; intStr[i] != '\0'; i++) { *ptr++ = intStr[i]; }
  *ptr++ = MZN_TOA_DECIMAL_POINT;
  for(i = 0; i < precision; i++){
    fraction *= MZN_TOA_BASE_10;
    digit = (int32)fraction;
    *ptr++ = (int8)(MZN_TOA_ZERO_CHAR + digit);
    fraction -= digit;
  }
  *ptr = '\0';
	return precision;
}

int32 mzn_itoa(i32 num, i32 base, i32 lowercase, i8* str, size_t size){
  i8 tmp[MZN_TOA_INT_BUF_SIZE];
  i32 i, k, sign;
  u32 v;
	if(!size || str == NULL) { return 0; }
	if(base < 2 || base > 36){
    str[0] = '\0';
    return 0;
  }
  sign = (base == MZN_TOA_BASE_10 && num < 0);
  if(sign){ v = (u32)(-num); }
  else { v = (u32)num; }
  k = 0;
  while(v || k == 0) {
    i = (i32)(v % base);
    v /= base;
    if(i < 10) {
      tmp[k++] = (i8)(MZN_TOA_ZERO_CHAR + i);
    } else {
      tmp[k++] =
				(lowercase ?
				(i8)MZN_TOA_LOWERCASE_OFFSET :
				(i8)MZN_TOA_UPPERCASE_OFFSET) + i;
    }
  }
  i = 0;
  if(sign){ str[i++] = '-'; }
  while(k > 0 && (size_t)i < size - 1) { str[i++] = tmp[--k]; }
  str[i] = '\0';
  return i;
}

int32 mzn_atoi(const int8* str) {
	int32 digit;
	int32 sign = 1;
	int64 result = 0;
	int64 limit = (sign == 1) ? INT32_MAX : ((int64)INT32_MAX + 1);
	if(str == NULL) { return 0; }
	while(*str != '\0' && mzn_is_whitespace((uint8)*str)) { str++; }
	if(*str == '-' || *str == '+') {
		if(*str == '-') {
			sign = -1;
		}
		str++;
	}
	while(*str && mzn_is_numeric((uint8)*str)) {
		digit = *str - '0';
		if(result > limit / 10 || (result == limit / 10 && digit > limit % 10)) {
			return (sign == 1) ? INT32_MAX : INT32_MIN;
		}
		result = result * 10 + digit;
		str++;
	}
  return (int32)(sign * result);
}

i32 mzn_xtoi(const i8* s) {
  i64 r = 0;
  while(mzn_is_whitespace(*s)) { s++; }
  while(mzn_is_hex(*s) || *s == 'x' || *s == 'X') {
    if(*s == 'x' || *s == 'X') {
      r = 0;
    } else {
      r = r * 16 + mzn_cxtou(*s);
    }
    s++;
  }
  return (i32)r;
}

r32 mzn_atof(const i8* s) {
  r32 r = 0.0;
	r32 frac = 1.0;
  i32 sign = 1;
  while(mzn_is_whitespace(*s)) { s++; };
  if(*s == '-' || *s == '+') { sign = (*s++ == '-') ? -1 : 1; };
  while(mzn_is_numeric(*s)) { r = r * 10.0 + (*s++ - '0'); };
  if(*s == '.') {
    s++;
    while(mzn_is_numeric(*s)) {
      r = r * 10.0 + (*s++ - '0');
      frac *= 10.0;
    }
  }
  return sign * (r / frac);
}

i32 mzn_putc(i8 c) {
	return mzn_sys_putc(c);
}

i32 mzn_puts(const i8* str) {
	return mzn_sys_puts(str);
}

i32 mzn_putsn(const i8* str, size_t len) {
	return mzn_sys_putsn(str, len);
}

i32 mzn_fputc(void* handle, i8 c) {
	return mzn_sys_fputc(handle, c);
}

i32 mzn_fputs(void* handle, const i8* str) {
	return mzn_sys_fputs(handle, str);
}

i32 mzn_fputsn(void* handle, const i8* str, size_t len) {
	return mzn_sys_fputsn(handle, str, len);
}

i8* mzn_sputc(i8* mem, i8 c) {
	if(mem) { *mem = c; }
	return mem;
}

i8* mzn_sputs(i8* mem, size_t len, const i8* str) {
	return mzn_strcpy(mem, len, str);
}

i8* mzn_sputsn(i8* mem, size_t s, const i8* str, u32 len) {
	return mzn_strncpy(mem, s, str, len);
}

/*----------------------------------------------------------------------------
  Format String Parser/Printer Implementation
----------------------------------------------------------------------------*/

/* Forward declaration of mznFormatStringContext */
typedef struct mznFormatStringContext_t mznFormatStringContext;

/* Function pointer type for a format-specifier callback */
typedef size_t (*PFFORMATSPEC)
	(mznFormatStringContext *ctx, char *buf, size_t len, va_list *lst);

typedef struct mznFormatStringSpecifier_t {
  int8 symbol;
  PFFORMATSPEC proc;
} mznFormatStringSpecifier;

struct mznFormatStringContext_t {
  char *buffer;
  mznFormatStringSpecifier *specifiers;
  size_t bufferMax;
  size_t bufferCount;
  size_t specifierCount;
  size_t specifierMax;
  int32 truncate;
	int32 leftAlign;
  int32 zeroPad;
  int32 width;
  int32 precision;
};

int32 mzn_format_string_context_init(
		mznFormatStringContext *ctx,
		void *textMem, size_t textMemSize, void *specMem, size_t specMemSize) {
  mzn_memclr(ctx, sizeof(mznFormatStringContext));
  ctx->specifiers = specMem;
  ctx->specifierMax = specMemSize / sizeof(mznFormatStringSpecifier);
  ctx->specifierCount = 0;
  ctx->buffer = textMem;
  ctx->bufferMax = textMemSize;
  ctx->bufferCount = 0;
  return TRUE;
}

int32 mzn_format_string_register_specifier(
		mznFormatStringContext *ctx, int8 symbol, PFFORMATSPEC proc) {
  if(ctx->specifierCount < ctx->specifierMax) {
    ctx->specifiers[ctx->specifierCount].proc = proc;
    ctx->specifiers[ctx->specifierCount].symbol = symbol;
    ctx->specifierCount++;
    return TRUE;
  } else {
    return FALSE;
  }
}

typedef struct mznParser_t {
  const char *root;
  size_t cur;
  size_t max;
} mznParser;

mznParser mzn_parser_create(const char *str, size_t max) {
  mznParser parser;
  parser.root = str;
  parser.cur = 0;
  parser.max = max;
  return parser;
}

char mzn_parser_at(mznParser *p) {
  if(p->cur < p->max)
    return p->root[p->cur];
  return '\0';
}

char mzn_parser_next(mznParser *p) {
  if(p->cur < p->max)
    return p->root[p->cur++];
  return '\0';
}

char mzn_parser_peek(mznParser *p) {
  if(p->cur + 1 < p->max)
    return p->root[p->cur + 1];
  return '\0';
}

const char *mzn_parser_at_raw(mznParser *p) {
  return &p->root[p->cur];
}

int32 mzn_parser_copy_to(mznParser *p, char *buf, size_t size, char sym) {
  int32 count = 0;
  char c;
  c = mzn_parser_at(p);
  while(c != '\0' && c != sym && count < (int)size - 1) {
    buf[count++] = c;
    mzn_parser_next(p);
    c = mzn_parser_at(p);
  }
  buf[count] = '\0';
  return count;
}

int32 mzn_is_format_flag(char c) {
  return (c == '-' || c == '0');
}

size_t mzn_apply_padding(
		mznFormatStringContext *ctx, const char *str, char *buf, size_t max) {
  size_t len;
  int width;
  int padLen;
  size_t count;
  char padChar;
  size_t i;
  int j;
  len = mzn_strlen(str);
  width = ctx->width;
  if(width <= (int)len || max <= len) {
    for(i = 0; i < len && i < max - 1; i++) {
      buf[i] = str[i];
    }
    buf[i] = '\0';
    return i;
  }
  padLen = width - (int)len;
  count = 0;
  padChar = (ctx->zeroPad && !ctx->leftAlign) ? '0' : ' ';
  if(ctx->leftAlign) {
    for(i = 0; i < len && count < max - 1; i++, count++) {
      buf[count] = str[i];
    }
    for(j = 0; j < padLen && (int)count < (int)max - 1; j++, count++) {
      buf[count] = padChar;
    }
  } else {
    for(j = 0; j < padLen && (int)count < (int)max - 1; j++, count++) {
      buf[count] = padChar;
    }
    for(i = 0; i < len && count < max - 1; i++, count++) {
      buf[count] = str[i];
    }
  }
  buf[count] = '\0';
  return count;
}

int32 mzn_parser_copy_var(
		mznFormatStringContext *ctx,
		mznParser *p, char *buf, size_t size, va_list *args) {
  char c;
  int32 i;
	int32 count = 0;
  int32 left = FALSE;
  int32 pad = FALSE;
  int32 width = 0;
  int32 precision = -1;
  size_t specResult = 0;
  int found = FALSE;
  ctx->precision = -1;
	ctx->width = -1;
  ctx->truncate = FALSE;
	ctx->leftAlign = FALSE;
	ctx->zeroPad = FALSE;
	while(1) {
    c = mzn_parser_at(p);
    if(c == '-') {
      left = TRUE;
      mzn_parser_next(p);
    } else if(c == '0') {
      pad = TRUE;
      mzn_parser_next(p);
    } else {
      break;
    }
  }
  c = mzn_parser_at(p);
  if(c == '*') {
    mzn_parser_next(p);
    width = va_arg(*args, int);
  } else if(c >= '0' && c <= '9') {
    width = mzn_atoi(mzn_parser_at_raw(p));
    while(mzn_parser_at(p) >= '0' && mzn_parser_at(p) <= '9')
      mzn_parser_next(p);
  }
  c = mzn_parser_at(p);
  if(c == '.') {
		ctx->truncate = TRUE;
    mzn_parser_next(p);
    c = mzn_parser_at(p);
    if(c == '*') {
      mzn_parser_next(p);
      precision = va_arg(*args, int);
    } else if(c >= '0' && c <= '9') {
      precision = mzn_atoi(mzn_parser_at_raw(p));
      while(mzn_parser_at(p) >= '0' && mzn_parser_at(p) <= '9')
        mzn_parser_next(p);
    } else {
      precision = 0;
    }
  }
  c = mzn_parser_at(p);
  if(c == 'l' || c == 'h') {
    mzn_parser_next(p);
    if(c == 'l' && mzn_parser_at(p) == 'l')
      mzn_parser_next(p);
  }
  c = mzn_parser_next(p);
  for(i = 0; i < (int32)ctx->specifierCount; i++) {
    if(ctx->specifiers[i].symbol == c) {
      ctx->width = width > 0 ? width : 0;
      ctx->precision = precision >= 0 ? precision : 6;
      ctx->leftAlign = left;
      ctx->zeroPad = pad;
      specResult = ctx->specifiers[i].proc(ctx, buf, size, args);
      found = TRUE;
      break;
    }
  }
  if(!found) {
    if(size > 2) {
      buf[0] = '%';
      buf[1] = c;
      buf[2] = '\0';
      count = 2;
    }
  } else {
    count = specResult;
  }
  return count;
}

int32 mzn_parse_format_string(
		mznFormatStringContext *ctx,
		char *dest, size_t size, size_t max, const char *fmt, va_list *args) {
  char c = 0;
  size_t len;
  mznParser parser;
  int32 count = 0;
  int32 n = max < size ? max : size;
  len = mzn_strlen(fmt);
  parser = mzn_parser_create(fmt, len);
  while((c = mzn_parser_at(&parser)) != '\0' && count < n) {
    if(c == '%') {
      mzn_parser_next(&parser);
      if(mzn_parser_at(&parser) == '%') {
        mzn_parser_next(&parser);
        if(count < n - 1) {
          dest[count++] = '%';
        }
      } else {
        count +=
					mzn_parser_copy_var(ctx, &parser, &dest[count], n - count, args);
      }
    } else {
      count += mzn_parser_copy_to(&parser, &dest[count], n - count, '%');
    }
  }
  if(count < n) {
    dest[count] = '\0';
	} else if(n > 0) {
    dest[n - 1] = '\0';
	}
  return count;
}

int32 mzn_internal_vsnprintf(
		mznFormatStringContext *ctx,
		char *buf, size_t size, size_t max, const char *fmt, va_list *args) {
  return mzn_parse_format_string(ctx, buf, size, max, fmt, args);
}

int32 mzn_write(const char *str, size_t size) {
  size_t i;
  for(i = 0; i < size && str[i] != '\0'; i++)
    mzn_sys_putc(str[i]);
  return TRUE;
}

size_t mzn_format_int(
		mznFormatStringContext *ctx, char *buf, size_t max, va_list *args) {
  char tmp[64];
  size_t res;
  mzn_itoa(va_arg(*args, int), 10, 1, tmp, sizeof(tmp));
  res = mzn_apply_padding(ctx, tmp, buf, max);
  return res;
}

size_t mzn_format_hex_lower(
		mznFormatStringContext *ctx, char *buf, size_t max, va_list *args) {
  char tmp[64];
  size_t res;
  mzn_itoa(va_arg(*args, int), 16, 1, tmp, sizeof(tmp));
  res = mzn_apply_padding(ctx, tmp, buf, max);
  return res;
}

size_t mzn_format_hex_upper(
		mznFormatStringContext *ctx, char *buf, size_t max, va_list *args) {
  char tmp[64];
  size_t res;
  mzn_itoa(va_arg(*args, int), 16, 0, tmp, sizeof(tmp));
  res = mzn_apply_padding(ctx, tmp, buf, max);
  return res;
}

size_t mzn_format_float(
		mznFormatStringContext *ctx, char *buf, size_t max, va_list *args) {
  char tmp[128];
  size_t res;
  mzn_ftoa(va_arg(*args, double), ctx->precision, tmp, sizeof(tmp));
  res = mzn_apply_padding(ctx, tmp, buf, max);
  return res;
}

size_t mzn_format_double(
		mznFormatStringContext *ctx, char *buf, size_t max, va_list *args) {
  char tmp[128];
  size_t res;
  mzn_dtoa(va_arg(*args, double), ctx->precision, tmp, sizeof(tmp));
  res = mzn_apply_padding(ctx, tmp, buf, max);
  return res;
}

size_t mzn_format_string(
		mznFormatStringContext *ctx, char *buf, size_t max, va_list *args) {
  const char *s;
  char tmp[256];
  size_t strLen;
  size_t i;
  s = va_arg(*args, const char*);
  strLen = mzn_strlen(s);
	if(ctx->truncate) {
		if(ctx->precision >= 0 && (size_t)ctx->precision < strLen) {
    	strLen = ctx->precision;
		}
	}
  for(i = 0; i < strLen && i < sizeof(tmp) - 1; i++) {
    tmp[i] = s[i];
  }
  tmp[i] = '\0';
  return mzn_apply_padding(ctx, tmp, buf, max);
}

size_t mzn_format_char(
		mznFormatStringContext *ctx, char *buf, size_t max, va_list *args) {
  char ch;
  char tmp[2];
  ch = (char)va_arg(*args, int);
  tmp[0] = ch;
  tmp[1] = '\0';
  return mzn_apply_padding(ctx, tmp, buf, max);
}

int32 mzn_vsnprintf(
		char *dest, size_t size, size_t n, const char *format, va_list args) {
	mznFormatStringSpecifier specifiers[10];
	mznFormatStringContext ctx;
	mzn_format_string_context_init(&ctx, dest, size, specifiers, sizeof(specifiers));
	mzn_format_string_register_specifier(&ctx, 'd', mzn_format_int);
	mzn_format_string_register_specifier(&ctx, 'x', mzn_format_hex_lower);
	mzn_format_string_register_specifier(&ctx, 'X', mzn_format_hex_upper);
	mzn_format_string_register_specifier(&ctx, 'f', mzn_format_double);
	mzn_format_string_register_specifier(&ctx, 's', mzn_format_string);
	mzn_format_string_register_specifier(&ctx, 'c', mzn_format_char);
	return mzn_internal_vsnprintf(&ctx, dest, size, n, format, &args);
}

int32 mzn_snprintf(char *dest, size_t size, size_t n, const char *format, ...) {
	va_list args;
	int32 result;
	va_start(args, format);
	result = mzn_vsnprintf(dest, size, n, format, args);
	va_end(args);
	return result;
}

int32 mzn_printf(const i8* format, ...) {
	int32 len;
	va_list args;
	char buffer[MZN_MAX_STRING];
  mznFormatStringSpecifier specifiers[16];
  mznFormatStringContext ctx;
  mzn_format_string_context_init(
			&ctx, buffer, sizeof(buffer), specifiers, sizeof(specifiers));
  mzn_format_string_register_specifier(&ctx, 'd', mzn_format_int);
  mzn_format_string_register_specifier(&ctx, 'x', mzn_format_hex_lower);
  mzn_format_string_register_specifier(&ctx, 'X', mzn_format_hex_upper);
  mzn_format_string_register_specifier(&ctx, 'f', mzn_format_double);
  mzn_format_string_register_specifier(&ctx, 's', mzn_format_string);
  mzn_format_string_register_specifier(&ctx, 'c', mzn_format_char);
  va_start(args, format);
  len = mzn_internal_vsnprintf(
			&ctx, buffer, sizeof(buffer), sizeof(buffer), format, &args);
  va_end(args);
  mzn_write(buffer, len);
  return len;
}


#endif /* MZN_LIB_IMPLEMENTATION */

/* @USER-UTILS ***************************************************************/

/* @USER-UTILS-INTERFACE *****************************************************/

/* @USER-UTILS-IMPLEMENTATION ************************************************/

/* @USER-AUDIO ***************************************************************/

/* @USER-AUDIO-INTERFACE *****************************************************/

MZNRET mzn_audio_init(mznAudioContext* context);
MZNRET mzn_audio_play(mznAudioContext* context);
MZNRET mzn_audio_stop(mznAudioContext* context);
MZNRET mzn_audio_finalize(mznAudioContext* context);
MZNRET mzn_audio_update(mznAudioContext* context, PFAUDIOPROC proc, void* dt);
mznAudioFormat mzn_audio_format(uint32 br, uint32 sr, uint32 ch, uint32 type);

/* @USER-AUDIO-IMPLEMENTATION ************************************************/

#ifdef MZN_LIB_IMPLEMENTATION

mznAudioFormat mzn_audio_format(
		uint32 bitRate, uint32 sampleRate, uint32 channels, uint32 type) {
	mznAudioFormat ret;
	ret.type = type;
	ret.bitRate = bitRate;
	ret.sampleRate = sampleRate;
	ret.channels = channels;
	return ret;
}

MZNRET mzn_audio_init(mznAudioContext* context) {
	MZN_LOG(LOG_DEBUG, "Audio intitializing");
	mzn_sys_audio_init(context);
	context->running = TRUE;
	return TRUE;
}

MZNRET mzn_audio_play(mznAudioContext* context) {
	MZN_LOG(LOG_DEBUG, "Audio play");
	mzn_sys_audio_play(context);
	return TRUE;
}

MZNRET mzn_audio_stop(mznAudioContext* context) {
	MZN_LOG(LOG_DEBUG, "Audio stop");
	mzn_sys_audio_stop(context);
	return TRUE;
}

MZNRET mzn_audio_finalize(mznAudioContext* context) {
	MZN_LOG(LOG_DEBUG, "Audio finalizing");
	mzn_sys_audio_finalize(context);
	return TRUE;
}

MZNRET mzn_audio_update(
		mznAudioContext* context, PFAUDIOPROC proc, void* data) {
	MZN_LOG(LOG_DEBUG, "Audio updating");
	mzn_sys_audio_update(context, proc, data);
	return TRUE;
}

#endif /* MZN_LIB_IMPLEMENTATION */

typedef struct mznMemoryEntry_t {
	uint32 index;
	size_t size;
} mznMemoryEntry;

typedef struct mznMemory_t {
	void* base;
	size_t max;
	mznMemoryEntry* entries;
} mznMemory;

typedef struct mznMemoryContext_t {
} mznMemoryContext;

/* @RENDER-CONTEXT ***********************************************************/

/* @RENDER-CONTEXT-INTERFACE *************************************************/

int32 mzn_context_init(mznContext* c);

/* @RENDER-CONTEXT-IMPLEMENTATION ********************************************/

#ifdef MZN_LIB_IMPLEMENTATION

int32 mzn_render_context_init(mznRenderContext* r, mznMemory* mem) {
	mzn_memset(r, 0, sizeof(mznRenderContext));
	return TRUE;
}

#endif /* MZN_LIB_IMPLEMENTATION */

/* @USER-CONTEXT *************************************************************/

/* @USER-CONTEXT-INTERFACE ***************************************************/

int32 mzn_context_init(mznContext* c);

/* @USER-CONTEXT-IMPLEMENTATION **********************************************/

#ifdef MZN_LIB_IMPLEMENTATION

int32 mzn_context_init(mznContext* c) {
	mzn_memset(c, 0, sizeof(mznContext));
	return TRUE;
}

#endif /* MZN_LIB_IMPLEMENTATION */
#endif /* MZN_LIB_H */
