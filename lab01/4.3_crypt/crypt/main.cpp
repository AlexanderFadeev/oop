#include <algorithm>
#include <fstream>
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

auto CryptFn(char key)
{
	return [&](char c) {
		c ^= key;
		MoveBits(c);
		return c;
	};
}

auto DecryptFn(char key)
{
	return [&](char c) {
		UndoMoveBits(c);
		c ^= key;
		return c;
	};
}

void Crypt(std::istream& input, std::ostream& output, char key)
{
	std::istreambuf_iterator<char> begin(input);
	std::ostreambuf_iterator<char> destinataion(output);
	std::transform(begin, {}, destinataion, CryptFn(key));
}

void Decrypt(std::istream& input, std::ostream& output, char key)
{
	std::istreambuf_iterator<char> begin(input);
	std::ostreambuf_iterator<char> destinataion(output);
	std::transform(begin, {}, destinataion, DecryptFn(key));
}

const std::string COMMAND_CRYPT = "crypt";
const std::string COMMAND_DECRYPT = "decrypt";

bool Run(const std::string& command, const std::string& inputFileName, const std::string& outputFileName, char key)
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

	if (command == COMMAND_CRYPT)
	{
		Crypt(inputFile, outputFile, key);
	}
	else if (command == COMMAND_DECRYPT)
	{
		Decrypt(inputFile, outputFile, key);
	}
	else
	{
		std::cerr << "Wrong command\n";
		return false;
	}

	return static_cast<bool>(outputFile);
}

long StrToLong(char* str, bool& wasErr)
{
	char* pEnd = NULL;
	long value = strtol(str, &pEnd, 10);
	wasErr = ((*str == '\0') || (*pEnd != '\0'));
	return value;
}

void ShowUsage()
{
	std::cout << "Usage: crypt.exe " << COMMAND_CRYPT << '|' << COMMAND_DECRYPT
			  << "<input file> <output file> <key=0..255>\n";
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
	if ((key < 0) || (key > 255) || wasErr)
	{
		std::cout << "Wrong key: " << argv[4] << '\n';
		ShowUsage();
		return 1;
	}

	bool ok = Run(command, inputFileName, outputFileName, static_cast<char>(key));
	if (!ok)
	{
		ShowUsage();
		return 1;
	}

	return 0;
}
