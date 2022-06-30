#include "World.h"
#include "PhysicalWorld.h"
#include "SFMLUtils.h"

#include <ranges>

void World::AddEntity(std::unique_ptr<Entity> ent)
{
	entities_.emplace(std::make_pair(ent->GetId(), std::move(ent)));
}

void World::RemoveEntity(const long id)
{
    entities_.at(id).reset();
	entities_.erase(id);
}

void World::Start()
{
    sf::Clock clock;
    sf::Time collectedEllapse;
    sf::Time lastPhysicFrame;

	while (window_->isOpen())
	{
        sf::Time elapsed = clock.restart();

		Update(static_cast<double>(elapsed.asSeconds()));

        if (static_cast<double>(elapsed.asSeconds()) > SFMLUtils::MAXTIMESTEP)
            continue;

        collectedEllapse += elapsed;


        if (static_cast<double>((collectedEllapse - lastPhysicFrame).asSeconds()) > physicsTimestep_)
        {
			UpdatePhysics(static_cast<double>((collectedEllapse - lastPhysicFrame).asSeconds()));
            lastPhysicFrame = collectedEllapse;
        }
	}
}

void World::Update(const double deltaTime)
{
	//Process events
    sf::Event event{};

    while (window_->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window_->close();
            return;
        }
    }
    constexpr double cameraSpeed = 500.0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        cameraPos_ += Vector2D(0, cameraSpeed * deltaTime);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        cameraPos_ += Vector2D(0, -cameraSpeed * deltaTime);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        cameraPos_ += Vector2D(cameraSpeed * deltaTime, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        cameraPos_ += Vector2D(-cameraSpeed * deltaTime, 0);

    //Draw
    window_->clear();

    for (auto& ent : entities_ | std::views::values)
    {
        ent->UpdateGraphicsPosition(cameraPos_);
        window_->draw(*ent);
    }

    window_->display();
}

void World::UpdatePhysics(const double deltaTime)
{
	PhysicalWorld::Tick(deltaTime);
}
