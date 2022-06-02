#include <iostream>
#include <string>

#include  "Vector.h"

int main()
{
    Vector v(5, 5);
    Vector w(-2, 2);

    std::cout << "Base Vectors:\n";
    std::cout << v.ToString() + "\n" + w.ToString() + "\n";

    std::cout << "Vectors Addition and soustraction:\n";
    std::cout << (v + w).ToString() + "\n" + (v - w).ToString() + "\n";

    std::cout << "Vector multiplication with scalar:\n";
    std::cout << (v * 2.0f).ToString() + "\n" + (w / 2.0f).ToString() + "\n";

    std::cout << "Using the assignment operators\n";
    w += v;
    std::cout << w.ToString() + "\n";

    w /= 2.0f;
    std::cout << w.ToString() + "\n";

    w /= 2.0f;
    std::cout << w.ToString() + "\n";

    std::cout << "\n\nVector:\n" + v.ToString() + "\nMagnitude:\n" + std::to_string(v.Magnitude()) + "\nNormalized:\n" + v.Normalize().ToString() << std::endl;

    return EXIT_SUCCESS;
}