#pragma once
#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <ctime>

class World
{
public:
	explicit World(std::unique_ptr<sf::RenderWindow> window) : window_(std::move(window)) {}

	void AddEntity(std::unique_ptr<Entity>);
	void RemoveEntity(long);

	void Start();
private:
	std::map<long, std::unique_ptr<Entity>> entities_;

	std::unique_ptr<sf::RenderWindow> window_;

	Vector cameraPos_;

	/*int physicFramePerSeconds_;
	int framePerSeconds_;*/

	void Update(double);
	void UpdatePhysics(double);
};