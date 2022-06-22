#include "PhysicalWorld.h"
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
	//Check collisions
	for (const auto rbPtr1 : rigibodies_ | std::views::values)
	{
		for (const auto rbPtr2 : rigibodies_ | std::views::values)
		{
			if (rbPtr1 != rbPtr2)
			{
				std::cout << Collisions::CheckCollision(rbPtr1, rbPtr2) << std::endl;
			}
		}
	}

	for (const auto rbPtr : rigibodies_ | std::views::values)
	{
		rbPtr->Update(timeElapsed);
	}
}