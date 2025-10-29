#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <istream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <fstream>

bool ValidNumber(double value)
{
	try 
	{
		if (std::cin.fail()) 
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
			throw std::invalid_argument("неправильный ввод"); 
		}
		return true; 
	}
	catch (const std::exception& e) 
	{
		std::cerr << "Ошибка: " << e.what() << std::endl;
		return false; 
	}
}

std::vector<double> ReadNumbers(int n, std::vector<double>& vec) {
	for (int i = 0; i < n; ++i)
	{
		double value;
		std::cin >> value;
		try
		{
			if (ValidNumber(value))
			{
				vec[i] = value;
			}
		}
		catch (const std::exception& e)
		{	
			std::cout << "Введён некорректный символ, введите число снова" << std::endl;
			break;
		}
	}
	return vec;
}

void PrintSortedNumbers(std::vector<double>& numbers)
{
	std::cout << std::fixed << std::setprecision(3);
	for (double num : numbers)
	{
		std::cout << num << " ";
	}
	std::cout << std::endl;
}

double SumOfPositives(const std::vector<double>& numbers)
{
	return std::accumulate(numbers.begin(), numbers.end(), 0.0, [](double acc, double num)
		{
			return num > 0 ? acc + num : acc;
		});
}

size_t CountPositives(const std::vector<double>& numbers)
{
	return std::count_if(numbers.begin(), numbers.end(), [](double num)
		{
			return num > 0;
		});
}

double AverageOfPositives(const std::vector<double>& numbers)
{
	double sum_positive = SumOfPositives(numbers);
	size_t count_positive = CountPositives(numbers);
	return (count_positive > 0) ? sum_positive / count_positive : 0.0;
}

void AddAverageToElements(std::vector<double>& numbers, double average)
{
	for (double& num : numbers)
	{
		num += average;
	}
}

void ProccesNumbers(std::vector<double>& numbers)
{
	double average_positive = AverageOfPositives(numbers);
	AddAverageToElements(numbers, average_positive);
	std::sort(numbers.begin(), numbers.end());
}

int main(int argc, char* argv[])
{

	setlocale(LC_ALL, "ru");
	std::istream* input = &std::cin; // По умолчанию ввод с клавиатуры
	std::ifstream file_input;
	int n;
	std::cout << "Введите количество элементов массива: ";
	*input >> n;

	if (argc > 1)
	{
		file_input.open(argv[1]);
		if (!file_input.is_open())
		{
			std::cerr << "Ошибка: не удалось открыть файл " << argv[1] << std::endl;
			return 1;
		}
		input = &file_input; // Перенаправляем ввод на файл
	}

	std::vector<double> vec(n);
	std::cout << "Введите " << n << " элементов массива через пробел \n" << std::endl;
	std::vector<double> vec = ReadNumbers(n, *input);
	std::cout << "Введенные числа: ";
	for (int i = 0; i < n; ++i) {
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;
	ProccesNumbers(vec);
	PrintSortedNumbers(vec);

	return 0;
}