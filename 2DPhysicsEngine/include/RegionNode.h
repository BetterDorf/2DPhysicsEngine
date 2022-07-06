#pragma once
#include "Vector2D.h"
#include "Rigibody.h"
#include <unordered_set>
#include <vector>

namespace SpacePartionning
{
	class RegionNode
	{
	public:
		RegionNode(std::unique_ptr<std::unordered_set<Rigibody*>> inRegion, int depth);

		[[nodiscard]] bool HasSplit() const { return hasSplit_; }
		[[nodiscard]] Vector2D SplitPoint() const { return splitPoint_; }

		[[nodiscard]] std::unordered_set<std::unordered_set<Rigibody*>*> GetBodiesInRegionsInRadius(const Rigibody*);

		[[nodiscard]] int FindSubregionForBody(const Rigibody* body) const;
	private:
		int depth_;

		std::vector<std::unique_ptr<RegionNode>> children_;

		bool hasSplit_ = false;

		Vector2D splitPoint_;
		std::unique_ptr<std::unordered_set<Rigibody*>> bodiesInRegion_;

		[[nodiscard]] std::unordered_set<Rigibody*>* BodiesInRegion() const { return &*bodiesInRegion_; }

		void TrySplit();
		void Split();
	};
}