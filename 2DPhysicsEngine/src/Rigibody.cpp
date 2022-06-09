#include "Rigibody.h"

void Rigibody::Update(const double time)
{
	position += velocity * time;
}

void Rigibody::AddForceImpulse(const Vector force)
{
	velocity += force;
}
