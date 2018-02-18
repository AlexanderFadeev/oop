SET PROGRAM="%~1"

IF NOT EXIST "%PROGRAM%" GOTO usage

REM TODO

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