#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <string>

const size_t MOVE_SCHEMA[8] = { 2, 3, 4, 6, 7, 0, 1, 5 };

void MoveBits(char& c)
{
	char result = 0;
	for (size_t index = 0; index < CHAR_BIT; index++)
	{
		if (c & (1u << index))
		{
			result |= 1 << MOVE_SCHEMA[index];
		}
	}
	c = result;
}

void UndoMoveBits(char& c)
{
	char result = 0;
	for (size_t index = 0; index < CHAR_BIT; index++)
	{
		if (c & (1u << MOVE_SCHEMA[index]))
		{
			result |= 1 << index;
		}
	}
	c = result;
}

std::function<char(char)> CryptFn(char key)
{
	return [key](char c) {
		c ^= key;
		MoveBits(c);
		return c;
	};
}

std::function<char(char)> DecryptFn(char key)
{
	return [key](char c) {
		UndoMoveBits(c);
		c ^= key;
		return c;
	};
}

void Crypt(std::istream& input, std::ostream& output, std::function<char(char)> fn)
{
	std::istreambuf_iterator<char> begin(input);
	std::ostreambuf_iterator<char> destinataion(output);
	std::transform(begin, {}, destinataion, fn);
}

bool Crypt(const std::string& inputFileName, const std::string& outputFileName, std::function<char(char)> fn)
{
	std::ifstream inputFile(inputFileName, std::ios::binary);
	if (!inputFile.is_open())
	{
		std::cerr << "Failed to open input file: " << inputFileName << '\n';
		return false;
	}

	std::ofstream outputFile(outputFileName, std::ios::binary);
	if (!outputFile.is_open())
	{
		std::cerr << "Failed to open output file: " << outputFileName << '\n';
		return false;
	}

	Crypt(inputFile, outputFile, fn);

	outputFile.flush();
	return static_cast<bool>(outputFile);
}

long StrToLong(char* str, bool& wasErr)
{
	char* pEnd = NULL;
	long value = strtol(str, &pEnd, 10);
	wasErr = ((*str == '\0') || (*pEnd != '\0'));
	return value;
}

const std::string COMMAND_CRYPT = "crypt";
const std::string COMMAND_DECRYPT = "decrypt";

bool CommandIsWrong(const std::string& command)
{
	return command != COMMAND_CRYPT && command != COMMAND_DECRYPT;
}

std::function<char(char)> TransformationFn(const std::string& command, char key)
{
	return (command == COMMAND_CRYPT) ? CryptFn(key) : DecryptFn(key);
}

const int KEY_UPPER_BOUND = 255;
const int KEY_LOWER_BOUND = 0;

bool KeyIsInBounds(int key)
{
	return (KEY_LOWER_BOUND <= key) && (key <= KEY_UPPER_BOUND);
}

void ShowUsage()
{
	std::cout << "Usage: crypt.exe " << COMMAND_CRYPT << '|' << COMMAND_DECRYPT
			  << "<input file> <output file> <key="
			  << KEY_LOWER_BOUND << ".." << KEY_UPPER_BOUND << ">\n";
}

const int ARGS_COUNT = 4;

int main(int argc, char* argv[])
{
	if (argc != ARGS_COUNT + 1)
	{
		std::cout << "Invalid arguments count\n";
		ShowUsage();
		return 1;
	}

	std::string command = argv[1];
	std::string inputFileName = argv[2];
	std::string outputFileName = argv[3];

	bool wasErr = false;
	long key = StrToLong(argv[4], wasErr);
	if (wasErr || !KeyIsInBounds(key))
	{
		std::cout << "Wrong key: " << argv[4] << '\n';
		ShowUsage();
		return 1;
	}

	if (CommandIsWrong(command))
	{
		std::cerr << "Wrong command " << command << '\n';
		ShowUsage();
		return 1;
	}

	auto fn = TransformationFn(command, static_cast<char>(key));
	if (!Crypt(inputFileName, outputFileName, fn))
	{
		ShowUsage();
		return 1;
	}

	return 0;
}
