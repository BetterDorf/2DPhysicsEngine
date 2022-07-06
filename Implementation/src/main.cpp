#include <iostream>
#include "ConvexShape.h"
#include "CircleShape.h"
#include "World.h"

#include <random>

int main()
{
    World world(std::make_unique<sf::RenderWindow>(sf::VideoMode(1920, 1080), "2DPhysics Demoz Nemoz"), 1 / 60.0);

#pragma region Create Floor
    world.AddEntity(std::make_unique<Entity>(std::make_unique<Rigibody>(std::make_unique<ConvexShape>(std::vector<Vector2D> 
    {Vector2D(-5.0, -1.0), Vector2D(5.0, -1.0), Vector2D(-5.0, 1.0), Vector2D(0.0, 10.0), Vector2D(5.0, 1.0)}),
        Vector2D(-15.0, -5.0), Vector2D(), 1.0, true)));

    world.AddEntity(std::make_unique<Entity>(std::make_unique<Rigibody>(std::make_unique<ConvexShape>(std::vector<Vector2D>
    {Vector2D(-5.0, -1.0), Vector2D(5.0, -1.0), Vector2D(-5.0, 1.0), Vector2D(0.0, 10.0), Vector2D(5.0, 1.0)}),
        Vector2D(15.0, -5.0), Vector2D(), 1.0, true)));

    world.AddEntity(std::make_unique<Entity>(std::make_unique<Rigibody>(std::make_unique<ConvexShape>(std::vector<Vector2D>
    {Vector2D(-20.0, -2.0), Vector2D(20.0, -2.0), Vector2D(-20.0, 2.0), Vector2D(20.0, 2.0)}),
        Vector2D(0.0, -10.5), Vector2D(), 1.0, true)));
#pragma endregion

    world.Start();

    std::cout << "Hello World !\n";
    return EXIT_SUCCESS;
}