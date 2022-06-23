#pragma once
#include "Vector.h"
#include "Collider.h"

class Rigibody
{
public:
	explicit Rigibody(std::unique_ptr<Collider>);
	Rigibody(std::unique_ptr<Collider>, Vector pos);
	Rigibody(std::unique_ptr<Collider>, Vector pos, double mass);
	Rigibody(std::unique_ptr<Collider>, Vector pos, Vector vel);
	Rigibody(std::unique_ptr<Collider>, Vector pos, Vector vel, double mass);
	Rigibody(std::unique_ptr<Collider>, Vector pos, Vector vel, double mass, bool isStatic);
	Rigibody(std::unique_ptr<Collider>, Vector pos, Vector vel, double mass, bool isStatic, bool useGravity);

	Rigibody(const Rigibody&) = delete;

	~Rigibody();

	//static bool CheckCollide(Rigibody a, Rigibody b);
	//static bool CheckBoundingBoxCollide(Rigibody a, Rigibody b);

	void Update(double time);

	void AddForceImpulse(Vector force);
	void AddForceContinuous(Vector force, double time);
	void AddAcceleration(Vector acceleration);
	void AddAccelerationContinuous(Vector acceleration, double time);

	[[nodiscard]] long GetId() const { return id_; }
	[[nodiscard]] Vector GetPos() const { return position_; }
	[[nodiscard]] Vector GetVelocity() const { return velocity_; }
	[[nodiscard]] double GetMass() const { return mass_; }
	[[nodiscard]] Collider* GetCollider() const { return colliderPtr_.get(); }
	[[nodiscard]] bool IsStatic() const { return isStatic_; }
	[[nodiscard]] bool UseGravity() const { return useGravity_; }

	void SetPos(const Vector newPos) { position_ = newPos; }
	void SetVelocity(const Vector newVelocity) { velocity_ = newVelocity; }
	void SetMass(const double newMass) { mass_ = newMass; }
	void SetCollider(std::unique_ptr<Collider> newCol) { colliderPtr_.reset(); colliderPtr_ = std::move(newCol); }

private:
	inline static long CurId = 0;
	long id_{};

	Vector position_ = Vector(0.0, 0.0);
	Vector velocity_ = Vector(0.0, 0.0);

	double mass_ = 1.0;
	bool useGravity_ = true;
	bool isStatic_ = false;

	std::unique_ptr<Collider> colliderPtr_;
};
