#ifndef VOCABULARY_H
#define VOCABULARY_H

#include <map>
#include <string>
#include <locale>

using VocabularyMap = std::map<std::wstring, std::wstring>; //â using

VocabularyMap LoadVocabulary(const std::string& filename);

bool SaveVocabulary(const std::string& filename, const VocabularyMap& vocabulary);

void NewRecord(VocabularyMap& vocabulary, const std::wstring& input, bool& changesMade, std::wstring& lowerInput);

void ExitProgram(const std::string& filename, const VocabularyMap& vocabulary, bool changesMade);

#endif 