#include <iostream>
#include "PhysicalWorld.h"
#include "CircleCollider.h"
#include "SFMLUtils.h"
#include "World.h"

int main()
{
    World world;

	std::unique_ptr<Rigibody> rb;
	rb = std::make_unique<Rigibody>(std::make_unique<CircleCollider>(), Vector(5.0, -4.0), Vector(-40.0, 0.0));
	std::unique_ptr<Rigibody> rb2;
	rb2 = std::make_unique<Rigibody>(std::make_unique<CircleCollider>(), Vector(2.0, -4.0), Vector(20.0, 5.0));
    std::unique_ptr<Rigibody> rb3;
    rb3 = std::make_unique<Rigibody>(std::make_unique<CircleCollider>(), Vector(2.0, 0.0), Vector(4.0, -49.0));
    std::unique_ptr<Rigibody> rb4;
    rb4 = std::make_unique<Rigibody>(std::make_unique<CircleCollider>(), Vector(0.0, 1.0), Vector(34.0, -49.0));

	Entity e(&world, std::move(rb), std::make_unique<sf::CircleShape>(SFMLUtils::PIXELSTOMETERSRATIO/ 2));
    Entity e2(&world, std::move(rb2), std::make_unique<sf::CircleShape>(SFMLUtils::PIXELSTOMETERSRATIO / 2));
    Entity e3(&world, std::move(rb3), std::make_unique<sf::CircleShape>(SFMLUtils::PIXELSTOMETERSRATIO / 2));
    Entity e4(&world, std::move(rb4), std::make_unique<sf::CircleShape>(SFMLUtils::PIXELSTOMETERSRATIO / 2));

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "window");

    double timeStep = 1.0 / 6000.0;
    Vector cameraPos(- (window.getSize().x / SFMLUtils::PIXELSTOMETERSRATIO) / 2.0,
        - (window.getSize().y / SFMLUtils::PIXELSTOMETERSRATIO) / 2.0);

    while (window.isOpen())
    {
        //REMOVE THAT LATER
        world.Update();

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
        e3.GetRigibody().AddForceContinuous(Vector(0.0, -9.81), timeStep);
        e4.GetRigibody().AddForceContinuous(Vector(0.0, -9.81), timeStep);

        PhysicalWorld::Tick(timeStep);

        e.UpdateGraphicsPosition(cameraPos);
        window.draw(e);

        e2.UpdateGraphicsPosition(cameraPos);
        window.draw(e2);

        e3.UpdateGraphicsPosition(cameraPos);
        window.draw(e3);

        e4.UpdateGraphicsPosition(cameraPos);
        window.draw(e4);

        window.display();
    }

    std::cout << "Hello World !\n";
    return EXIT_SUCCESS;
}