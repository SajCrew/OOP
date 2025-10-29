#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <chrono>

const int INCORRECT_ARGUMENT = 1;
const int SUCCES = 0;

using HtmlEntityMap = const std::unordered_map<std::string, char>&;

const std::unordered_map<std::string, char>& GetHtmlEntities()
{
    //сделать через static map чтобы не пересоздавать map
    static HtmlEntityMap htmlEntities = //можно заменить на using
    {
        {"&quot;", '"'},
        {"&apos;", '\''},
        {"&lt;", '<'},
        {"&gt;", '>'},
        {"&amp;", '&'}
    };
    return htmlEntities;
}

bool TryDecodeHtmlEntity(const std::string& html, size_t pos,  
    HtmlEntityMap htmlEntities, char& decodedChar, size_t& entityLength)
{
    //переназвать функцию
   //сделать алиас для типа const std::unordered_map<std::string, char>&
    for (const auto& entity : htmlEntities)
    {
        if (html.substr(pos, entity.first.length()) == entity.first)
        {
            decodedChar = entity.second; 
            entityLength = entity.first.length();
            return true; 
        }
    }
    return false; 
}

std::string HtmlDecode(const std::string& html)
{
    auto htmlEntities = GetHtmlEntities();
    std::string result;
    size_t pos = 0;
    size_t htmlLength = html.length();

    while (pos < htmlLength)
    {
        char decodedChar;
        size_t entityLength;

        if (TryDecodeHtmlEntity(html, pos, htmlEntities, decodedChar, entityLength))
        {
            result += decodedChar; 
            pos += entityLength;
        }
        else
        {
            result += html[pos];
            pos++;
        }
    }

    return result;
}

//вектор передавать по ссылке
   //Htmldecode в main
void PrintDecode(const std::string& decodedLine)
{
    std::cout << decodedLine << std::endl;
}

void RunInputAndPrint()
{
    while (std::getline(inputFile, line))
    {
        std::string decodedLine = HtmlDecode(line);
        PrintDecode(decodedLine);
    }
}

void ManualHandleProcces()
{
    std::string line;
    RunInputAndPrint();
}

void HtmlProccesFile(const std::string& inputFilePath)
{
    std::string line;
    std::ifstream inputFile(inputFilePath);

    if (!inputFile.is_open())
    {
        std::cerr << "Ошибка: Не удалось открыть файл для чтения: " << inputFilePath << std::endl;
        return;
    }
    RunInputAndPrint();
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "ru");
    std::cout << "Введите строку для декодировки и ctrl - z" << std::endl;
    //не сохранять в lines все строки сразу
    if (argc == 1)
    {
        ManualHandleProcces();
    }
    else if (argc == 2)
    {
        std::string inputFilePath = argv[1];
        HtmlProccesFile(inputFilePath);
    }
    else
    {
        std::cerr << "Incorrect number of arguments" << std::endl;
        return INCORRECT_ARGUMENT;
    }
    return SUCCES;
}