#pragma once
#include "Vector2D.h"
#include "PhysicShape.h"

class Rigibody
{
public:
	explicit Rigibody(std::unique_ptr<PhysicShape>);
	Rigibody(std::unique_ptr<PhysicShape>, Vector2D pos);
	Rigibody(std::unique_ptr<PhysicShape>, Vector2D pos, float mass);
	Rigibody(std::unique_ptr<PhysicShape>, Vector2D pos, Vector2D vel);
	Rigibody(std::unique_ptr<PhysicShape>, Vector2D pos, Vector2D vel, float mass);
	Rigibody(std::unique_ptr<PhysicShape>, Vector2D pos, Vector2D vel, float mass, bool isStatic);
	Rigibody(std::unique_ptr<PhysicShape>, Vector2D pos, Vector2D vel, float mass, bool isStatic, bool useGravity);

	Rigibody(const Rigibody&) = delete;

	~Rigibody();

	//static bool CheckCollide(Rigibody a, Rigibody b);
	//static bool CheckBoundingBoxCollide(Rigibody a, Rigibody b);

	void Update(float time);

	void AddForceImpulse(Vector2D force);
	void AddForceContinuous(Vector2D force, float time);
	void AddAcceleration(Vector2D acceleration);
	void AddAccelerationContinuous(Vector2D acceleration, float time);

	[[nodiscard]] Vector2D LocalToWorldPos(Vector2D) const;
	[[nodiscard]] Vector2D WorldToLocalPos(Vector2D) const;

	[[nodiscard]] long GetId() const { return id_; }
	[[nodiscard]] Vector2D GetPos() const { return position_; }
	[[nodiscard]] Vector2D GetVelocity() const { return velocity_; }
	[[nodiscard]] float GetMass() const;
	[[nodiscard]] PhysicShape* GetCollider() const { return colliderPtr_.get(); }
	[[nodiscard]] bool IsStatic() const { return isStatic_; }
	[[nodiscard]] bool UseGravity() const { return useGravity_; }
	[[nodiscard]] bool IsColliding() const { return isColliding_; }

	void SetPos(const Vector2D newPos) { position_ = newPos; }
	void SetVelocity(const Vector2D newVelocity) { velocity_ = newVelocity; }
	void SetMass(const float newMass) { mass_ = newMass; }
	void SetCollider(std::unique_ptr<PhysicShape> newCol) { colliderPtr_.reset(); colliderPtr_ = std::move(newCol); }
	void SetIsColliding(const bool colliding) { isColliding_ = colliding; }

private:
	inline static unsigned long CurId = 0;
	unsigned long id_;

	Vector2D position_ = Vector2D(0.0, 0.0);
	//Angle in radians
	float rotation = 0.0;
	Vector2D velocity_ = Vector2D(0.0, 0.0);

	float mass_ = 1.0;
	bool useGravity_ = true;
	bool isStatic_ = false;

	bool isColliding_ = false;

	std::unique_ptr<PhysicShape> colliderPtr_;
};
