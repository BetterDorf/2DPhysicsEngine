#include "Entity.h"
#include "SFMLUtils.h"

Entity::Entity(std::unique_ptr<Rigibody> rigibody, std::unique_ptr<sf::Drawable> drawable)
: rbPtr_(std::move(rigibody)), visualPtr_(std::move(drawable))
{}

void Entity::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	target.draw(*visualPtr_, this->getTransform());
}

void Entity::PhysicUpdate(const double timeElapsed) const
{
	rbPtr_->Update(timeElapsed);
}

void Entity::UpdateGraphicsPosition(const Vector cameraPos)
{
	const sf::Vector2f pos = SFMLUtils::WorldToScreenPos(rbPtr_->GetPos(), cameraPos);
	setPosition(pos);
}