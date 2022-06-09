#pragma once
#include <SFML/Graphics.hpp>
#include "Rigibody.h"

class Entity :public sf::Drawable, public sf::Transformable
{
public:
	Entity(std::unique_ptr<Rigibody>, std::unique_ptr<sf::Drawable>);

	[[nodiscard]] Rigibody GetRigibody() const { return  *rbPtr; }

	bool flaggedForRemoval = false;

	void PhysicUpdate(double timeElapsed);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	void UpdateShapePosition();

	std::unique_ptr<Rigibody> rbPtr;
	std::unique_ptr<sf::Drawable> visualPtr;
};