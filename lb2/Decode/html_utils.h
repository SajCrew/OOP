#ifndef HTML_UTILS
#define HTML_UTILS

#include <string>

void ManualHandleProcces();

void HtmlProccesFile(const std::string& inputFilePath);

void ProcessInput(std::istream& inputStream);

void PrintDecode(const std::string& decodedLine);
#endif