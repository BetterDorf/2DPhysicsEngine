#pragma once
#include <vector>

#include <string>

class Matrix
{
public:
	Matrix() = default;
	explicit Matrix(std::vector<std::vector<double>> v);
	Matrix(int l, int c, std::vector<std::vector<double>> v);

	static bool compareOrder(const Matrix&, const Matrix&);

	[[nodiscard]] std::string ToString() const;

	[[nodiscard]] Matrix operator+(const Matrix&) const;
	Matrix& operator+= (const Matrix&);
	

private:
	int lines = 0;
	int columns = 0;

	std::vector<std::vector<double>> values;
};
