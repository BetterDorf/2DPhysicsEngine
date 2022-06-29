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
				const Collisions::ColData data = Collisions::MakeColData(rbPtr1, rbPtr2);
				Collisions::SolveOverlap(data);
				Collisions::SolveVelocities(data);
			}
		}
	}

	//Move each object
	for (const auto rb : rigibodies_ | std::views::values)
	{
		if (rb->UseGravity())
		{
			rb->AddAccelerationContinuous(PhysicsConstants::GRAVITY_ACCELERATION, timeElapsed);
		}

		rb->Update(timeElapsed);
	}
}