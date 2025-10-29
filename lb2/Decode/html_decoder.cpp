#include "html_decoder.h"
#include <iostream>
#include <fstream>

const std::unordered_map<std::string, char>& GetHtmlEntities()
{
    static const std::unordered_map<std::string, char> htmlEntities =
    {
        {"&quot;", '"'},
        {"&apos;", '\''},
        {"&lt;", '<'},
        {"&gt;", '>'},
        {"&amp;", '&'}
    };
    return htmlEntities;
}
                                                                        //мапу по конст ссылке
bool TryDecodeHtmlEntity(const std::string& html, size_t pos, const HtmlEntityMap& htmlEntities, char& decodedChar, size_t& entityLength)
{
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

void PrintDecode(const std::string& decodedLine)
{
    std::cout << decodedLine << std::endl;
}

void ManualHandleProcces()
{
    std::string line;
    while (std::getline(std::cin, line))
    {
        std::string decodedLine = HtmlDecode(line);
        PrintDecode(decodedLine);
    }
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

    while (std::getline(inputFile, line))
    {
        std::string decodedLine = HtmlDecode(line);
        PrintDecode(decodedLine);
    }
}