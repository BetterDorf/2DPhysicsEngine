#include "Rigibody.h"
#include "PhysicalWorld.h"

#include "PhysicsConstant.h"

Rigibody::Rigibody(std::unique_ptr<PhysicShape> col) : id_(CurId++), colliderPtr_(std::move(col))
{
	PhysicalWorld::AddRb(this);
}

Rigibody::Rigibody(std::unique_ptr<PhysicShape> col, const Vector2D pos) : Rigibody(std::move(col))
{
	position_ = pos;
}

Rigibody::Rigibody(std::unique_ptr<PhysicShape> col, const Vector2D pos, const double mass) : Rigibody(std::move(col), pos)
{
	mass_ = mass;
}

Rigibody::Rigibody(std::unique_ptr<PhysicShape> col, const Vector2D pos, const Vector2D vel) : Rigibody(std::move(col), pos)
{
	velocity_ = vel;
}

Rigibody::Rigibody(std::unique_ptr<PhysicShape> col, const Vector2D pos, const Vector2D vel, const double mass) : Rigibody(std::move(col), pos, vel)
{
	mass_ = mass;
}

Rigibody::Rigibody(std::unique_ptr<PhysicShape> col, const Vector2D pos, const Vector2D vel, const double mass, const bool isStatic)
	: Rigibody(std::move(col), pos, vel, mass)
{
	isStatic_ = isStatic;
}

Rigibody::Rigibody(std::unique_ptr<PhysicShape> col, const Vector2D pos, const Vector2D vel, const double mass, const bool isStatic, const bool useGravity)
	: Rigibody(std::move(col), pos, vel, mass, isStatic)
{
	useGravity_ = useGravity;
}


Rigibody::~Rigibody()
{
	PhysicalWorld::RemoveRb(id_);
}


void Rigibody::Update(const double time)
{
	if (_isnan(velocity_.X) || _isnan(velocity_.Y))
		velocity_ = Vector2D();

	position_ += velocity_ * time;

	velocity_ -= velocity_ * PhysicsConstants::deccelerationFactor * time;
}

void Rigibody::AddForceImpulse(const Vector2D force)
{
	if (isStatic_)
		return;

	this->velocity_ += force / mass_;
}
 
void Rigibody::AddForceContinuous(const Vector2D force, const double time)
{
	if (isStatic_)
		return;

	this->velocity_ += force * time / mass_;
}

void Rigibody::AddAcceleration(const Vector2D acceleration)
{
	if (isStatic_)
		return;

	this->velocity_ += acceleration;
}

void Rigibody::AddAccelerationContinuous(const Vector2D acceleration, const double time)
{
	if (isStatic_)
		return;

	this->velocity_ += acceleration * time;
}

Vector2D Rigibody::LocalToWorldPos(const Vector2D local) const
{
	return local + position_;
}

Vector2D Rigibody::WorldToLocalPos(const Vector2D world) const
{
	return world - position_;
}

double Rigibody::GetMass() const
{
	return mass_;
}
