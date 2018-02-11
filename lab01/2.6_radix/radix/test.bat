SET PROGRAM="%~1"

IF NOT EXIST "%PROGRAM%" GOTO usage

REM Binary to decimal
CALL :run_test 1 2 10 11111111
IF ERRORLEVEL 1 GOTO err

REM Hex to MAXINT32
CALL :run_test 2 16 10 7FFFFFFF
IF ERRORLEVEL 1 GOTO err

REM Hex to MININT32
CALL :run_test 3 16 10 -80000000
IF ERRORLEVEL 1 GOTO err

REM Radix 36 to binary
CALL :run_test 4 36 2 10
IF ERRORLEVEL 1 GOTO err

REM Decimal to binary
CALL :run_test 5 10 2 32767
IF ERRORLEVEL 1 GOTO err

REM Hex to MAXINT32+1
CALL :run_test_fail 16 10 80000000
IF ERRORLEVEL 1 GOTO err

REM Hex to MININT32-1
CALL :run_test_fail 16 10 -80000001
IF ERRORLEVEL 1 GOTO err

REM Wrong digits for a given radix
CALL :run_test_fail 2 10 12345
IF ERRORLEVEL 1 GOTO err

echo "PASS"
exit /B 0

:run_test 
SET ID=%~1
%PROGRAM% "%~2" "%~3" "%~4" >%TEMP%\output%ID%.txt
IF ERRORLEVEL 1 EXIT /B 1
fc %TEMP%\output%ID%.txt tests/expected%ID%.txt
IF ERRORLEVEL 1 EXIT /B 1
EXIT /B 0

REM Check if program exits non-zero return value
:run_test_fail
%PROGRAM% "%~1" "%~2" "%~3" >%TEMP%\output.txt
IF ERRORLEVEL 1 EXIT /B 0
EXIT /B 1


:err
echo "FAIL"
exit /B 1

:usage
echo "Usage: test.bat <program file>"
exit /B 1