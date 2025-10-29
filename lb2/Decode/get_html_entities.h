#ifndef GET_HTML_ENTITIES_H
#define GET_HTML_ENTITIES_H

#include <string>
#include <unordered_map>

using HtmlEntityMap = const std::unordered_map<std::string, char>&;
const std::unordered_map<std::string, char>& GetHtmlEntities();
#endif