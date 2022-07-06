#include <iostream>
#include "ConvexShape.h"
#include "CircleShape.h"
#include "World.h"

#include <random>

int main()
{
    World world(std::make_unique<sf::RenderWindow>(sf::VideoMode(1920, 1080), "2DPhysics Demoz Nemoz"), 1 / 60.0);

#pragma region Create Bodies

    world.AddEntity(std::make_unique<Entity>(std::make_unique<Rigibody>(std::make_unique<ConvexShape>(std::vector<Vector2D> 
    {Vector2D(-5.0, -1.0), Vector2D(5.0, -1.0), Vector2D(-5.0, 1.0), Vector2D(0.0, 10.0), Vector2D(5.0, 1.0)}),
        Vector2D(-15.0, -5.0), Vector2D(), 1.0, true)));

    world.AddEntity(std::make_unique<Entity>(std::make_unique<Rigibody>(std::make_unique<ConvexShape>(std::vector<Vector2D>
    {Vector2D(-5.0, -1.0), Vector2D(5.0, -1.0), Vector2D(-5.0, 1.0), Vector2D(0.0, 10.0), Vector2D(5.0, 1.0)}),
        Vector2D(15.0, -5.0), Vector2D(), 1.0, true)));

    world.AddEntity(std::make_unique<Entity>(std::make_unique<Rigibody>(std::make_unique<ConvexShape>(std::vector<Vector2D>
    {Vector2D(-20.0, -2.0), Vector2D(20.0, -2.0), Vector2D(-20.0, 2.0), Vector2D(20.0, 2.0)}),
        Vector2D(0.0, -10.5), Vector2D(), 1.0, true)));
//    srand(time(nullptr));
//    for (int i = 0; i < 20 ; i++)
//    {
//	   if (rand() % 2 == 0)
//	   {
//            int edges = rand() % 10;
//            if (edges < 3)
//                edges = 3;
//            std::vector<Vector2D> points(edges);
//            for (int e = 0; e < edges; e++)
//            {
//                points.emplace_back(Vector2D(distr(eng), distr(eng)));
//            }
//
//            ConvexShape shape(points);
//            auto rb = std::make_unique<Rigibody>(std::make_unique<ConvexShape>(shape),
//                Vector2D(rand() % 30 - 15, rand() % 30 - 15), Vector2D(/*rand() % 10 - 5, rand() % 10 - 5*/), edges, false, false);
//            world.AddEntity(std::make_unique<Entity>(std::move(rb)));
//	   }
//        else
//        {
//        double rad = rand() % 5 + 0.1;
//            auto rb = std::make_unique<Rigibody>(std::make_unique<CircleShape>(rad),
//                Vector2D(rand() % 30 - 15, rand() % 30 - 15), Vector2D(rand() % 10 - 5, rand() % 10 - 5), rad, false, false);
//            world.AddEntity(std::make_unique<Entity>(std::move(rb)));
//        }
//
//        std::cout << "made shape" + std::to_string(i) << std::endl;
//    }
//
//    
#pragma endregion

    //Testing polygonal shapes
    
    //std::cout << shape.GetFurthestPoint(Vector2D(-1.0, 0.0)).ToString() << std::endl;

    world.Start();

    std::cout << "Hello World !\n";
    return EXIT_SUCCESS;
}