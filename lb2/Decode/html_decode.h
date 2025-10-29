#ifndef HTML_DECODE_H
#define HTML_DECODE_H

#include "get_html_entities.h"
#include <string>

bool TryDecodeHtmlEntity(const std::string& html, size_t pos, const HtmlEntityMap& htmlEntities, char& decodedChar, size_t& entityLength);
std::string HtmlDecode(const std::string& html);
#endif