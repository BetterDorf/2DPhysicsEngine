#include "Rigibody.h"
#include "PhysicalWorld.h"

Rigibody::Rigibody(std::unique_ptr<PhysicShape> col) : id_(CurId++), colliderPtr_(std::move(col))
{
	PhysicalWorld::AddRb(this);
}

Rigibody::Rigibody(std::unique_ptr<PhysicShape> col, const Vector pos) : Rigibody(std::move(col))
{
	position_ = pos;
}

Rigibody::Rigibody(std::unique_ptr<PhysicShape> col, const Vector pos, const double mass) : Rigibody(std::move(col), pos)
{
	mass_ = mass;
}

Rigibody::Rigibody(std::unique_ptr<PhysicShape> col, const Vector pos, const Vector vel) : Rigibody(std::move(col), pos)
{
	velocity_ = vel;
}

Rigibody::Rigibody(std::unique_ptr<PhysicShape> col, const Vector pos, const Vector vel, const double mass) : Rigibody(std::move(col), pos, vel)
{
	mass_ = mass;
}

Rigibody::Rigibody(std::unique_ptr<PhysicShape> col, const Vector pos, const Vector vel, const double mass, const bool isStatic)
	: Rigibody(std::move(col), pos, vel, mass)
{
	isStatic_ = isStatic;
}

Rigibody::Rigibody(std::unique_ptr<PhysicShape> col, const Vector pos, const Vector vel, const double mass, const bool isStatic, const bool useGravity)
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
	position_ += velocity_ * time;
}

void Rigibody::AddForceImpulse(const Vector force)
{
	if (isStatic_)
		return;

	this->velocity_ += force / mass_;
}
 
void Rigibody::AddForceContinuous(const Vector force, const double time)
{
	if (isStatic_)
		return;

	this->velocity_ += force * time / mass_;
}

void Rigibody::AddAcceleration(const Vector acceleration)
{
	if (isStatic_)
		return;

	this->velocity_ += acceleration;
}

void Rigibody::AddAccelerationContinuous(const Vector acceleration, const double time)
{
	if (isStatic_)
		return;

	this->velocity_ += acceleration * time;
}
