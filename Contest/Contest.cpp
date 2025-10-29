#include <fstream>
#include <iostream>
#include <istream>
#include <string>
#include <vector>

// Коды возврата
const int SUCCESS = 0;
const int FILE_NOT_FOUND = 1;
const int FILE_IS_EMPTY = 2;
const int SUBSTRING_NOT_FOUND = 3;
const int INVALID_ARGUMENTS = 4;

std::vector<int> prefixFunction(const std::string& pattern) {
	int m = pattern.length();
	std::vector<int> pi(m, 0); 
	int k = 0; // длина текущего совпадающего префикса

	for (int i = 1; i < m; i++) {
		
		while (k > 0 && pattern[k] != pattern[i]) {
			k = pi[k - 1];
		}
	
		if (pattern[k] == pattern[i]) {
			k++;
		}

		pi[i] = k;
	}

	return pi;
}

bool kmpSearch(const std::string& text, const std::string& pattern) {
	int n = text.length(); // длина текста
	int m = pattern.length(); // длина подстроки

	if (m == 0) return false; 
	
	std::vector<int> pi = prefixFunction(pattern);
	int q = 0; // количество совпавших символов
	
	for (int i = 0; i < n; i++) {
		
		while (q > 0 && pattern[q] != text[i]) {
			q = pi[q - 1]; 
		}
		if (pattern[q] == text[i]) {
			q++;
		}
		if (q == m) {
			return true; 
		}
	}
	return false; 
}
int main(int argc, char* argv[])
{
	std::string line;
	int lineNumber = 0;
	bool found = false;
	std::string fileName;
	std::string searchText;

	fileName = argv[1];
	searchText = argv[2];

	setlocale(LC_ALL, "ru");

	if (argc != 3) 
	{
		std::cerr << "не соответствувует количеству нужных аргументов" << std::endl;
		return INVALID_ARGUMENTS;
	}

	std::ifstream file(fileName);
	if (!file.is_open()) {
		std::cerr << "Error: Could not open file " << fileName << std::endl;
		return FILE_NOT_FOUND;
	}

	file.seekg(0, std::ios::end);
	if (file.tellg() == 0) {
		std::cerr << "Error: The file is empty." << std::endl;
		return FILE_IS_EMPTY; 
	}
	file.seekg(0, std::ios::beg);

	while (std::getline(file, line)) {
		lineNumber++;

		line.erase(std::remove(line.begin(), line.end(), ' '), line.end());

		if (kmpSearch(line, searchText)) {
			std::cout << lineNumber << std::endl;
			found = true;
		}
	}
	file.close();


	if (!found) {
		std::cout << "Text not found" << std::endl;
		return SUBSTRING_NOT_FOUND;
	}
	else
		return SUCCESS;
}