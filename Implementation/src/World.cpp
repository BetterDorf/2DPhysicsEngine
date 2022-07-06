#include "World.h"

#include <random>

#include "PhysicalWorld.h"
#include "SFMLUtils.h"

#include <ranges>

#include "CircleShape.h"

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

    //Move camera to be in center of the screen
    cameraPos_ = SFMLUtils::sfVectorToVector2(static_cast<sf::Vector2f>(window_->getSize())) * -0.5;
    std::cout << cameraPos_.ToString();

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
        if (event.type == sf::Event::MouseButtonPressed)
        {
            ClickEvent(event);
        }
    }
    constexpr double cameraSpeed = 50.0;

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

void World::ClickEvent(const sf::Event event)
{
    std::cout << std::to_string(sf::Mouse::getPosition(*window_).x) + " " + std::to_string(sf::Mouse::getPosition(*window_).y) + " "
	+ SFMLUtils::ScreenToWorldPos(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window_)), cameraPos_).ToString() + " " + cameraPos_.ToString();

    std::random_device rd;
    std::default_random_engine eng(rd());
    const std::uniform_real_distribution<double> distr(-5.0, 5.0);

	if (event.mouseButton.button == sf::Mouse::Left)
	{
        double rad = abs(distr(eng)) + 1;
        auto rb = std::make_unique<Rigibody>(std::make_unique<CircleShape>(rad),
            SFMLUtils::ScreenToWorldPos((static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window_))), cameraPos_), Vector2D(), rad);
        AddEntity(std::make_unique<Entity>(std::move(rb)));
	}
}
