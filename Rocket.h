#ifndef ROCKET_H // include guard
#define ROCKET_H
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "Particle.h" 

namespace ml
{
	class Rocket
	{
	private:
		int state;
		bool launched;
		float gravity; // gravity constant
		std::vector<Particle> particles;
		sf::Vector2f pos;
		sf::Vector2f vel;
		sf::RectangleShape rocketBody;
		sf::Vector2f convertToWorldSpace(sf::Vector2f *pos);
		void explode(int antal, float force, float forceMod);
	public:
		Rocket(float x, float y);
		void shoot();
		sf::RectangleShape getBody();
		void renderRocket(sf::RenderWindow &window);
		void renderParticles(sf::RenderWindow &window, float deltaTime);
		void update(float deltaTime);
		void launch();
	};
}

#endif /* MY_CLASS_H */