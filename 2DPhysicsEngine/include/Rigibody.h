#pragma once
#include "Vector.h"

class Rigibody
{
public:
	Rigibody();
	explicit Rigibody(Vector pos);
	Rigibody(Vector pos, double mass);
	Rigibody(Vector pos, Vector vel);
	Rigibody(Vector pos, Vector vel, double mass);

	Rigibody(const Rigibody&);

	~Rigibody();

	//static bool CheckCollide(Rigibody a, Rigibody b);
	//static bool CheckBoundingBoxCollide(Rigibody a, Rigibody b);

	void Update(double time);

	void AddForceImpulse(Vector force);
	void AddForceContinuous(Vector force, double time);

	[[nodiscard]] long GetId() const { return id_; }
	[[nodiscard]] Vector GetPos() const { return position_; }
	[[nodiscard]] Vector GetVelocity() const { return velocity_; }
	[[nodiscard]] double GetMass() const { return mass_; }

	void SetPos(const Vector newPos) { position_ = newPos; }
	void SetVelocity(const Vector newVelocity) { velocity_ = newVelocity; }
	void SetMass(const double newMass) { mass_ = newMass; }

private:
	inline static long CurId = 0;
	long id_{};

	Vector position_ = Vector(0.0, 0.0);
	Vector velocity_ = Vector(0.0, 0.0);

	double mass_ = 1.0;
};
