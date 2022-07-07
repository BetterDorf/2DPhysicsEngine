#include "RegionNode.h"

#include "PhysicsConstant.h"
#include "MathUtils.h"

#include <iostream>

#include <ranges>
#include <string>
#include <utility>

SpacePartionning::RegionNode::RegionNode(std::unique_ptr<std::unordered_set<Rigibody*>> inRegion, const int depth) :
depth_(depth), bodiesInRegion_(std::move(inRegion))
{
	bodiesInDistance_ = std::make_unique<std::unordered_set<Rigibody*>>(*bodiesInRegion_);
	TrySplit();
}

SpacePartionning::RegionNode::RegionNode(std::unique_ptr<std::unordered_set<Rigibody*>> inRegion,
	std::unique_ptr<std::unordered_set<Rigibody*>> inDistance, const int depth) : depth_(depth), bodiesInRegion_(std::move(inRegion)),
	bodiesInDistance_(std::move(inDistance))
{
	TrySplit();
}

std::unordered_set<std::unordered_set<Rigibody*>*> SpacePartionning::RegionNode::GetBodiesInRegionsInRadius(const Rigibody* rbPtr)
{
	std::unordered_set<std::unordered_set<Rigibody*>*> possibleCollisionBodies = {};

	if (hasSplit_)
	{
		const auto intersectingRegions = FindSubregionsForBody(rbPtr);

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
		if (bodiesInDistance_ == nullptr)
			possibleCollisionBodies.emplace(bodiesInRegion_.get());
		else
			possibleCollisionBodies.emplace(bodiesInDistance_.get());
	}

	return possibleCollisionBodies;
}

void SpacePartionning::RegionNode::TrySplit()
{
	if (depth_ >= PhysicsConstants::maxQuadDepth)
		return;

	if (static_cast<int>(bodiesInRegion_->size()) <= PhysicsConstants::maxBodiesInRegion)
		return;

	Split();
}

void SpacePartionning::RegionNode::Split()
{
	hasSplit_ = true;

	//Calculate average of points
	Vector2D sum;
	for (const auto& val : *bodiesInRegion_)
	{
		sum += val->GetPos();
	}

	splitPoint_ = sum / static_cast<double>(bodiesInRegion_->size());

	//Make the new regions
	//Find the points that belong in them
	auto region0Bodies = std::make_unique<std::unordered_set<Rigibody*>>();
	auto region0NearBodies = std::make_unique<std::unordered_set<Rigibody*>>();
	auto region1Bodies = std::make_unique<std::unordered_set<Rigibody*>>();
	auto region1NearBodies = std::make_unique<std::unordered_set<Rigibody*>>();
	auto region2Bodies = std::make_unique<std::unordered_set<Rigibody*>>();
	auto region2NearBodies = std::make_unique<std::unordered_set<Rigibody*>>();
	auto region3Bodies = std::make_unique<std::unordered_set<Rigibody*>>();
	auto region3NearBodies = std::make_unique<std::unordered_set<Rigibody*>>();

	for (auto& body : *bodiesInRegion_)
	{
		switch (FindSubregionForBody(body))
		{
		case 0:
			region0Bodies->emplace(body);
			break;
		case 1:
			region1Bodies->emplace(body);
			break;
		case 2:
			region2Bodies->emplace(body);
			break;
		case 3:
			region3Bodies->emplace(body);
			break;
		default:break;
		}
	}

	for (auto& body : *bodiesInDistance_)
	{
		for (auto regions = FindSubregionsForBody(body); const auto region : regions)
		{
			switch (region)
			{
			case 0:
				region0NearBodies->emplace(body);
				break;
			case 1:
				region1NearBodies->emplace(body);
				break;
			case 2:
				region2NearBodies->emplace(body);
				break;
			case 3:
				region3NearBodies->emplace(body);
				break;
			default:break;
			}
		}
	}

	//Clear our unused memory 
	/*bodiesInRegion_.reset();
	bodiesInDistance_.reset();*/

	children_.emplace_back(std::make_unique<RegionNode>(std::move(region0Bodies), std::move(region0NearBodies), depth_ + 1));
	children_.emplace_back(std::make_unique<RegionNode>(std::move(region1Bodies), std::move(region1NearBodies), depth_ + 1));
	children_.emplace_back(std::make_unique<RegionNode>(std::move(region2Bodies), std::move(region2NearBodies), depth_ + 1));
	children_.emplace_back(std::make_unique<RegionNode>(std::move(region3Bodies), std::move(region3NearBodies), depth_ + 1));
}

std::unordered_set<int> SpacePartionning::RegionNode::FindSubregionsForBody(const Rigibody* rbPtr) const
{
	std::unordered_set<int> intersectingRegions;
	int baseRegion = FindSubregionForBody(rbPtr);

	intersectingRegions.emplace(baseRegion);

	//Find all the regions the body crosses over in with it's radius
	if (const double distance = rbPtr->GetPos().X - splitPoint_.X;  std::abs(distance) < rbPtr->GetCollider()->GetBoundingCircleRad())
	{
		intersectingRegions.emplace((baseRegion + 2) % 4);
	}
	if (const double distance = rbPtr->GetPos().Y - splitPoint_.Y;  std::abs(distance) < rbPtr->GetCollider()->GetBoundingCircleRad())
	{
		intersectingRegions.emplace((baseRegion + 1) % 2 + baseRegion > 1 ? 2: 0);
	}

	//Assume that if three regions are in, the fourth will be too
	if (static_cast<int>(intersectingRegions.size()) == 3)
	{
		intersectingRegions = { 0, 1, 2, 3 };
	}

	return  intersectingRegions;
}

int SpacePartionning::RegionNode::FindSubregionForBody(const Rigibody* rbPtr) const
{
	if (const Vector2D bodyPos = rbPtr->GetPos(); bodyPos.X >= splitPoint_.X)
	{
		if (bodyPos.Y >= splitPoint_.Y)
		{
			return  0;
		}
		else
		{
			return  1;
		}
	}
	else
	{
		if (bodyPos.Y >= splitPoint_.Y)
		{
			return  2;
		}
		else
		{
			return  3;
		}
	}
}
