SET PROGRAM="%~1"

IF NOT EXIST "%PROGRAM%" GOTO usage

REM Basic example
CALL :run_test 1 "crypt" "0"
IF ERRORLEVEL 1 GOTO err

REM Non-zero key
CALL :run_test 2 "crypt" "85"
IF ERRORLEVEL 1 GOTO err

REM Decoding of previous test
CALL :run_test 3 "decrypt" "85"
IF ERRORLEVEL 1 GOTO err

REM Empty input
CALL :run_test 4 "crypt" "42"
IF ERRORLEVEL 1 GOTO err

echo "PASS"
exit /B 0

:run_test 
SET ID=%~1
%PROGRAM% %~2 "tests/input%ID%.txt" %TEMP%\output%ID%.txt %~3
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