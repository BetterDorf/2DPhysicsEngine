#include <iostream>
#include "PhysicalWorld.h"
#include "CircleShape.h"
#include "ConvexShape.h"
#include "SFMLUtils.h"
#include "World.h"

int main()
{
    World world(std::make_unique<sf::RenderWindow>(sf::VideoMode(1920, 1080), "2DPhysics Demoz Nemoz"), 1 / 60.0);

#pragma region Create Bodies
    ConvexShape shape(std::vector{ Vector2D(0.0, 0.0), Vector2D(-1.0, 2.0), Vector2D(1.0, 3.0), Vector2D(3, 2), Vector2D(3, -2) });
    ConvexShape shape2(std::vector{ Vector2D(-1.0, 3.0),Vector2D(1.0, 4.0),Vector2D(0.0, 0.0), Vector2D(3.0, 3.0) });

    /*auto rb = std::make_unique<Rigibody>(std::make_unique<CircleShape>(), Vector2D(5.0, -4.0), Vector2D(-7.0, 1.5), 10.0);
    auto rb2 = std::make_unique<Rigibody>(std::make_unique<CircleShape>(), Vector2D(2.0, -4.0), Vector2D(0.0, 0.5));
    auto rb3 = std::make_unique<Rigibody>(std::make_unique<CircleShape>(), Vector2D(2.0, 0.0), Vector2D(0.0, -10.0));*/
    auto rb4 = std::make_unique<Rigibody>(std::make_unique<ConvexShape>(shape), Vector2D(0.0, 0.0), Vector2D(0.0, 0.0), 1.0, false, false);
    auto rb5 = std::make_unique<Rigibody>(std::make_unique<ConvexShape>(shape2), Vector2D(6.0, 0.0), Vector2D(-1.0, 0.0), 1.0, false, false);

    /*world.AddEntity(std::make_unique<Entity>(std::move(rb), std::make_unique<sf::CircleShape>(SFMLUtils::PIXELSTOMETERSRATIO * 0.5)));
    world.AddEntity(std::make_unique<Entity>(std::move(rb2), std::make_unique<sf::CircleShape>(SFMLUtils::PIXELSTOMETESRATIO * 0.5)));
    world.AddEntity(std::make_unique<Entity>(std::move(rb3), std::make_unique<sf::CircleShape>(SFMLUtils::PIXELSTOMETERSRATIO * 0.5)));*/
    world.AddEntity(std::make_unique<Entity>(std::move(rb4)));
    world.AddEntity(std::make_unique<Entity>(std::move(rb5)));
#pragma endregion

    //Testing polygonal shapes
    
    //std::cout << shape.GetFurthestPoint(Vector2D(-1.0, 0.0)).ToString() << std::endl;

    world.Start();

    std::cout << "Hello World !\n";
    return EXIT_SUCCESS;
}