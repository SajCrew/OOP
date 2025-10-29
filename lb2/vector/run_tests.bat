@echo off
setlocal

:: Указываем путь к исполняемому файлу
set "number_processor=C:\Users\MSI\source\repos\OOP\lb2\vector\x64\Debug\vector.exe"

:: Проверяем, существует ли файл
if not exist "%number_processor%" (
    echo Error: Executable file not found: %number_processor%
    exit /b 1
)

:: Тестовый случай 1
echo Running Test 1...
echo 3 1.0 2 3.659512 > input.txt  :: 3 элемента: 1.0, 2, 3.659512
echo 3.220 4.220 5.879 > expected_output.txt
"%number_processor%" < input.txt > output.txt
fc output.txt expected_output.txt > nul
if %errorlevel% equ 0 (
    echo Test 1 passed.
) else (
    echo Test 1 failed.
)

:: Тестовый случай 2
echo Running Test 2...
echo 4 0.0 -1.0 2.0 4.0 > input.txt  :: 4 элемента: 0.0, -1.0, 2.0, 4.0
echo 2.000 3.000 5.000 6.000 > expected_output.txt
"%number_processor%" < input.txt > output.txt
fc output.txt expected_output.txt > nul
if %errorlevel% equ 0 (
    echo Test 2 passed.
) else (
    echo Test 2 failed.
)

:: Тестовый случай 3 (Крайний случай: нет положительных чисел)
echo Running Test 3...
echo 3 -1.0 -2.0 -3.0 > input.txt  :: 3 элемента: -1.0, -2.0, -3.0
echo -1.000 -2.000 -3.000 > expected_output.txt
"%number_processor%" < input.txt > output.txt
fc output.txt expected_output.txt > nul
if %errorlevel% equ 0 (
    echo Test 3 passed.
) else (
    echo Test 3 failed.
)

:: Тестовый случай 4 (Некорректный ввод)
echo Running Test 4...
echo 2 abc 1.0 > input.txt  :: 2 элемента, но второй элемент некорректен
echo Введён некорректный символ, введите число снова > expected_output.txt
"%number_processor%" < input.txt > output.txt
fc output.txt expected_output.txt > nul
if %errorlevel% equ 0 (
    echo Test 4 passed.
) else (
    echo Test 4 failed.
)

:: Очистка временных файлов
del input.txt output.txt expected_output.txt
echo All tests completed.

endlocal