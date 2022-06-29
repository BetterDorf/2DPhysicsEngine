#include "Entity.h"
#include "SFMLUtils.h"
#include "World.h"
#include "ConvexShape.h"

Entity::Entity(std::unique_ptr<Rigibody> rigibody, std::unique_ptr<sf::Drawable> drawable, const sf::Vector2f centerOffset)
: id_(curId++), rbPtr_(std::move(rigibody)), visualPtr_(std::move(drawable))
{
	this->setOrigin(centerOffset);
}

Entity::Entity(std::unique_ptr<Rigibody> rigibody): id_(curId++), rbPtr_(std::move(rigibody))
{
	switch (rbPtr_->GetCollider()->GetShapeType())
	{
		case PhysicShape::ShapeType::None: break;
		case PhysicShape::ShapeType::Circle: 
			visualPtr_ = std::make_unique<sf::CircleShape>(rbPtr_->GetCollider()->GetBoundingCircleRad());
			break;
		case PhysicShape::ShapeType::Polygon:
			const auto shape = dynamic_cast<ConvexShape*>(rbPtr_->GetCollider());
			int pointCount = static_cast<int>(shape->GetPoints().size());
			sf::ConvexShape visualShape(pointCount);
			for(int i = 0; i < pointCount; i++)
			{
				visualShape.setPoint(i, SFMLUtils::vector2ToSFML(shape->GetPoints()[i]));
			}
			visualPtr_ = std::make_unique<sf::ConvexShape>(visualShape);
			break;
	}
	
}

Entity::Entity(std::unique_ptr<Rigibody> rigibody, std::unique_ptr<sf::CircleShape> drawable)
	: id_(curId++), rbPtr_(std::move(rigibody)), visualPtr_(std::move(drawable))
{
	const float radius = dynamic_cast<sf::CircleShape*>(visualPtr_.get())->getRadius();
	this->setOrigin(sf::Vector2f(radius, radius));
}

Entity::Entity(std::unique_ptr<Rigibody> rigibody, std::unique_ptr<sf::RectangleShape> drawable)
	: id_(curId++), rbPtr_(std::move(rigibody)), visualPtr_(std::move(drawable))
{
	const sf::Vector2f dimensions = dynamic_cast<sf::RectangleShape*>(visualPtr_.get())->getSize();
	this->setOrigin(dimensions / 2.0f);
}

Entity::Entity(std::unique_ptr<Rigibody> rigibody, std::unique_ptr<sf::Sprite> drawable)
	: id_(curId++), rbPtr_(std::move(rigibody)), visualPtr_(std::move(drawable))
{
	const auto spritePtr = dynamic_cast<sf::Sprite*>(visualPtr_.get());
	const auto dimensions = sf::Vector2f(spritePtr->getTextureRect().height, spritePtr->getTextureRect().width);
	this->setOrigin(dimensions / 2.0f);
}

void Entity::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	target.draw(*visualPtr_, this->getTransform());
}

void Entity::UpdateGraphicsPosition(const Vector2D cameraPos)
{
	const sf::Vector2f pos = SFMLUtils::WorldToScreenPos(rbPtr_->GetPos(), cameraPos);
	setPosition(pos);
}