#include <iostream>
#include "PhysicalWorld.h"
#include "CircleShape.h"
#include "PolygonShape.h"
#include "SFMLUtils.h"
#include "World.h"

int main()
{
    World world(std::make_unique<sf::RenderWindow>(sf::VideoMode(1920, 1080), "2DPhysics Demoz Nemoz"));

#pragma region Create Bodies
    /*auto rb = std::make_unique<Rigibody>(std::make_unique<CircleShape>(), Vector2D(5.0, -4.0), Vector2D(-7.0, 1.5), 10.0);
    auto rb2 = std::make_unique<Rigibody>(std::make_unique<CircleShape>(), Vector2D(2.0, -4.0), Vector2D(0.0, 0.5));
    auto rb3 = std::make_unique<Rigibody>(std::make_unique<CircleShape>(), Vector2D(2.0, 0.0), Vector2D(0.0, -10.0));*/
    auto rb4 = std::make_unique<Rigibody>(std::make_unique<CircleShape>(0.5), Vector2D(3.0, 0.0), Vector2D(0.0, 0.0));
    auto rb5 = std::make_unique<Rigibody>(std::make_unique<CircleShape>(1), Vector2D(6.0, 0.0), Vector2D(-4.0, 1.0));

    /*world.AddEntity(std::make_unique<Entity>(std::move(rb), std::make_unique<sf::CircleShape>(SFMLUtils::PIXELSTOMETERSRATIO * 0.5)));
    world.AddEntity(std::make_unique<Entity>(std::move(rb2), std::make_unique<sf::CircleShape>(SFMLUtils::PIXELSTOMETESRATIO * 0.5)));
    world.AddEntity(std::make_unique<Entity>(std::move(rb3), std::make_unique<sf::CircleShape>(SFMLUtils::PIXELSTOMETERSRATIO * 0.5)));*/
    world.AddEntity(std::make_unique<Entity>(std::move(rb4),
        std::make_unique<sf::CircleShape>(SFMLUtils::PIXELSTOMETERSRATIO * 0.5)));
    world.AddEntity(std::make_unique<Entity>(std::move(rb5), std::make_unique<sf::CircleShape>(SFMLUtils::PIXELSTOMETERSRATIO * 1)));
#pragma endregion

    //Testing polygonal shapes
    PolygonShape shape(std::vector {Vector2D(12.0, 13.0), Vector2D(7.0, 17.0), Vector2D( 10.0, 10.0),});
    for (auto& element : shape.GetPoints())
    {
        std::cout << element.ToString() << std::endl;
    }
    std::cout << shape.GetFurthestPoint(Vector2D(-1.0, 0.0)).ToString() << std::endl;

    world.Start();

    std::cout << "Hello World !\n";
    return EXIT_SUCCESS;
}