#include <iostream>
#include <fstream>
#include <string>

std::string ReplaceInLine(const std::string &srcLine,
	const std::string &searchString, const std::string &replaceString)
{
	std::string result;
	size_t prevPos = 0;
	size_t pos = 0;

	while (pos != std::string::npos)
	{
		pos = srcLine.find(searchString, pos);
		result.append(srcLine, prevPos, pos - prevPos);

		if (pos != std::string::npos)
		{
			result.append(replaceString);
			pos += searchString.length();
		}

		prevPos = pos;
	}

	return result;
}

void Replace(std::istream &input, std::ostream &output,
	const std::string &searchString, const std::string &replaceString, bool &wasError)
{
	std::string line;

	while (std::getline(input, line))
	{
		const std::string result = ReplaceInLine(line, searchString, replaceString);
		output << result << '\n';
	}

	output.flush();
	wasError = !output;
}

bool Replace(const std::string &inputFile, const std::string &outputFile,
	const std::string &searchString, const std::string &replaceString)
{
	std::ifstream input(inputFile);
	if (!input.is_open())
	{
		std::cout << "Failed to open input file: " << inputFile << '\n';
		return 1;
	}

	std::ofstream output(outputFile);
	if (!output.is_open())
	{
		std::cout << "Failed to open output file: " << outputFile << '\n';
		return 1;
	}

	bool wasError = false;
	Replace(input, output, searchString, replaceString, wasError);

	if (wasError)
	{
		std::cout << "Failed to replace\n";
	}

	return !wasError;
}

const int ARGS_COUNT = 4;

int main(int argc, char* argv[]) 
{
	if (argc != ARGS_COUNT + 1) 
	{
		std::cout << "Invalid arguments count\n"
			<< "Usage: replace.exe <input file> <output file> <search string> <replace string>\n";
		return 1;
	}

	bool ok = Replace(argv[1], argv[2], argv[3], argv[4]);
	if (!ok)
	{
		return 1;
	}

	return 0;
}