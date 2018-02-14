#include <iostream>
#include <fstream>
#include <string>


std::string ReplaceInLine(const std::string &srcLine,
	const std::string &searchString, const std::string &replaceString)
{
	std::string result;
	size_t startPos = 0;
	size_t searchPos = 0;

	while (searchPos != std::string::npos)
	{
		searchPos = srcLine.find(searchString, searchPos);
		if (searchPos != std::string::npos)
		{
			const size_t endPos = searchPos;
			const size_t len = endPos - startPos;
			result.append(srcLine, startPos, len);
			result.append(replaceString);
			searchPos += searchString.length();
			startPos = searchPos;
		}
	}
	
	if (startPos < srcLine.length())
	{
		const size_t len = srcLine.length() - startPos;
		result.append(srcLine, startPos, len);
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