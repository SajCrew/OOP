#include <algorithm>
#include <fcntl.h> // ��� _setmode
#include <io.h>    // ��� _setmode
#include <windows.h>
#include <iostream>
#include <fstream>
#include "Utils.h"

bool changesMade = false;

void ValidateVocabulary()
{

}


std::wstring ToLowerCase(const std::wstring& str)
{
    std::wstring lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::towlower);
    return lowerStr;
}

void InitializeProgram()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    // ��������� ������������ ����� � ������ �� ������ � UTF-16
    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stdout), _O_U16TEXT);
    //����������� ��������� ansi
}

void ProccesInput(VocabularyMap& vocabulary)
{
    std::wcout << L"������� ����� �� ���������� ��� �������� �� ������� (��� ������������� &) ��� exit ��� ������:" << std::endl;
    std::wstring input;
    while (true)
    {
        std::wcout << L">";
        std::getline(std::wcin, input);

        if (input == L"...")
        {
            ExitProgram(FILENAME, vocabulary, changesMade);
            break;
        }

        //�������� ��������� ����� ������������� &
        std::wstring lowerInput = ToLowerCase(input);

        if (vocabulary.find(lowerInput) != vocabulary.end())
        {
            Translate(lowerInput, vocabulary);
        }
        else
        {
            NewRecord(vocabulary, input, changesMade, lowerInput);
        }
    }
}

void LoadKeyAndValue(std::wifstream& file, VocabularyMap& vocabulary)
{
    std::wstring line;
    while (std::getline(file, line))
    {
        size_t spacePos = line.find(L'&');
        if (spacePos == std::wstring::npos)
        {
            continue; // ���������� ������ ��� ��������
        }
        std::wstring key = line.substr(0, spacePos);
        std::wstring value = line.substr(spacePos + 1);
        vocabulary[ToLowerCase(key)] = value;
    }
}

void Translate(const std::wstring& input, VocabularyMap& vocabulary)
{
    //��������� ������ ����� ������ � ��������
    if (input.empty())
    {
        return;
    }
    auto it = vocabulary.find(input);
    if (it != vocabulary.end())
    {
        std::wcout << it->second << std::endl;
    }
}
