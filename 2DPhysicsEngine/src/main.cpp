#include <iostream>
#include "Entity.h"

int main()
{
    Rigibody rb(Vector(5.0, -4.0), Vector(3.0, 7.0));

    Entity e(std::make_unique<Rigibody>(rb), std::make_unique<sf::CircleShape>(100));
    Entity e2(std::make_unique<Rigibody>(rb), std::make_unique<sf::CircleShape>(50));
    e2.GetRigibody().position = Vector(0.0,0.0);

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "window");

    double timeStep = 1.0 / 600.0;
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
        e.PhysicUpdate(timeStep);
        e2.PhysicUpdate(timeStep);

        e.UpdateGraphicsPosition(cameraPos);
        window.draw(e);

        e2.UpdateGraphicsPosition(cameraPos);
        window.draw(e2);

        window.display();
    }

    std::cout << "Hello World !\n";
    return EXIT_SUCCESS;
}