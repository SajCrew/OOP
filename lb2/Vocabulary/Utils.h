#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <locale>
#include <map>
#include "Vocabulary.h"
//цикл зависимость с vocabulary.h

const std::string FILENAME = "dictionary.txt";
extern bool changesMade;

std::wstring ToLowerCase(const std::wstring& str);

void InitializeProgram();

void ProccesInput(VocabularyMap& vocabulary);

void LoadKeyAndValue(std::wifstream& file, VocabularyMap& vocabulary);

void Translate(const std::wstring& input, VocabularyMap& vocabulary);

#endif // UTILS_H