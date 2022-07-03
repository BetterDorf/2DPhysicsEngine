#pragma once
#include "Rigibody.h"

#include <unordered_map>

class PhysicalWorld
{
public:
	PhysicalWorld() = delete;

	static void AddRb(Rigibody*);
	static void RemoveRb(long);
	static void Tick(double timeElapsed);
private:
	static std::unordered_map<unsigned long, Rigibody*> rigibodies_;
};