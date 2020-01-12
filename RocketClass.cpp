#include <vector>
#include <iostream>
#include "Rocket.h" 
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "Particle.h" 
#include <math.h> 

sf::Vector2f ml::Rocket::convertToWorldSpace(sf::Vector2f *pos)
{
	sf::Vector2f output;
	output.x = pos->x;
	output.y = 1000 -pos->y;
	return output;
}

void ml::Rocket::explode(int antal, float force, float forceMod)
{
	float PI = 3.141592f;
	for (int i = 0; i < antal; i++) {
		float dir = rand() / (RAND_MAX + 1.);
		dir -= 0.5f;
		dir *= 2 * PI;
		sf::Vector2f velOfPart;
		velOfPart.x = sin(dir);
		velOfPart.y = cos(dir);
		float tempForce = force - (rand() % (int)forceMod);
		velOfPart *= tempForce;
		sf::Color color(200,50 + rand() % 150 ,150 + rand() % 100);
		particles.push_back(Particle(pos, velOfPart, 0.75f, color));
	}
}

ml::Rocket::Rocket(float x, float y)
{
	state = 0; // 0=Rocket stage , 1=Explotion stage
	launched = false;
	gravity = 35.f;
	pos.x = x;
	pos.y = y;
	rocketBody.setSize(sf::Vector2f(3,6));
	//convertWorldSpace(&pos);
	rocketBody.setPosition(convertToWorldSpace(&pos));
	rocketBody.setFillColor(sf::Color(130,145,255));
	rocketBody.setOutlineColor(sf::Color::Transparent);
}

void ml::Rocket::shoot()
{
	std::cout << "Rocket launched!" << std::endl;
}

sf::RectangleShape ml::Rocket::getBody()
{
	return rocketBody;
}

void ml::Rocket::renderRocket(sf::RenderWindow & window)
{
	if(state==0)
		window.draw(rocketBody);
}

void ml::Rocket::renderParticles(sf::RenderWindow & window, float deltaTime)
{
	for (int i = 0; i < particles.size(); i++) {
		if (!particles[i].update(deltaTime)) {
			explode(5, 250.0f, 200.f);
			particles.erase(particles.begin() + i);
			
		}
		else {
			window.draw(particles[i].getBody());
		}
		
	}
}

void ml::Rocket::update(float deltaTime)
{
	if (vel.y < 0 && state == 0) {
		state = 1;
		//explode(1500 + rand() % 3000, 250.0f, 250.f);
		explode(5, 250.0f, 200.f);
	}
	if (launched && state == 0) {
		float val =  rand() % 10000;
		float val1 = 10000;
		if (val > val1 - (deltaTime * 100000)) {
			sf::Vector2f velo(3.0f - (rand() % 60) / 10.0f , -rand() % 30/10.0f );
			particles.push_back(Particle(pos,velo, 0.25f, sf::Color(200, 100 + rand() % 50, 100 + rand() % 50)));
		}
		vel.y -= gravity * deltaTime;
	}
	pos.y += vel.y*deltaTime;
	rocketBody.setPosition(convertToWorldSpace(&pos));
}

void ml::Rocket::launch()
{
	launched = true;
	vel.y = 100 + rand() % 100;
}
