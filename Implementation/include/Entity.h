#pragma once
#include <SFML/Graphics.hpp>
#include "Rigibody.h"

class Entity final :public sf::Drawable, public sf::Transformable
{
public:
	Entity(std::unique_ptr<Rigibody>, std::unique_ptr<sf::Drawable>);

	[[nodiscard]] Rigibody& GetRigibody() const { return *rbPtr_; }

	bool flaggedForRemoval = false;

	void PhysicUpdate(double timeElapsed) const;
	void UpdateGraphicsPosition(Vector cameraPos);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	std::unique_ptr<Rigibody> rbPtr_;
	std::unique_ptr<sf::Drawable> visualPtr_;
};