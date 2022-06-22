#include "Rigibody.h"
#include "PhysicalWorld.h"

Rigibody::Rigibody(std::unique_ptr<Collider> col) : id_(CurId++), colliderPtr_(std::move(col))
{
	PhysicalWorld::AddRb(this);
}

Rigibody::Rigibody(std::unique_ptr<Collider> col, const Vector pos) : Rigibody(std::move(col))
{
	position_ = pos;
}

Rigibody::Rigibody(std::unique_ptr<Collider> col, const Vector pos, const double mass) : Rigibody(std::move(col), pos)
{
	mass_ = mass;
}

Rigibody::Rigibody(std::unique_ptr<Collider> col, const Vector pos, const Vector vel) : Rigibody(std::move(col), pos)
{
	velocity_ = vel;
}

Rigibody::Rigibody(std::unique_ptr<Collider> col, const Vector pos, const Vector vel, const double mass) : Rigibody(std::move(col), pos, vel)
{
	mass_ = mass;
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
	this->velocity_ += force / mass_;
}
 
void Rigibody::AddForceContinuous(const Vector force, const double time)
{
	this->velocity_ += force * time / mass_;
}
