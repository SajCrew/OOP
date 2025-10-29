#ifndef HTML_DECODER_H
#define HTML_DECODER_H

#include <string>
#include <unordered_map>

const int INCORRECT_ARGUMENT = 1;

using HtmlEntityMap = const std::unordered_map<std::string, char>&;


const std::unordered_map<std::string, char>& GetHtmlEntities();


bool TryDecodeHtmlEntity(const std::string& html, size_t pos, HtmlEntityMap htmlEntities, char& decodedChar, size_t& entityLength);


std::string HtmlDecode(const std::string& html);


void PrintDecode(const std::string& decodedLine);


void ManualHandleProcces();


void HtmlProccesFile(const std::string& inputFilePath);

#endif 