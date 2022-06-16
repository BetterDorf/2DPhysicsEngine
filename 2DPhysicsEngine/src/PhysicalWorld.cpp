#include "PhysicalWorld.h"

#include <ranges>

std::map<long, Rigibody&> PhysicalWorld::rigibodies_ = std::map<long, Rigibody&>{};

void PhysicalWorld::AddRb(Rigibody& rb)
{
	rigibodies_.emplace(rb.GetId(), rb);
}

void PhysicalWorld::RemoveRb(const long id)
{
	rigibodies_.erase(id);
}

void PhysicalWorld::Tick(const double timeElapsed)
{
	for (auto& rb : rigibodies_ | std::views::values)
	{
		rb.Update(timeElapsed);
	}
}