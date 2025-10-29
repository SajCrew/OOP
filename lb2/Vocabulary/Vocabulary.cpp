#include <iostream>
#include <fstream>
#include <algorithm>
#include "Utils.h"

//����� � ����� �����
VocabularyMap LoadVocabulary(const std::string& filename)
{
    VocabularyMap vocabulary;
    std::wifstream file(filename);
    if (!file.is_open())
    {
        std::wcerr << L"���� ������� �� ������." << std::endl;
        return vocabulary;
    }
    file.imbue(std::locale("ru_RU.UTF-8"));

    LoadKeyAndValue(file, vocabulary);
    
    file.close();
    return vocabulary;
}

//�������� ��������� ������� � �����

bool SaveVocabulary(const std::string& filename, const VocabularyMap& vocabulary)
{
    std::wofstream file(filename);
    if (!file.is_open())
    {
        std::wcerr << L"������ ��� �������� ����� ��� ����������." << std::endl;
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
    //lowerInput ����� ������
    std::wcout << L"����������� ����� \"" << input << L"\". ������� ������� ��� ������ ������ ��� ������." << std::endl;
    std::wstring translation;
    std::getline(std::wcin, translation);
    std::wcout << L"�������� �������: \"" << translation << L"\"" << std::endl;
    if (!translation.empty())
    {
        vocabulary[lowerInput] = translation;
        std::wcout << L"����� \"" << input << L"\" ��������� � ������� ��� \"" << translation << L"\"." << std::endl;
        changesMade = true;
    }
    else
    {
        std::wcout << L"����� \"" << input << L"\" ���������������." << std::endl;
    }
}

void ExitProgram(const std::string& filename, const VocabularyMap& vocabulary, bool changesMade)
{
    if (!changesMade)
    {
        return;
    }
    std::wcout << L"� ������� ���� ������� ���������." << std::endl;

    //��������� �����������
    if (SaveVocabulary(filename, vocabulary))
    {
        std::wcout << L"��������� ���������." << std::endl;
    }
    else
    {
        std::wcout << L"�� ������� ��������� ���������." << std::endl;
    }
}

