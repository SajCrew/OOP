#include <iostream>
#include <fstream>
#include <unordered_map>

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