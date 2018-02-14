#include <iostream>
#include <fstream>
#include <string>


std::string ReplaceInLine(std::string &srcLine, const std::string searchString, const std::string replaceString)
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
	const std::string searchString, const std::string replaceString)
{
	std::string line;

	while (std::getline(input, line))
	{
		const std::string result = ReplaceInLine(line, searchString, replaceString);
		output << result << '\n';
	}
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

	std::ifstream inputFile(argv[1]);
	if (!inputFile.is_open()) 
	{
		std::cout << "Failed to open input file: " << argv[1] << '\n';
		return 1;
	}

	std::ofstream outputFile(argv[2]);
	if (!outputFile.is_open())
	{
		std::cout << "Failed to open output file: " << argv[2] << '\n';
		return 1;
	}

	std::string searchString = argv[3];
	std::string replaceString = argv[4];

	Replace(inputFile, outputFile, searchString, replaceString);

	return 0;
}