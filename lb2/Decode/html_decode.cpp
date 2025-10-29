#include "get_html_entities.h"
#include <iostream>
#include <fstream>
#include <string>

bool TryDecodeHtmlEntity(const std::string& html, size_t pos, const HtmlEntityMap& htmlEntities, char& decodedChar, size_t& entityLength)
{
    for (size_t len = 1; len <= html.length() - pos; ++len)
    {
        std::string key = html.substr(pos, len);
        auto it = htmlEntities.find(key);
        if (it != htmlEntities.end())
        {
            decodedChar = it->second;
            entityLength = it->first.length();
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