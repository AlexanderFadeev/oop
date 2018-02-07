SET PROGRAM="%~1"

IF NOT EXIST "%PROGRAM%" GOTO usage

REM Simple test
CALL :run_test 1 "foo" "bar"
IF ERRORLEVEL 1 GOTO err

REM Recurrent strings 1
CALL :run_test 2 "foo" "barfoo"
IF ERRORLEVEL 1 GOTO err

REM Recurrent strings 2
CALL :run_test 3 "ma" "mama"
IF ERRORLEVEL 1 GOTO err

REM Special case
CALL :run_test 4 "1231234" "technology"
IF ERRORLEVEL 1 GOTO err

REM Empty input file
CALL :run_test 5 "empty" "file"
IF ERRORLEVEL 1 GOTO err

echo "PASS"
exit /B 0

:run_test 
SET ID=%~1
%PROGRAM% tests/input%ID%.txt %TEMP%\output%ID%.txt "%~2" "%~3"
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