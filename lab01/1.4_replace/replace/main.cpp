#include <iostream>
#include <fstream>
#include <string>


void ReplaceInLine(std::string &line, const std::string searchString, const std::string replaceString) {
	size_t pos = 0;
	while (pos != std::string::npos)
	{
		pos = line.find(searchString, pos);
		if (pos != std::string::npos)
		{
			line.replace(pos, searchString.length(), replaceString);
			pos += replaceString.length();
		}
	}
}

void Replace(std::istream &input, std::ostream &output,
	const std::string searchString, const std::string replaceString)
{
	std::string line;

	while (std::getline(input, line)) {
		ReplaceInLine(line, searchString, replaceString);
		output << line << '\n';
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