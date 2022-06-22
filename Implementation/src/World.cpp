#include "World.h"
#include "PhysicalWorld.h"

World::World()
{

}

void World::AddEntity(Entity* ent)
{
	entities_.emplace(std::make_pair(ent->GetId(), ent));
}

void World::RemoveEntity(const long id)
{
	entities_.erase(id);
}

void Update()
{
	PhysicalWorld::Tick(1/60);
}