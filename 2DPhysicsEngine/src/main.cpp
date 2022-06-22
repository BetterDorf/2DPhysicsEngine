#include <iostream>
#include "Entity.h"
#include "PhysicalWorld.h"

#include "CircleCollider.h"

int main()
{
	std::unique_ptr<Rigibody> rb;
	rb = std::make_unique<Rigibody>(Vector(5.0, -4.0), Vector(0.3, 0.7));
	std::unique_ptr<Rigibody> rb2;
	rb2 = std::make_unique<Rigibody>(Vector(0.0, -10.0), Vector(7.3, 2.0));

	Entity e(std::move(rb), std::make_unique<sf::CircleShape>(100));
    Entity e2(std::move(rb2), std::make_unique<sf::CircleShape>(50));

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "window");

    double timeStep = 1.0 / 60.0;
    Vector cameraPos;

    while (window.isOpen())
    {
        sf::Event event{};

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return 0;
            }
        }
        constexpr double cameraSpeed = 5.0;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
            cameraPos += Vector(0, cameraSpeed);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
            cameraPos += Vector(0, -cameraSpeed);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
            cameraPos += Vector(cameraSpeed, 0) ;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
            cameraPos += Vector(-cameraSpeed, 0);

        window.clear();

        e.GetRigibody().AddForceContinuous(Vector(0.0, -9.81), timeStep);
        e2.GetRigibody().AddForceContinuous(Vector(0.0, -9.81), timeStep);

        PhysicalWorld::Tick(timeStep);

        e.UpdateGraphicsPosition(cameraPos);
        window.draw(e);

        e2.UpdateGraphicsPosition(cameraPos);
        window.draw(e2);

        window.display();
    }

    std::cout << "Hello World !\n";
    return EXIT_SUCCESS;
}