#pragma once
#include <SFML/Graphics.hpp>
#include "Rigibody.h"

class World;

class Entity final : public sf::Drawable, public sf::Transformable
{
public:
	Entity(std::unique_ptr<Rigibody>, std::unique_ptr<sf::CircleShape>);
	Entity(std::unique_ptr<Rigibody>, std::unique_ptr<sf::RectangleShape>);
	Entity(std::unique_ptr<Rigibody>, std::unique_ptr<sf::Sprite>);
	Entity(std::unique_ptr<Rigibody>, std::unique_ptr<sf::Drawable>, sf::Vector2f centerOffset);
	explicit Entity(std::unique_ptr<Rigibody>);

	[[nodiscard]] Rigibody& GetRigibody() const { return *rbPtr_; }

	bool flaggedForRemoval = false;

	void UpdateGraphicsPosition(Vector2D cameraPos);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	int GetId() const { return id_; }

private:
	int id_;
	inline static int curId = 0;

	std::unique_ptr<Rigibody> rbPtr_;
	std::unique_ptr<sf::Drawable> visualPtr_;
};