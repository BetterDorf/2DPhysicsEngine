#include "Entity.h"
#include "SFMLUtils.h"
#include "World.h"

Entity::Entity(World* world, std::unique_ptr<Rigibody> rigibody, std::unique_ptr<sf::Drawable> drawable)
: id_(curId++), rbPtr_(std::move(rigibody)), visualPtr_(std::move(drawable))
{
	world->AddEntity(this);
}

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