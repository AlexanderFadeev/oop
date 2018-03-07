SET PROGRAM="%~1"

IF NOT EXIST "%PROGRAM%" GOTO usage

REM Primes in range 1 .. 10
CALL :run_test 1 10
IF ERRORLEVEL 1 GOTO err

REM Negative upper bound
CALL :run_test 2 -42
IF ERRORLEVEL 1 GOTO err

REM Primes in range 1 .. 100
CALL :run_test 3 100
IF ERRORLEVEL 1 GOTO err

REM Upper bound is a prime number
CALL :run_test 4 17
IF ERRORLEVEL 1 GOTO err

REM Upper bound larger than 1E+8
CALL :run_test_fail 100000001
IF ERRORLEVEL 1 GOTO err

echo "PASS"
exit /B 0

:run_test REM (1-ID 2-UPPER_BOUND)
SET ID=%~1
SET OUT="%TEMP%\output%ID%.txt"
SET EXP="tests/expected%ID%.txt"
%PROGRAM% %~2 >%OUT%
IF ERRORLEVEL 1 EXIT /B 1
fc %OUT% %EXP%
EXIT /B %ERRORLEVEL%

REM Checks if program exits with non-zero return value
:run_test_fail REM (1-UPPER_BOUND)
%PROGRAM% %~1 > nul
IF ERRORLEVEL 1 EXIT /B 0
EXIT /B 1

:err
echo "FAIL"
exit /B 1

:usage
echo "Usage: test.bat <program file>"
exit /B 1