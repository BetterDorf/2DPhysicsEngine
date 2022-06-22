#include <iostream>
#include "PhysicalWorld.h"
#include "CircleCollider.h"
#include "SFMLUtils.h"
#include "World.h"

int main()
{
    World world(std::make_unique<sf::RenderWindow>(sf::VideoMode(1920, 1080), "window"));

#pragma region Create Bodies
    auto rb = std::make_unique<Rigibody>(std::make_unique<CircleCollider>(), Vector(5.0, -4.0), Vector(-4.0, 0.0));
    auto rb2 = std::make_unique<Rigibody>(std::make_unique<CircleCollider>(), Vector(2.0, -4.0), Vector(2.0, 0.5));
    auto rb3 = std::make_unique<Rigibody>(std::make_unique<CircleCollider>(), Vector(2.0, 0.0), Vector(2.5, -5.0));
    auto rb4 = std::make_unique<Rigibody>(std::make_unique<CircleCollider>(), Vector(0.0, 1.0), Vector(3.0, -9.0));

    world.AddEntity(std::make_unique<Entity>(std::move(rb), std::make_unique<sf::CircleShape>(SFMLUtils::PIXELSTOMETERSRATIO / 2)));
    world.AddEntity(std::make_unique<Entity>(std::move(rb2), std::make_unique<sf::CircleShape>(SFMLUtils::PIXELSTOMETERSRATIO / 2)));
    world.AddEntity(std::make_unique<Entity>(std::move(rb3), std::make_unique<sf::CircleShape>(SFMLUtils::PIXELSTOMETERSRATIO / 2)));
    world.AddEntity(std::make_unique<Entity>(std::move(rb4), std::make_unique<sf::CircleShape>(SFMLUtils::PIXELSTOMETERSRATIO / 2)));
#pragma endregion
    world.Start();

    std::cout << "Hello World !\n";
    return EXIT_SUCCESS;
}