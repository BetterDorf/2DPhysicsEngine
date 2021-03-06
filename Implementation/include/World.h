#pragma once
#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <ctime>

class World
{
public:
	explicit World(std::unique_ptr<sf::RenderWindow> window, const double physicsTimestep) : window_(std::move(window)),
	physicsTimestep_(physicsTimestep){}

	void AddEntity(std::unique_ptr<Entity>);
	void RemoveEntity(long);

	void Start();
private:
	std::map<long, std::unique_ptr<Entity>> entities_;

	std::unique_ptr<sf::RenderWindow> window_;

	Vector2D cameraPos_;
	double physicsTimestep_;

	/*int physicFramePerSeconds_;
	int framePerSeconds_;*/

	void Update(double);
	static void UpdatePhysics(double);

	void ClickEvent(sf::Event);
};