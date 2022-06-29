#pragma once
#include "Vector2D.h"
#include "PhysicShape.h"

class Rigibody
{
public:
	explicit Rigibody(std::unique_ptr<PhysicShape>);
	Rigibody(std::unique_ptr<PhysicShape>, Vector2D pos);
	Rigibody(std::unique_ptr<PhysicShape>, Vector2D pos, double mass);
	Rigibody(std::unique_ptr<PhysicShape>, Vector2D pos, Vector2D vel);
	Rigibody(std::unique_ptr<PhysicShape>, Vector2D pos, Vector2D vel, double mass);
	Rigibody(std::unique_ptr<PhysicShape>, Vector2D pos, Vector2D vel, double mass, bool isStatic);
	Rigibody(std::unique_ptr<PhysicShape>, Vector2D pos, Vector2D vel, double mass, bool isStatic, bool useGravity);

	Rigibody(const Rigibody&) = delete;

	~Rigibody();

	//static bool CheckCollide(Rigibody a, Rigibody b);
	//static bool CheckBoundingBoxCollide(Rigibody a, Rigibody b);

	void Update(double time);

	void AddForceImpulse(Vector2D force);
	void AddForceContinuous(Vector2D force, double time);
	void AddAcceleration(Vector2D acceleration);
	void AddAccelerationContinuous(Vector2D acceleration, double time);

	Vector2D LocalToWorldPos(Vector2D) const;
	Vector2D WorldToLocalPos(Vector2D) const;

	[[nodiscard]] long GetId() const { return id_; }
	[[nodiscard]] Vector2D GetPos() const { return position_; }
	[[nodiscard]] Vector2D GetVelocity() const { return velocity_; }
	[[nodiscard]] double GetMass() const { return mass_; }
	[[nodiscard]] PhysicShape* GetCollider() const { return colliderPtr_.get(); }
	[[nodiscard]] bool IsStatic() const { return isStatic_; }
	[[nodiscard]] bool UseGravity() const { return useGravity_; }

	void SetPos(const Vector2D newPos) { position_ = newPos; }
	void SetVelocity(const Vector2D newVelocity) { velocity_ = newVelocity; }
	void SetMass(const double newMass) { mass_ = newMass; }
	void SetCollider(std::unique_ptr<PhysicShape> newCol) { colliderPtr_.reset(); colliderPtr_ = std::move(newCol); }

private:
	inline static long CurId = 0;
	long id_{};

	Vector2D position_ = Vector2D(0.0, 0.0);
	//Angle in radians
	double rotation = 0.0;
	Vector2D velocity_ = Vector2D(0.0, 0.0);

	double mass_ = 1.0;
	bool useGravity_ = true;
	bool isStatic_ = false;

	std::unique_ptr<PhysicShape> colliderPtr_;
};
