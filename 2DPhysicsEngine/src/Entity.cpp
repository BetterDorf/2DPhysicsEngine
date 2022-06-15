#include "Entity.h"
#include "SFMLUtils.h"

Entity::Entity(std::unique_ptr<Rigibody> rigibody, std::unique_ptr<sf::Drawable> drawable)
: rbPtr(std::move(rigibody)), visualPtr(std::move(drawable))
{}

void Entity::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	target.draw(*visualPtr, this->getTransform());
}

void Entity::PhysicUpdate(const double timeElapsed) const
{
	rbPtr->Update(timeElapsed);
}

void Entity::UpdateGraphicsPosition(const Vector cameraPos)
{
	const sf::Vector2f pos = SFMLUtils::WorldToScreenPos(rbPtr->position, cameraPos);
	setPosition(pos);
}

