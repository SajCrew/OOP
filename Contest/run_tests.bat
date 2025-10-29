@echo off
set PROGRAM="C:\Users\MSI\source\repos\OOP\Contest\x64\Debug\Contest.exe" 
set OUT="%TEMP%\out.txt"

rem ������������� ����

if "%PROGRAM%"=="" (
    echo Error: Program name not provided.
    exit /b 1
)

rem ���� �� ����� ��������� "world"
echo 1.  Testing program with arguments...
%PROGRAM% test1.txt "world" > %OUT%
if ERRORLEVEL 4 (
    echo Error: Program failed with arguments.
    goto err
)

fc %OUT% output1.txt >nul
if ERRORLEVEL 1 (
    echo Error: Output does not match expected result.
    goto err
) 
if ERRORLEVEL 0 (
    echo OK: Program executed successfully and output matches expected result.
)

rem const int SUCCESS = 0;
rem const int FILE_NOT_FOUND = 1;
rem const int FILE_IS_EMPTY = 2;
rem const int SUBSTRING_NOT_FOUND = 3;
rem const int INVALID_ARGUMENTS = 4;

rem �������������� �����
call :test_empty_file
call :test_missing_file
call :test_nonexistent_substring
call :test_multiple_occurrences
call :test_case_insensitive
call :test_empty_substring
call :test_long_line
call :test_special_characters
call :test_empty_lines

echo OK: All tests passed.
exit /b 0

:err
echo Error: Program testing failed.
exit /b 1

:test_empty_file
    echo 2.  Testing program with empty file...
    echo.> empty.txt
    %PROGRAM% empty.txt "world" > %OUT%
    if ERRORLEVEL 2 (
        echo OK: Program correctly handles empty file.
    ) else (
        echo Error: Program should fail on empty file.
        goto err
    )
    exit /b 0

:test_missing_file
    echo 3.  Testing program with missing file...
    %PROGRAM% missing.txt "world" > %OUT%
    if ERRORLEVEL 1 (
        echo OK: Program correctly handles missing file.
    ) else (
        echo Error: Program should fail on missing file.
        goto err
    )
    exit /b 0

:test_nonexistent_substring
    echo 4.  Testing program with nonexistent_substring...
    %PROGRAM% test1.txt "nonexistent" > %OUT%
    if ERRORLEVEL 3 (
        echo OK: Program correctly handles missing substring.
    ) else (
        echo Error: Program should fail when substring is not found.
        goto err
    )
    exit /b 0

:test_multiple_occurrences
    echo 5.  Testing program with multiple_occurrences...
    %PROGRAM% test2.txt "world" > %OUT%
    fc %OUT% output2.txt >nul
    if ERRORLEVEL 1 (
        echo Error: Output does not match expected result for multiple occurrences.
        goto err
    ) else (
        echo OK: Output matches expected result for multiple occurrences.
    )
    exit /b 0


:test_case_insensitive
    echo 6.  Testing program with UP-case symbols...
    %PROGRAM% test2.txt "world" > %OUT%
    fc %OUT% output2.txt >nul
    if ERRORLEVEL 1 (
        echo Error: Output does not match expected result for case-insensitive search.
        goto err
    ) else (
        echo OK: Output matches expected result for case-insensitive search.
    )
    exit /b 0

:test_empty_substring
    echo 7.  Testing program with empty substring...
    %PROGRAM% test1.txt "" > %OUT%
    if ERRORLEVEL 3 (
        echo OK: Program correctly handles empty substring.
    ) else (
        echo Error: Program should fail on empty substring.
        goto err
    )
    exit /b 0

:test_long_line
    echo 8.  Testing program with long-line substring...
    %PROGRAM% test3.txt "This is a very long line with the word world somewhere in the middle..." > %OUT%
    fc %OUT% output3.txt > nul
    if ERRORLEVEL 1 (
        echo Error: Output does not match expected result for long lines.
        goto err
    ) else (
        echo OK: Output matches expected result for long lines.
    )
    exit /b 0