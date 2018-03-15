#include <fstream>
#include <iostream>
#include <queue>
#include <string>

const size_t SIZE = 100;
const size_t TOTAL_SIZE = SIZE + 2; // size with borders

enum class CellType : char
{
	EMPTY = ' ',
	FILLED = '.',
	SOURCE = 'O',
	BORDER = '#',
	IN_QUEUE = '*',
};

struct Field
{
	CellType cells[TOTAL_SIZE][TOTAL_SIZE];
};

bool IsBorderCell(const size_t row, const size_t col)
{
	return row == 0 || row == TOTAL_SIZE - 1 || col == 0 || col == TOTAL_SIZE - 1;
}

void InitField(Field& field)
{
	for (size_t row = 0; row < TOTAL_SIZE; row++)
	{
		for (size_t col = 0; col < TOTAL_SIZE; col++)
		{
			field.cells[row][col] = IsBorderCell(row, col) ? CellType::BORDER : CellType::EMPTY;
		}
	}
}

void ReadField(std::istream& input, Field& field)
{
	size_t row = 0;
	while (input && row < SIZE)
	{
		std::string line;
		std::getline(input, line);
		for (size_t col = 0; col < line.length() && col < SIZE; col++)
		{
			field.cells[row + 1][col + 1] = static_cast<CellType>(line[col]);
		}
		row++;
	}
}

struct Position
{
	size_t row;
	size_t col;
};

void InitQueue(std::queue<Position>& q, const Field& field)
{
	for (size_t row = 0; row < TOTAL_SIZE; row++)
	{
		for (size_t col = 0; col < TOTAL_SIZE; col++)
		{
			if (field.cells[row][col] == CellType::SOURCE)
			{
				q.push(Position{ row, col });
			}
		}
	}
}

Position GetFieldSize(const Field& field)
{
	size_t maxRow = 0;
	size_t maxCol = 0;
	for (size_t row = 1; row < TOTAL_SIZE - 1; row++)
	{
		for (size_t col = 1; col < TOTAL_SIZE - 1; col++)
		{
			if (field.cells[row][col] != CellType::EMPTY)
			{
				maxRow = std::max(maxRow, row);
				maxCol = std::max(maxCol, col);
			}
		}
	}

	return Position{ maxRow, maxCol };
}

void PrintField(std::ostream& output, const Field& field)
{
	auto size = GetFieldSize(field);

	for (size_t row = 1; row <= size.row; row++)
	{
		for (size_t col = 1; col <= size.col; col++)
		{
			output << static_cast<char>(field.cells[row][col]);
		}
		output << '\n';
	}
}

struct Offsets // struct Position is using size_t
{
	int row;
	int col;
};

const size_t DIR_COUNT = 4;
const Offsets OFFSETS[DIR_COUNT] = {
	{ 1, 0 },
	{ 0, 1 },
	{ -1, 0 },
	{ 0, -1 },
};

void FillNeighbours(Field& field, std::queue<Position>& q, const Position& pos)
{
	for (size_t dir = 0; dir < DIR_COUNT; dir++)
	{
		Position newPos = pos;
		newPos.row += OFFSETS[dir].row;
		newPos.col += OFFSETS[dir].col;
		if (field.cells[newPos.row][newPos.col] == CellType::EMPTY)
		{
			q.push(newPos);
			field.cells[newPos.row][newPos.col] = CellType::IN_QUEUE;
		}
	}
}

void Fill(Field& field)
{
	std::queue<Position> q;
	InitQueue(q, field);

	while (!q.empty())
	{
		Position pos = q.front();
		q.pop();

		CellType& currentCell = field.cells[pos.row][pos.col];

		if (currentCell == CellType::IN_QUEUE)
		{
			currentCell = CellType::FILLED;
		}

		FillNeighbours(field, q, pos);
	}
}

void Fill(std::istream& input, std::ostream& output)
{
	Field field;
	InitField(field);
	ReadField(input, field);

	Fill(field);

	PrintField(output, field);
}

bool Fill(const std::string& inputFileName, const std::string& outputFileName)
{
	std::ifstream inputFile(inputFileName);
	if (!inputFile.is_open())
	{
		std::cerr << "Failed to open input file: " << inputFileName << '\n';
		return false;
	}

	std::ofstream outputFile(outputFileName);
	if (!outputFile.is_open())
	{
		std::cerr << "Failed to open output file: " << outputFileName << '\n';
		return false;
	}

	Fill(inputFile, outputFile);

	return static_cast<bool>(outputFile);
}

void ShowUsage()
{
	std::cerr << "Usage: fill.exe <input file> <output file>\n";
}

const int ARGS_COUNT = 2;

int main(int argc, char* argv[])
{
	if (argc != ARGS_COUNT + 1)
	{
		std::cout << "Invalid arguments count\n";
		ShowUsage();
		return 1;
	}

	std::string inputFileName(argv[1]);
	std::string outputFileName(argv[2]);

	bool ok = Fill(inputFileName, outputFileName);
	if (!ok)
	{
		ShowUsage();
		return 1;
	}

	return 0;
}
