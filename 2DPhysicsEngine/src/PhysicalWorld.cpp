#include "PhysicalWorld.h"

#include "PhysicsConstant.h"
#include "Collisions.h"

#include <ranges>

std::map<long, Rigibody*> PhysicalWorld::rigibodies_ = std::map<long, Rigibody*>{};

void PhysicalWorld::AddRb(Rigibody* rb)
{
	rigibodies_.emplace(rb->GetId(), rb);
}

void PhysicalWorld::RemoveRb(const long id)
{
	rigibodies_.erase(id);
}

void PhysicalWorld::Tick(const double timeElapsed)
{
	//Check Collisions
	for (auto iter1 = rigibodies_.begin() ; iter1 != rigibodies_.end() ; ++iter1)
	{
		for (auto iter2 = iter1; iter2 != rigibodies_.end(); ++iter2)
		{
			const auto rbPtr1 = iter1->second;
			const auto rbPtr2 = iter2->second;

			if (rbPtr1 != rbPtr2 && Collisions::CheckCollision(rbPtr1, rbPtr2))
			{
				//Find the normal and tangent vector of the collision
				Vector normalVector = (rbPtr2->GetPos() - rbPtr1->GetPos()).Normalize();
				const Vector tangVector = normalVector.GetPerpendicularVector(true);

				//Calculate projections of V1 on normal and tangent
				const double V1n = normalVector.X * rbPtr1->GetVelocity().X + normalVector.Y * rbPtr1->GetVelocity().Y;
				const double V1t = tangVector.X * rbPtr1->GetVelocity().X + tangVector.Y * rbPtr1->GetVelocity().Y;

				//Calculate projections of V2 on normal and tangent
				const double V2n = normalVector.X * rbPtr2->GetVelocity().X + normalVector.Y * rbPtr2->GetVelocity().Y;
				const double V2t = tangVector.X * rbPtr2->GetVelocity().X + tangVector.Y * rbPtr2->GetVelocity().Y;

				//Set velocities according to their elastic collisions on each axis
				rbPtr1->SetVelocity(Vector(normalVector.X * V2n + tangVector.X * V1t,
					normalVector.Y * V2n + tangVector.Y * V1t));
				rbPtr2->SetVelocity(Vector(normalVector.X * V1n + tangVector.X * V2t,
					normalVector.Y * V1n + tangVector.Y * V2t));
			}
		}
	}

	//Move each object
	for (const auto rbPtr : rigibodies_ | std::views::values)
	{
		rbPtr->Update(timeElapsed);
	}
}