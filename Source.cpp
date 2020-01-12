#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h> 
#include "Rocket.h"

sf::Vector2f windowSize;

int main() {
	sf::Clock clock1;
	
	windowSize.x = 1400; windowSize.y = 1000;
	sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "THEGAME");

	std::vector<ml::Rocket> rockets;
	for(int i=0; i<3;i++)
		rockets.push_back(ml::Rocket(rand() % 1000,50));
	for (int i = 0; i < rockets.size(); i++) {
		rockets[i].launch();
	}
	//ml::Rocket r(100, 200);
	clock1.restart();
	while (window.isOpen()) {

		//Handeling window events like mouse and keyboard
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) {
			
			case sf::Event::Closed:
				window.close();
			case sf::Event::KeyPressed:
				
			default:
				break;
				

			}
				
		}	
		//Uppdateing physics
		sf::Time elapsed1 = clock1.getElapsedTime();
		float time = elapsed1.asSeconds();
		for (int i = 0; i < rockets.size();i++) {
			rockets[i].update(time);
		}
		
		clock1.restart();

		//Clearing rendering and drawing to screen
		window.clear();
		for (int i = 0; i < rockets.size(); i++) {
			//window.draw(rockets[i].getBody());
			rockets[i].renderRocket(window);
			rockets[i].renderParticles(window, time);
		}
		window.display();
	}
}



