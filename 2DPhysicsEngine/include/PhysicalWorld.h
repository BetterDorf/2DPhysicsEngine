#pragma once
#include "Rigibody.h"

#include <map>

class PhysicalWorld
{
public:
	PhysicalWorld() = delete;

	static void AddRb(Rigibody&);
	static void RemoveRb(long);
	static void Tick(double timeElapsed);
private:
	static std::map<long, Rigibody&> rigibodies_;
};