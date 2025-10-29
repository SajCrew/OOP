#include <iostream>
#include <fstream>
#include "html_decode.h"

void PrintDecode(const std::string& decodedLine)
{
    std::cout << decodedLine << std::endl;
}

void ProcessInput(std::istream& inputStream)
{
    std::string line;
    while (std::getline(inputStream, line))
    {
        std::string decodedLine = HtmlDecode(line);
        PrintDecode(decodedLine);
    }
}

void HtmlProccesFile(const std::string& inputFilePath)
{
    std::ifstream inputFile(inputFilePath);

    if (!inputFile.is_open())
    {
        std::cerr << "Ошибка: Не удалось открыть файл для чтения: " << inputFilePath << std::endl;
        return;
    }

    ProcessInput(inputFile);
}

void ManualHandleProcces()
{
    ProcessInput(std::cin);
}

