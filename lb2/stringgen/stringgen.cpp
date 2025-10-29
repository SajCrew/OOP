#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <fstream>

// Функция для генерации случайного числа в диапазоне [min, max]
int GetRandomNumber(int min, int max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(min, max);
    return distrib(gen);
}

// Функция для генерации длинной строки с HTML-сущностями
std::string GenerateLongString(size_t length)
{
    // Список HTML-сущностей
    std::vector<std::string> htmlEntities = { "&quot;", "&apos;", "&lt;", "&gt;", "&amp;" };

    // Строка для результата
    std::string result;
    result.reserve(length); // Резервируем память для ускорения работы

    // Генерация строки
    for (size_t i = 0; i < length; )
    {
        // Случайно выбираем, вставить ли HTML-сущность или обычный символ
        if (GetRandomNumber(0, 1) == 1 && i + 6 <= length) // 6 — максимальная длина сущности
        {
            // Выбираем случайную HTML-сущность
            std::string entity = htmlEntities[GetRandomNumber(0, htmlEntities.size() - 1)];
            result += entity;
            i += entity.length();
        }
        else
        {
            // Добавляем случайный символ (например, букву или цифру)
            char randomChar = 'a' + GetRandomNumber(0, 25); // Случайная буква
            result += randomChar;
            i++;
        }
    }

    return result;
}

int main()
{
    // Длина генерируемой строки
    size_t length = 1000000; // 1 миллион символов

    // Генерация строки
    std::string longString = GenerateLongString(length);

    // Сохранение строки в файл
    std::ofstream outputFile("long_string.txt");
    if (outputFile.is_open())
    {
        outputFile << longString;
        std::cout << "Длинная строка успешно записана в файл 'long_string.txt'" << std::endl;
    }
    else
    {
        std::cerr << "Ошибка: Не удалось открыть файл для записи." << std::endl;
        return 1;
    }

    return 0;
}