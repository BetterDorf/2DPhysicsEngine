#include <iostream>
#include  "Rigibody.h"

int main()
{
	constexpr int totalIters = 5000;
	auto a = Rigibody(0.0, 0.0);
    a.velocity = Vector(8.0, -9.81);

    for (int iters = 0; iters < totalIters; iters++)
    {
        a.Update(1.0 / 60.0);
        std::cout << a.position.ToString() << std::endl;
    }

    std::cout << "Hello World !\n";
    return EXIT_SUCCESS;
}