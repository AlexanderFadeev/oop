#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <assert.h>

const size_t SIZE = 3;

struct Matrix3x3
{
	double items[SIZE][SIZE];
};

struct Matrix2x2
{
	double items[SIZE - 1][SIZE - 1];
};

bool ReadMatrix(std::istream &input, Matrix3x3 &matrix)
{
	for (size_t row = 0; row < SIZE; row++)
	{
		for (size_t col = 0; col < SIZE; col++)
		{
			if (!(input >> matrix.items[row][col]))
			{
				return false;
			}
		}
	}

	return true;
}

double CalcMinor(const Matrix3x3 &matrix, const size_t row, const size_t col)
{
	Matrix2x2 minorMatrix;
	for (size_t rowIndex = 0; rowIndex < SIZE; rowIndex++)
	{
		if (rowIndex == row)
		{
			continue;
		}

		for (size_t colIndex = 0; colIndex < SIZE; colIndex++)
		{
			if (colIndex == col)
			{
				continue;
			}

			const size_t rowMinor = (rowIndex > row) ? (rowIndex - 1) : rowIndex;
			const size_t colMinor = (colIndex > col) ? (colIndex - 1) : colIndex;

			const double value = matrix.items[rowIndex][colIndex];
			minorMatrix.items[rowMinor][colMinor] = value;
		}
	}

	return minorMatrix.items[0][0] * minorMatrix.items[1][1] 
		- minorMatrix.items[0][1] * minorMatrix.items[1][0];
}

double CalcSign(const size_t row, const size_t col)
{
	const bool isPositive = ((row + col) % 2 == 0);
	return isPositive ? 1 : -1;
}

double Determinant(const Matrix3x3 &matrix)
{
	double result = 0;
	const size_t row = 0;
	for (size_t col = 0; col < SIZE; col++)
	{
		const double minor = CalcMinor(matrix, row, col);
		result  += matrix.items[row][col] * minor * CalcSign(row, col);
	}
	return result;
}

bool IsZero(const double value)
{
	const double eps = 1E-12;
	return (abs(value) < eps);
}

void TransposeMatrix(Matrix3x3 &matrix)
{
	for (size_t row = 1; row < SIZE; row++)
	{
		for (size_t col = 0; col < row; col++)
		{
			std::swap(matrix.items[row][col], matrix.items[col][row]);
		}
	}
}

void CalcInverseMatrix(Matrix3x3 &inverseMatrix, const Matrix3x3 &srcMatrix, const double determinant)
{
	for (size_t row = 0; row < SIZE; row++)
	{
		for (size_t col = 0; col < SIZE; col++)
		{
			const double minor = CalcMinor(srcMatrix, row, col);
			const double sign = CalcSign(row, col);

			inverseMatrix.items[row][col] = sign * minor / determinant;
		}
	}

	TransposeMatrix(inverseMatrix);
}

void PrintMatrix(const Matrix3x3 &matrix)
{
	std::cout << std::fixed << std::setprecision(3);
	for (size_t row = 0; row < SIZE; row++)
	{
		for (size_t col = 0; col < SIZE; col++)
		{
			if (IsZero(matrix.items[row][col]))
			{
				std::cout << 0.0 << '\t';
			}
			else 
			{
				std::cout << matrix.items[row][col] << '\t';
			}
		}
		std::cout << '\n';
	}
}

bool Invert(std::istream &input)
{
	Matrix3x3 matrix;
	bool ok = ReadMatrix(input, matrix);
	if (!ok)
	{
		std::cout << "Failed to read matrix\n";
		return false;
	}

	const double det = Determinant(matrix);

	if (IsZero(det))
	{
		std::cout << "Unable to invert matrix\n";
		return true;
	}

	Matrix3x3 invertedMatrix;
	CalcInverseMatrix(invertedMatrix, matrix, det);

	PrintMatrix(invertedMatrix);

	return true;
}

void ShowUsage()
{
	std::cout << "Usage: invert.exe <matrix file>\n";
}

const int ARGS_COUNT = 1;

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

	bool ok = Invert(inputFile);
	if (!ok)
	{
		ShowUsage();
		return 1;
	}

	return 0;
}