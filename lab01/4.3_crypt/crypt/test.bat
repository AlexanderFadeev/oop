SET PROGRAM="%~1"

IF NOT EXIST "%PROGRAM%" GOTO usage

REM Basic example
CALL :run_test 1 0
IF ERRORLEVEL 1 GOTO err

REM Non-zero key
CALL :run_test 2 85
IF ERRORLEVEL 1 GOTO err

REM Empty input
CALL :run_test 3 42
IF ERRORLEVEL 1 GOTO err

REM .exe file with zero key
CALL :run_test_exe 0
IF ERRORLEVEL 1 GOTO err

REM .exe file with non-zero key
CALL :run_test_exe 146
IF ERRORLEVEL 1 GOTO err

echo "PASS"
exit /B 0

REM Testing crypting and decrypting of exe file
:run_test_exe REM (1-KEY)
SET CRYPTED="%TEMP%\crypted.exe.dat"
SET DECRYPTED="%TEMP%\decrypted.exe"
%PROGRAM% "crypt" %PROGRAM% %CRYPTED% %~1
IF ERRORLEVEL 1 EXIT /B 1
CALL :run_test_impl "decrypt" %CRYPTED% %DECRYPTED% %PROGRAM% %~1
EXIT /B %ERRORLEVEL%

:run_test REM (1-ID 2-KEY)
CALL :run_test_crypt %~1 %~2
IF ERRORLEVEL 1 EXIT /B 1
CALL :run_test_decrypt %~1 %~2
EXIT /B %ERRORLEVEL%

:run_test_crypt REM (1-ID 2-KEY)
SET ID=%~1
SET IN="tests/input%ID%.txt"
SET OUT="%TEMP%\output%ID%.dat"
SET EXP="tests/expected%ID%.dat"
CALL :run_test_impl "crypt" %IN% %OUT% %EXP% %~2
EXIT /B %ERRORLEVEL%

:run_test_decrypt REM (1-ID 2-KEY)
SET ID=%~1
SET IN="%TEMP%/output%ID%.dat"
SET OUT="%TEMP%\decrypted%ID%.txt"
SET EXP="tests/input%ID%.txt"
CALL :run_test_impl "decrypt" %IN% %OUT% %EXP% %~2
EXIT /B %ERRORLEVEL%

:run_test_impl REM (1-COMMAND 2-IN 3-OUT 4-EXP 5-KEY)
%PROGRAM% %~1 %~2 %~3 %~5
IF ERRORLEVEL 1 EXIT /B 1
fc /B %~3 %~4
IF ERRORLEVEL 1 EXIT /B 1
EXIT /B 0

:err
echo "FAIL"
exit /B 1

:usage
echo "Usage: test.bat <program file>"
exit /B 1