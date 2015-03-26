@echo off
REM make16.bat
REM Revised 2/1/02
REM By: Kip R. Irvine

REM Assembles and links the current 16-bit ASM program.
REM 
REM Command-line options (unless otherwise noted, they are case-sensitive):
REM 
REM /nologo     Suppress the Microsoft logo display
REM -Cp         Enforce case-sensitivity for all identifiers
REM -Zi         Include source code line information for debugging
REM -Fl         Generate a listing file (see page 88)
REM /CODEVIEW   Generate CodeView debugging information (linker)
REM %1.asm      The name of the source file, passed on the command line

REM ************* The following lines can be customized:
REM PATH C:\Masm615
SET INCLUDE=C:\Masm611\INCLUDE;C:\TXTSTUFF\INCLUDE
SET LIB=C:\Masm611\LIB;C:\TXTSTUFF\LIB
REM **************************** End of customized lines

REM Invoke ML.EXE (the assembler):

REM ML /nologo -c -Fl -Zi %1.asm
ML -c -Fl %1.asm
if errorlevel 1 goto terminate

REM Run the 16-bit linker:

REM LINK /nologo /CODEVIEW %1,,NUL,Irvine16;
LINK /T %1,,NUL,Irvine16;
if errorlevel 1 goto terminate

REM Display all files related to this program:
rem DIR %1.*

:terminate
rem pause
