@ECHO OFF

SET "OPT= -O2"
SET "STD= -std=c89 -ansi"
SET "DBG= -pedantic -Wall -Wextra"
SET "EX1= -Wfloat-equal -Wbad-function-cast -Wcast-align -Wpointer-arith"
SET "EX2= -Wswitch -Wshadow -Wstrict-prototypes -Wunused-parameter"
SET "LNK= -lkernel32 -lgdi32 -lole32 -lwinmm -lavrt -lksuser -lcomdlg32"
ECHO BUILDING: [%1]
ECHO COMPILER FLAGS:
ECHO - OPTIMIZATION: %OPT%
ECHO - STANDARD....: %STD%
ECHO - DEBUG.......: %DBG%
gcc %1.c -o %1.exe %OPT% %DBG% %STD% %OTH% %LNK%
ECHO RUNNING EXECUTABLE
ECHO ==================
If [%2]==[] (
	GOTO EXEC
)
:EXEC
%1.exe %2
