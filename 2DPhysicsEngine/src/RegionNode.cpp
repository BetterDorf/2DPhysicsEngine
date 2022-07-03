#include "RegionNode.h"

#include "PhysicsConstant.h"
#include "MathUtils.h"

#include <ranges>
#include <utility>

SpacePartionning::RegionNode::RegionNode(std::unordered_set<Rigibody*> inRegion) :
bodiesInRegion_(std::move(inRegion))
{
	TrySplit();
}

std::unordered_set<std::unordered_set<Rigibody*>*> SpacePartionning::RegionNode::GetBodiesInRegionsInRadius(const Rigibody* rbPtr)
{
	std::unordered_set<std::unordered_set<Rigibody*>*> possibleCollisionBodies = {};

	if (hasSplit_)
	{
		std::vector<int> intersectingRegions = {};

		//Find where the body would be if it were in this parent region
		int baseregion = FindSubregionForBody(rbPtr);
		intersectingRegions.emplace_back(baseregion);

		//Find all the regions the body crosses over in with it's radius
		if (const double distance = rbPtr->GetPos().X - splitPoint_.X;  abs(distance) < rbPtr->GetCollider()->GetBoundingCircleRad())
		{
			intersectingRegions.emplace_back(baseregion + static_cast<int>(mathUtils::signnum_c(distance)));
		}
		if (const double distance = rbPtr->GetPos().Y - splitPoint_.Y;  abs(distance) < rbPtr->GetCollider()->GetBoundingCircleRad())
		{
			intersectingRegions.emplace_back(baseregion + static_cast<int>(mathUtils::signnum_c(distance)));
		}

		//Assume that if three regions are in, the fourth will be too
		if (static_cast<int>(intersectingRegions.size()) == 3)
		{
			intersectingRegions = { 0, 1, 2, 3 };
		}

		//Add the bodies of the subregions
		for (const auto& intersecting_region : intersectingRegions)
		{
			for (auto& bodies : children_[intersecting_region]->GetBodiesInRegionsInRadius(rbPtr))
			{
				possibleCollisionBodies.emplace(bodies);
			}
		}
	}
	else
	{
		//We don't have subregions so we just add our own bodylist
		possibleCollisionBodies.emplace(&bodiesInRegion_);
	}

	return possibleCollisionBodies;
}

void SpacePartionning::RegionNode::TrySplit()
{
	if (static_cast<int>(bodiesInRegion_.size()) <= PhysicsConstants::maxBodiesInRegion)
	{
		return;
	}

	Split();
}

void SpacePartionning::RegionNode::Split()
{
	hasSplit_ = true;

	//Calculate average of points
	Vector2D sum;
	for (const auto& val : bodiesInRegion_)
	{
		sum += val->GetPos();
	}

	splitPoint_ = sum / static_cast<double>(bodiesInRegion_.size());

	//Make the new regions
	//Find the points that belong in them
	std::unordered_set<Rigibody*> region0Bodies;
	std::unordered_set<Rigibody*> region1Bodies;
	std::unordered_set<Rigibody*> region2Bodies;
	std::unordered_set<Rigibody*> region3Bodies;

	for (const auto& body : bodiesInRegion_)
	{
		switch (FindSubregionForBody(body))
		{
		case 0:
			region0Bodies.emplace(body);
			break;
		case 1:
			region1Bodies.emplace(body);
			break;
		case 2:
			region2Bodies.emplace(body);
			break;
		case 3:
			region3Bodies.emplace(body);
			break;
		default:break;
		}
	}

	children_.emplace_back(std::make_unique<RegionNode>(region0Bodies));
	children_.emplace_back(std::make_unique<RegionNode>(region1Bodies));
	children_.emplace_back(std::make_unique<RegionNode>(region2Bodies));
	children_.emplace_back(std::make_unique<RegionNode>(region3Bodies));

	//Clear our unused memory
	bodiesInRegion_.clear();
}

int SpacePartionning::RegionNode::FindSubregionForBody(const Rigibody* body) const
{
	if (const Vector2D bodyPos = body->GetPos(); bodyPos.X >= splitPoint_.X)
	{
		if (bodyPos.Y >= splitPoint_.Y)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
	else
	{
		if (bodyPos.Y >= splitPoint_.Y)
		{
			return 2;
		}
		else
		{
			return 3;
		}
	}
}