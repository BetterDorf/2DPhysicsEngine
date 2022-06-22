#pragma once
#include "Entity.h"

class World
{
public:
	World();

	void AddEntity(Entity*);
	void RemoveEntity(long);

	void Update() const;
private:
	std::map<long, Entity*> entities_;
};