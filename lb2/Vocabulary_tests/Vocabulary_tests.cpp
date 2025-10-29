#define CATCH_CONFIG_MAIN // Генерация main() для Catch2
#include "catch.hpp" // Подключение заголовочного файла с интерфейсами
#include "../Vocabulary/Utils.h"

TEST_CASE("ToLowerCase converts strings to lowercase") 
{
    REQUIRE(ToLowerCase(L"Hello") == L"hello");
    REQUIRE(ToLowerCase(L"HELLO") == L"hello");
    REQUIRE(ToLowerCase(L"123ABC") == L"123abc");
    REQUIRE(ToLowerCase(L"") == L"");
}

TEST_CASE("LoadVocabulary loads dictionary from file") {
    VocabularyMap vocabulary = LoadVocabulary("dictionary.txt");
    REQUIRE(vocabulary.find(L"hello") != vocabulary.end());
    REQUIRE(vocabulary[L"hello"] == L"привет");
}

TEST_CASE("LoadVocabulary returns empty map for non-existent file") {
    VocabularyMap vocabulary = LoadVocabulary("non_existent_file.txt");
    REQUIRE(vocabulary.empty());
}

TEST_CASE("SaveVocabulary saves dictionary to file") {
    VocabularyMap vocabulary = { {L"hello", L"привет"}, {L"world", L"мир"} };
    REQUIRE(SaveVocabulary("test_output.txt", vocabulary) == true);

    VocabularyMap loadedVocabulary = LoadVocabulary("test_output.txt");
    REQUIRE(loadedVocabulary == vocabulary);
}

TEST_CASE("Translate finds existing word in vocabulary") {
    VocabularyMap vocabulary = { {L"hello", L"привет"} };
    bool changesMade = false;

    // Перехватываем вывод std::wcout
    std::wstringstream buffer;
    std::wstreambuf* old = std::wcout.rdbuf(buffer.rdbuf());

    Translate(L"hello", vocabulary);

    std::wcout.rdbuf(old);

    REQUIRE(buffer.str() == L"привет\n");
}

TEST_CASE("Translate handles unknown word") {
    VocabularyMap vocabulary = { {L"hello", L"привет"} };
    bool changesMade = false;

    std::wstringstream buffer;
    std::wstreambuf* old = std::wcout.rdbuf(buffer.rdbuf());

    Translate(L"world", vocabulary);

    std::wcout.rdbuf(old);

    REQUIRE(buffer.str().empty());
}

TEST_CASE("NewRecord adds new word to vocabulary") {
    VocabularyMap vocabulary;
    bool changesMade = false;
    std::wstring lowerInput = L"world";

    // Имитируем ввод пользователя
    std::wistringstream input(L"мир");
    std::wcin.rdbuf(input.rdbuf());

    NewRecord(vocabulary, L"world", changesMade, lowerInput);

    REQUIRE(vocabulary.find(L"world") != vocabulary.end());
    REQUIRE(vocabulary[L"world"] == L"мир");
    REQUIRE(changesMade == true);
}

//добавить тест с разделителем