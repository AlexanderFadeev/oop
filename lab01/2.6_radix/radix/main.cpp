#include <iostream>
#include <string>
#include <assert.h>

bool IsDigit(char c)
{
	return (c >= '0') && (c <= '9') || (c >= 'A') && (c <= 'Z');
}

int CharDigitToInt(char c, bool &wasError)
{
	if ((c >= '0') && (c <= '9')) 
	{
		return c - '0';
	}
	if ((c >= 'A') && (c <= 'Z')) 
	{
		return 10 + c - 'A';
	}
	wasError = true;
	return 0;
}

int Sign(char c, bool &wasError)
{
	if (c == '-')
	{
		return -1;
	} 
	if (c == '+')
	{
		return 1;
	}
	wasError = true;
	return 0;
}

bool Overflowed(int value, int sign) 
{
	return (sign > 0) ? (value < 0) : (value > 0);
}

int StringToInt(const std::string str, int radix, bool &wasError)
{
	if (str.length() == 0) // Пустая строка
	{
		wasError = true;
		return 0;
	}

	size_t pos = 0; // Позиция, с которой идут цифры
	int sign = 1;
	if (!IsDigit(str[0]))
	{
		if (str.length() == 1) // Строка из одного нецифрового символа
		{
			wasError = true;
			return 0;
		}
		sign = Sign(str[0], wasError);
		if (wasError) 
		{
			return 0;
		}
		pos++;
	}

	int value = 0;
	for (; pos < str.length(); pos++) 
	{
		if (value * radix / radix != value) // Проверка на переполнение при умножении на radix
		{
			wasError = true;
			return 0;
		}
		value *= radix;
		int digit = CharDigitToInt(str[pos], wasError);
		if (wasError || (digit >= radix))
		{
			wasError = true;
			return 0;
		}
		value += digit * sign;
		if (Overflowed(value, sign))
		{
			wasError = true;
			return 0;
		}
	}

	return value;
}

int GetLastDigit(int n, int radix, bool isNegative)
{
	int digit = (n % radix + radix) % radix;
	if (isNegative)
	{
		digit = (radix - digit) % radix;
	}
	return digit;
}

char IntDigitToChar(int n)
{
	if (n < 10)
	{
		return '0' + n;
	}
	return 'A' + n - 10;
}

std::string IntToString(int n, int radix, bool &wasError)
{
	std::string result = "";
	bool isNegative = (n < 0);

	if (n == 0)
	{
		result = "0";
	}

	while (n != 0)
	{
		int digit = GetLastDigit(n, radix, isNegative);
		result.push_back(IntDigitToChar(digit));
		n /= radix;
	}

	if (isNegative) 
	{
		result.push_back('-');
	}

	std::reverse(result.begin(), result.end()); // разворачиваем строку, т.к. младшие разряды шли слева

	return result;
}

bool NotationIsCorrect(int notation) 
{
	return (notation >= 2) && (notation <= 36);
}

const int ARGS_COUNT = 3;

void ShowUsage()
{
	std::cout << "Usage: radix.exe <source notation> <destination notation> <value>\n";
}

int main(int argc, char* argv[])
{
	if (argc != ARGS_COUNT + 1)
	{
		std::cout << "Invalid arguments count\n";
		ShowUsage();
		return 1;
	}

	bool wasError = false;
	int sourceNotation = StringToInt(std::string(argv[1]), 10, wasError);
	if (wasError || !NotationIsCorrect(sourceNotation))
	{
		std::cout << "Wrong source notation: " << argv[1] << '\n';
		ShowUsage();
		return 1;
	}

	wasError = false;
	int destinationNotation = StringToInt(std::string(argv[2]), 10, wasError);
	if (wasError || !NotationIsCorrect(destinationNotation))
	{
		std::cout << "Wrong destination notation: " << argv[2] << '\n';
		ShowUsage();
		return 1;
	}

	wasError = false;
	int value = StringToInt(std::string(argv[3]), sourceNotation, wasError);
	if (wasError)
	{
		std::cout << "Wrong value: " << argv[3] << '\n';
		ShowUsage();
		return 1;
	}

	wasError = false;
	std::string result = IntToString(value, destinationNotation, wasError);
	if (wasError)
	{
		std::cout << "Failed to convert value to destination radix: " << value << '\n';
		return 1;
	}

	std::cout << result << '\n';

	return 0;
}