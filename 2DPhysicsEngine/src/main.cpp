#include <iostream>
#include "Entity.h"

int main()
{
	auto a = Rigibody(0.0, 0.0);
    a.velocity = Vector(8.0, -9.81);

    Entity e(std::make_unique<Rigibody>(a), std::make_unique<sf::CircleShape>(5));

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "window");

    while (window.isOpen())
    {
        window.clear();

        e.GetRigibody().AddForceImpulse(Vector(0.0, -9.81));
        e.PhysicUpdate(1.0 / 60.0);
        window.draw(e);

        window.display();
    }

    std::cout << "Hello World !\n";
    return EXIT_SUCCESS;
}