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
		explicit RegionNode(std::unordered_set<Rigibody*> inRegion);

		[[nodiscard]] bool HasSplit() const { return hasSplit_; }
		[[nodiscard]] Vector2D SplitPoint() const { return splitPoint_; }

		[[nodiscard]] std::unordered_set<std::unordered_set<Rigibody*>*> GetBodiesInRegionsInRadius(const Rigibody*);

		[[nodiscard]] int FindSubregionForBody(const Rigibody* body) const;
	private:
		std::vector<std::unique_ptr<RegionNode>> children_;

		bool hasSplit_ = false;

		Vector2D splitPoint_;
		std::unordered_set<Rigibody*> bodiesInRegion_;

		[[nodiscard]] std::unordered_set<Rigibody*>* BodiesInRegion() { return &bodiesInRegion_; }

		void TrySplit();
		void Split();
	};
}