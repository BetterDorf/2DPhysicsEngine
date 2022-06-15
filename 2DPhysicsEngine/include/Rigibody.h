#pragma once
#include "Vector.h"

class Rigibody
{
public:
	Rigibody() = default;
	Rigibody(const double x, const double y) : position(Vector(x,y)){}
	explicit Rigibody(const Vector pos) : position(pos) {}
	Rigibody(const Vector pos, const Vector vel) : position(pos), velocity(vel) {}

	Vector position = Vector(0.0, 0.0);
	Vector velocity = Vector(0.0, 0.0);

	//static bool CheckCollide(Rigibody a, Rigibody b);
	//static bool CheckBoundingBoxCollide(Rigibody a, Rigibody b);

	void Update(double time);

	void AddForceImpulse(Vector force);
	void AddForceContinuous(Vector force, double time);
};
