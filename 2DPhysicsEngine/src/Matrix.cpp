#include "Matrix.h"

#include <optional>
#include <stdexcept>

Matrix::Matrix(std::vector<std::vector<double>> v) : values(v)
{
	int l = 0;
	int c = 0;

	for (auto element : v)
	{
		l++;
	}

	if (!v.empty())
	{
		for (auto element : v[0])
		{
			c++;
		}
	}

	lines = l;
	columns = c;
}

Matrix::Matrix(const int l, const int c, std::vector<std::vector<double>> v): lines(l), columns(c), values(v)
{
}

bool Matrix::compareOrder(const Matrix& a, const Matrix&b)
{
	return a.lines == b.lines && a.columns == b.columns;
}

std::string Matrix::ToString() const
{
	std::string s;

	for (int l = 0; l < lines; l++)
	{
		s += "|";

		for (int c = 0; c < columns; c++)
		{
			s += std::to_string(values[l][c]);

			if (c != columns - 1)
				s += ", ";
		}

		s += "|\n";
	}

	return s;
}


Matrix Matrix::operator+(const Matrix& other) const
{
	if (!compareOrder(*this, other))
		throw std::invalid_argument("Matrices don't have the same order");

	std::vector<std::vector<double>> newVals = values;

	for (int l = 0; l < lines ; l++)
	{
		for (int c = 0; c < columns; c++)
		{
			newVals[l][c] = values[l][c] + other.values[l][c];
		}
	}

	Matrix newMatrix(lines, columns, newVals);
	return newMatrix;
}

Matrix& Matrix::operator+=(const Matrix& other)
{
	*this = *this + other;

	return *this;
}
