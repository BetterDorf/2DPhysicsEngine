#include "Rigibody.h"
#include "PhysicalWorld.h"

Rigibody::Rigibody() : id_(CurId++)
{
	PhysicalWorld::AddRb(this);
}

Rigibody::Rigibody(const Vector pos) : Rigibody()
{
	position_ = pos;
}

Rigibody::Rigibody(const Vector pos, const double mass) : Rigibody(pos)
{
	mass_ = mass;
}

Rigibody::Rigibody(const Vector pos, const Vector vel) : Rigibody(pos)
{
	velocity_ = vel;
}

Rigibody::Rigibody(const Vector pos, const Vector vel, const double mass) : Rigibody(pos, vel)
{
	mass_ = mass;
}

Rigibody::Rigibody(const Rigibody& other)
{
	*this = Rigibody();

	this->SetMass(other.GetMass());
	this->SetPos(other.GetPos());
	this->SetVelocity(other.GetVelocity());
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
