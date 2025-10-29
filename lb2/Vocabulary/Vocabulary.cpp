#include <iostream>
#include <fstream>
#include <algorithm>
#include "Utils.h"

//фуекц с больш буквы
VocabularyMap LoadVocabulary(const std::string& filename)
{
    VocabularyMap vocabulary;
    std::wifstream file(filename);
    if (!file.is_open())
    {
        std::wcerr << L"Файл словаря не найден." << std::endl;
        return vocabulary;
    }
    file.imbue(std::locale("ru_RU.UTF-8"));

    LoadKeyAndValue(file, vocabulary);
    
    file.close();
    return vocabulary;
}

//добавить валидацию словаря и ввода

bool SaveVocabulary(const std::string& filename, const VocabularyMap& vocabulary)
{
    std::wofstream file(filename);
    if (!file.is_open())
    {
        std::wcerr << L"Ошибка при открытии файла для сохранения." << std::endl;
        return false;
    }

    file.imbue(std::locale("ru_RU.UTF-8"));

    for (const auto& pair : vocabulary)
    {
        file << pair.first << L"&" << pair.second << std::endl;
    }
    file.close();
    return true;
}

void NewRecord(VocabularyMap& vocabulary, const std::wstring& input, bool& changesMade, std::wstring& lowerInput)
{
    //lowerInput через ссылку
    std::wcout << L"Неизвестное слово \"" << input << L"\". Введите перевод или пустую строку для отказа." << std::endl;
    std::wstring translation;
    std::getline(std::wcin, translation);
    std::wcout << L"Введённый перевод: \"" << translation << L"\"" << std::endl;
    if (!translation.empty())
    {
        vocabulary[lowerInput] = translation;
        std::wcout << L"Слово \"" << input << L"\" сохранено в словаре как \"" << translation << L"\"." << std::endl;
        changesMade = true;
    }
    else
    {
        std::wcout << L"Слово \"" << input << L"\" проигнорировано." << std::endl;
    }
}

void ExitProgram(const std::string& filename, const VocabularyMap& vocabulary, bool changesMade)
{
    if (!changesMade)
    {
        return;
    }
    std::wcout << L"В словарь были внесены изменения." << std::endl;

    //уменьшить вложенность
    if (SaveVocabulary(filename, vocabulary))
    {
        std::wcout << L"Изменения сохранены." << std::endl;
    }
    else
    {
        std::wcout << L"Не удалось сохранить изменения." << std::endl;
    }
}

