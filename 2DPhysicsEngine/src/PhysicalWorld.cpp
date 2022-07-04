#include "PhysicalWorld.h"


#include "PhysicsConstant.h"
#include "Collisions.h"
#include "RegionNode.h"

#include <algorithm>
#include <ranges>

std::unordered_map<unsigned long, Rigibody*> PhysicalWorld::rigibodies_ = std::unordered_map<unsigned long, Rigibody*>{};

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

	//Make quad Tree
	auto rbs = std::make_unique<std::unordered_set<Rigibody*>>();
	for (auto& rb : rigibodies_ | std::views::values)
	{
		rbs->emplace(rb);
	}

	SpacePartionning::RegionNode baseNode(std::move(rbs));
	std::unordered_multimap<Rigibody*, Rigibody*> CheckedCollisions;

	for (const auto& rbPtr1 : rigibodies_ | std::views::values)
	{
		for (auto& rbSet : baseNode.GetBodiesInRegionsInRadius(rbPtr1))
		{
			for (auto& rbPtr2 : *rbSet)
			{
				//Check if collision is with same object
				if (rbPtr1 == rbPtr2)
				{
					continue;
				}
				//Check if collision already happened
				//Make a pair out of the pointers where the first one is the lowest of the two
				auto pointerPair = rbPtr1 < rbPtr2 ? std::pair<Rigibody*, Rigibody*>(rbPtr1, rbPtr2)
					                  : std::pair<Rigibody*, Rigibody*>(rbPtr2, rbPtr1);
				//Leverage the fact that we know that our pair will be stored as { lowest ; highest }
				auto [fst, snd] = CheckedCollisions.equal_range(pointerPair.first);
				bool isContained = false;
				for (auto iterator = fst; iterator != snd; ++iterator)
				{
					if (iterator->second == pointerPair.second)
					{
						isContained = true;
						break;
					}
				}
				if (isContained)
				{
					continue;
				}
				//Add the pair
				CheckedCollisions.emplace(pointerPair);

				if (Collisions::ColData data = Collisions::CheckCollision(rbPtr1, rbPtr2);
					data.HasCollided)
				{
					//Collisions::SolveOverlap(data);
					Collisions::SolveVelocities(data);
				}
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