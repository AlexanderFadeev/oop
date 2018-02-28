#include <iostream>
#include <fstream>
#include <string>
#include <queue>

const size_t SIZE = 100;
const size_t TOTAL_SIZE = SIZE + 2; // size with borders

enum class CellType : char {
	EMPTY    = ' ',
	FILLED   = '.',
	SOURCE   = 'O',
	BORDER   = '#',
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

void InitField(Field &field)
{
	for (size_t row = 0; row < TOTAL_SIZE; row++)
	{
		for (size_t col = 0; col < TOTAL_SIZE; col++)
		{
			field.cells[row][col] = IsBorderCell(row, col) ? CellType::BORDER : CellType::EMPTY;
		}
	}
}

void ReadField(std::istream &input, Field &field)
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

typedef std::pair<size_t, size_t> Position;

void InitQueue(std::queue<Position> &q, const Field &field)
{
	for (size_t row = 0; row < TOTAL_SIZE; row++)
	{
		for (size_t col = 0; col < TOTAL_SIZE; col++)
		{
			if (field.cells[row][col] == CellType::SOURCE)
			{
				q.push(Position{row, col});
			}
		}
	}
}

std::pair<size_t, size_t> GetFieldSize(const Field &field)
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

	return std::make_pair(maxRow, maxCol);
}

void PrintField(std::ostream &output, const Field &field)
{
	auto size = GetFieldSize(field);

	for (size_t row = 1; row <= size.first; row++)
	{
		for (size_t col = 1; col <= size.second; col++)
		{
			output << static_cast<char>(field.cells[row][col]);
		}
		output << '\n';
	}
}

void Fill(Field &field) {
	std::queue<Position> q;
	InitQueue(q, field);

	while (!q.empty())
	{
		Position pos = q.front();
		q.pop();

		if (field.cells[pos.first][pos.second] == CellType::IN_QUEUE)
		{
			field.cells[pos.first][pos.second] = CellType::FILLED;
		}

		const size_t dirCount = 4;
		const int dRow[dirCount] = { 1, 0, -1, 0 };
		const int dCol[dirCount] = { 0, 1, 0, -1 };

		for (size_t dir = 0; dir < dirCount; dir++)
		{
			Position newPos = pos;
			newPos.first += dRow[dir];
			newPos.second += dCol[dir];
			if (field.cells[newPos.first][newPos.second] == CellType::EMPTY)
			{
				q.push(newPos);
				field.cells[newPos.first][newPos.second] = CellType::IN_QUEUE;
			}
		}
	}
}

void Fill(std::istream &input, std::ostream &output) 
{
	Field field;
	InitField(field);
	ReadField(input, field);

	Fill(field);

	PrintField(output, field);
}

void ShowUsage()
{
	std::cout << "Usage: fill.exe <input file> <output file>\n";
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

	std::ifstream inputFile(argv[1]);
	if (!inputFile.is_open())
	{
		std::cout << "Failed to open input file: " << argv[1] << '\n';
		ShowUsage();
		return 1;
	}

	std::ofstream outputFile(argv[2]);
	if (!outputFile.is_open())
	{
		std::cout << "Failed to open output file: " << argv[2] << '\n';
		ShowUsage();
		return 1;
	}

	Fill(inputFile, outputFile);

	return 0;
}