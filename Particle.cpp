#include <vector>
#include <iostream>
#include "Particle.h" 
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>



sf::Vector2f ml::Particle::convertToWorldPos(sf::Vector2f & pos)
{
	sf::Vector2f output;
	output.x = pos.x;
	output.y = 1000 - pos.y;
	return output;
}

ml::Particle::Particle(sf::Vector2f pos, sf::Vector2f vel, float drag, sf::Color color)
{
	airDrag = drag; // Typ value = 0 - 0.1
	velosity = vel;
	position = pos;
	gravity = 50;
	// Render properties
	body.setPosition(pos);
	body.setSize(sf::Vector2f(1,1));
	body.setFillColor(color);
	body.setOutlineThickness(0);
}

bool ml::Particle::update(float deltaTime)
{
	velosity.y -= gravity * deltaTime;
	velosity /= (1+(airDrag*deltaTime)); 
	position += velosity * deltaTime;
	body.setPosition(convertToWorldPos(position));
	if (position.y < 0)
		return false;
	else
		return true;
}

sf::RectangleShape ml::Particle::getBody()
{
	return body;
}
