SET PROGRAM="%~1"

IF NOT EXIST "%PROGRAM%" GOTO usage

REM Basic example
CALL :run_test 1
IF ERRORLEVEL 1 GOTO err

REM Zero matrix
CALL :run_test 2
IF ERRORLEVEL 1 GOTO err

REM Fractional
CALL :run_test 3
IF ERRORLEVEL 1 GOTO err

REM No answer
CALL :run_test 4
IF ERRORLEVEL 1 GOTO err

echo "PASS"
exit /B 0

:run_test 
SET ID=%~1
%PROGRAM% "tests/input%ID%.txt" >%TEMP%\output%ID%.txt
IF ERRORLEVEL 1 EXIT /B 1
fc %TEMP%\output%ID%.txt tests/expected%ID%.txt
IF ERRORLEVEL 1 EXIT /B 1
EXIT /B 0

:err
echo "FAIL"
exit /B 1

:usage
echo "Usage: test.bat <program file>"
exit /B 1