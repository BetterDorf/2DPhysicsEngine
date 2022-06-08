#include <iostream>
#include <string>

#include  "Matrix.h"

int main()
{
	const std::vector<std::vector<double>> vals1{ {1, 1, 2}, {4, 3, 2} };
	const std::vector<std::vector<double>> vals2{ {4, 3, 2}, {4, 3, 2} };

    const Matrix m(vals1);
    const Matrix w(vals2);

    const Matrix t = m + w;

    std::cout << t.ToString();

    return EXIT_SUCCESS;
}