#include "World.h"

#include <random>

#include "PhysicalWorld.h"
#include "SFMLUtils.h"

#include <ranges>

#include "CircleShape.h"
#include "ConvexShape.h"

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
    std::random_device rd;
    std::default_random_engine eng(rd());

	if (event.mouseButton.button == sf::Mouse::Left)
	{
        const std::uniform_real_distribution<double> radiusdistr(0.0, 3.0);

        double rad = abs(radiusdistr(eng)) + 1;
        auto rb = std::make_unique<Rigibody>(std::make_unique<CircleShape>(rad),
            SFMLUtils::ScreenToWorldPos((static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window_))), cameraPos_), Vector2D(), rad);
        AddEntity(std::make_unique<Entity>(std::move(rb)));
	}
    else if (event.mouseButton.button == sf::Mouse::Right)
    {
        const std::uniform_int_distribution<int> edgesNumDistr(0, 5);
        const std::uniform_real_distribution<double> edgeDistr(-3.0, 3.0);

        int edges = abs(static_cast<int>(edgesNumDistr(eng)));
        if (edges < 3)
            edges = 3;
        std::vector<Vector2D> points(edges);
        for (int e = 0; e < edges; e++)
        {
            points.emplace_back(Vector2D(edgeDistr(eng), edgeDistr(eng)));
        }

        ConvexShape shape(points);
        auto rb = std::make_unique<Rigibody>(std::make_unique<ConvexShape>(shape),
            SFMLUtils::ScreenToWorldPos((static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window_))), cameraPos_),
            Vector2D(), edges, false, true);
        AddEntity(std::make_unique<Entity>(std::move(rb)));
    }
}
