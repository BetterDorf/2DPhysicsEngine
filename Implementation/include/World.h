#pragma once
#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <ctime>

class World
{
public:
	World();

	void AddEntity(Entity*);
	void RemoveEntity(long);
private:
	std::map<long, Entity*> entities_;

	sf::Window window_;

	/*int physicFramePerSeconds_;
	int framePerSeconds_;*/
};