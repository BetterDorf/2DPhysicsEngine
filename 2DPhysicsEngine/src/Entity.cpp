#include "Entity.h"

Entity::Entity(std::unique_ptr<Rigibody> rigibody, std::unique_ptr<sf::Drawable> drawable)
: rbPtr(std::move(rigibody)), visualPtr(std::move(drawable))
{}

void Entity::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	target.draw(*visualPtr, states);
}

void Entity::PhysicUpdate(const double timeElapsed)
{
	rbPtr->Update(timeElapsed);

	UpdateShapePosition();
}

void Entity::UpdateShapePosition()
{
 	
}

