SET PROGRAM="%~1"

IF NOT EXIST "%PROGRAM%" GOTO usage

REM Binary to decimal
CALL :run_test 1 2 10 11111111
IF ERRORLEVEL 1 GOTO err

REM Hex to MAXINT32
CALL :run_test 2 16 10 7FFFFFFF
IF ERRORLEVEL 1 GOTO err

REM Hex to MAXINT32 overflow
CALL :run_bad_test 3 16 10 80000000
IF ERRORLEVEL 1 GOTO err

REM Radix 36 to binary
CALL :run_test 4 36 2 10
IF ERRORLEVEL 1 GOTO err

REM Decimal to binary
CALL :run_test 5 10 2 32767
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

:run_bad_test
SET ID=%~1
%PROGRAM% "%~2" "%~3" "%~4" >%TEMP%\output%ID%.txt
fc %TEMP%\output%ID%.txt tests/expected%ID%.txt
IF ERRORLEVEL 1 EXIT /B 1
EXIT /B 0


:err
echo "FAIL"
exit /B 1

:usage
echo "Usage: test.bat <program file>"
exit /B 1