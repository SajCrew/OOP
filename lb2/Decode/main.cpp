#include "html_utils.h"
#include <iostream>

const int INCORRECT_ARGUMENT = 1;

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "ru");
    std::cout << "Введите строку для декодировки и ctrl - z" << std::endl;

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

    return 0;
}