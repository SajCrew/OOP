#include "Validation.h"
#include <algorithm>
#include <cctype>

bool IsValidIdentifier(const std::string& name)
{
    if (name.empty() || isdigit(name[0]))
        return false;
    for (char c : name)
    {
        if (!isalnum(c) && c != '_')
            return false;
    }
    return true;
}

bool OpIsNumber(const std::string& value)
{
    bool isNumber = true;
    for (char c : value)
    {
        if (!isdigit(c) && c != '.' && c != '-' && c != '+')
        {
            isNumber = false;
            break;
        }
    }
    return isNumber;
}

void Trim(std::string& s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) { return !isspace(ch); }));
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) { return !isspace(ch); }).base(), s.end());
}