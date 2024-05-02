/*
@author- Kaevin Barta
@file- polygons.sln
@version- 0.2

The purpose of this assignment is to give an introduction  
into using SFML to create a simple interactive graphics-based
program which utilizes your SpaceObject class from the previous assignment.
*/
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include "constants.h"
#include "spaceObject.h"
bool objectsIntersect(Point p1, Point p2);
Point getRandomLocation();
Point getRandomVelocity();
//============================================================================
int main()
{
	//create graphics window
	sf::RenderWindow window(
		sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),
		"Polygons!",
		sf::Style::Titlebar | sf::Style::Close //adds title bar and X button
	);

	window.setFramerateLimit(60);

	//create SpaceObjects
	int shipBlown = 0;
	Point shipLocation;
	Point asteriodsLocation;
	SpaceObject* ship = nullptr;
	ship = new SpaceObject;
	ship->setType(1);
	SpaceObject* asteriods[5] = { nullptr };
	for (int x = 0; x < 5; x++) {
		Point location;
		Point velocity;
		location = getRandomLocation();
		velocity = getRandomVelocity();
		asteriods[x] = new SpaceObject;
		asteriods[x]->setLocation(location.x, location.y);
		asteriods[x]->setVelocity(velocity.x, velocity.y);
	}
		//TODO: create ship (step 3.2)
	srand(42);
		//game loop
	while (window.isOpen())
	{
		//handle user input (events and keyboard keys being pressed) ----
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			ship->changeAngle(-3);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			ship->changeAngle(3);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			ship->applyThrust();


		// update game objects ------------------------------------------
		for (int x = 0; x < 5; x++) {
			asteriods[x]->updatePosition();
		}
		
	    ship->updatePosition(); 

		// draw new frame ------------------------------------------------
		window.clear();
		for (int x = 0; x < 5; x++) {
			asteriods[x]->draw(window);
		}
			ship->draw(window);
		for (int x = 0; x < 5; x++) {
			asteriodsLocation = asteriods[x]->getLocation();
			shipLocation = ship->getLocation();
			if (objectsIntersect(asteriodsLocation, shipLocation)) {
				ship->explode();			
			}
		}
		
		window.display();
		//reitterate the while loop
	}

	return 0;
}

Point getRandomLocation() {
	Point randNum;
	randNum.x = rand() % SCREEN_WIDTH + 1;
	randNum.y = rand() % SCREEN_HEIGHT + 1;
	return randNum;
}

Point getRandomVelocity() {
	Point randNum;
	int range = (.99 + .99 + .001) * 1000;
	randNum.x = (rand() % range) / 1000 - .99;
	randNum.y = (rand() % range) / 1000 - .99;
	return randNum;
}

bool objectsIntersect(Point p1, Point p2) {
	if ((p1.x - p2.x) < 30 && (p1.y - p2.y) < 30 && (p1.x - p2.x) > -30 && (p1.y - p2.y) > -30)
		return true;
	else
		return false;
}

