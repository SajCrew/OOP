#include <iostream>
#include <locale>
#include <windows.h>
#include "Utils.h"

int main(int argc, char* argv[])
{
    InitializeProgram();

    //TryLoadVocabulary()
    VocabularyMap vocabulary = LoadVocabulary(FILENAME);
    
    ProccesInput(vocabulary);

    return 0;
}