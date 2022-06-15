#include "Rigibody.h"

void Rigibody::Update(const double time)
{
	position += velocity * time;
}

void Rigibody::AddForceImpulse(const Vector force)
{
	this->velocity += force;
}

void Rigibody::AddForceContinuous(const Vector force, const double time)
{
	this->velocity += force * time;
}