#ifndef PARTICLE_H // include guard
#define PARTICLE_H
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

namespace ml
{
	class Particle
	{
	private:
		sf::Vector2f position;
		sf::Vector2f velosity;
		sf::RectangleShape body;
		float gravity;
		float airDrag;
		sf::Vector2f convertToWorldPos(sf::Vector2f &pos);
	public:
		Particle(sf::Vector2f pos, sf::Vector2f vel, float drag, sf::Color color);
		bool update(float deltaTime);
		sf::RectangleShape getBody();
	};
}


#endif /* MY_CLASS_H */