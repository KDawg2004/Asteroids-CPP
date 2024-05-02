#include <iostream>
#include "spaceObject.h"
#include "constants.h"
#include <math.h>


SpaceObject::SpaceObject() {
	type = SpaceObjType::ASTEROID;
	radius = 20;
	location.x = 200;
	location.y = 200;
	velocity.x = 1;
	velocity.y = 1;
	angleDeg = 1;
}

SpaceObject::SpaceObject(SpaceObjType type, double radius, Point location, Point velocity, double angle){
	if (type == SpaceObjType::ASTEROID || type == SpaceObjType::SHIP || type == SpaceObjType::PHOTON_TORPEDO)
		this->type = type;

	if (radius < 30 && radius > 0)
		this->radius = radius;

	if (location.x > 0 && location.x < 400 && location.y > 0 && location.y < 400)
		this->location = location;

	if (velocity.x > 0 && velocity.x < 10 && velocity.y > 0 && velocity.x < 10 )
		this->velocity = velocity;

	this->angleDeg = angle;
}

bool SpaceObject::setRadius(int radius){
	if (radius > 0 && radius < 200) {
		this->radius = radius;
		return true;
	}
	else
		return false;
}

bool SpaceObject::setLocation(double x, double y){
	while (x > 400 || x < 0 || y > 400 || y < 0) {
		if (x > SCREEN_WIDTH)
			x = x - SCREEN_WIDTH;
		if (x < 0)
			x = x + SCREEN_WIDTH;
		if (y > SCREEN_HEIGHT)
			y = y - SCREEN_HEIGHT;
		if (y < 0)
			y = y + SCREEN_HEIGHT;
	}
	location.x = x;
	location.y = y;

		return true;
}

bool SpaceObject::setVelocity(double velocityX, double velocityY){
	
		velocity.x = velocityX;
		velocity.y = velocityY;
	

	return false;
}

bool SpaceObject::setAngle(double angDeg){
	angleDeg = angDeg;

	return false;
}

double SpaceObject::getRadius() const{
	std::cout << "RADIUS:" << radius << "\n";

	return 0;
}

void SpaceObject::dumpData() const {
	std::cout << "---------DUMP DATA---------" << "\n"
		<< "TYPE:";

	if (type == SpaceObjType::ASTEROID)
		std::cout << "Astroid" << "\n";
	if (type == SpaceObjType::SHIP)
		std::cout << "Ship" << "\n";
	if (type == SpaceObjType::PHOTON_TORPEDO)
		std::cout << "Photon Torpedo" << "\n";

	std::cout
		<< "LOCATION(X,Y):" << location.x << ", " << location.y << "\n"
		<< "VELOCITY(X,Y):" << velocity.x << ", " << velocity.y << "\n"
		<< "ANGLE:" << angleDeg << "\n" << "RADIUS:" << radius << "\n";
}

Point SpaceObject::getLocation() const {
	//std::cout << "Location(X,Y):" << location.x << " " << location.y << "\n";

	return location;
}

Point SpaceObject::getVelocity() const {
	std::cout << "Velocity(X,Y):" << velocity.x << ", " << velocity.y << "\n";

	return velocity;
}

double SpaceObject::getAngle() const {
	std::cout << "Angle: " << angleDeg << "\n";

	return 0;
}

void SpaceObject::changeAngle(double deltaDeg) {
	if (this->type == SpaceObjType::SHIP) {
		angleDeg = angleDeg + deltaDeg;
	}
}

void SpaceObject::updatePosition() {
	if (location.x != NULL && location.y != NULL)
	setLocation(location.x + velocity.x, location.y + velocity.y);
}

void SpaceObject::draw(sf::RenderWindow& win) {
	if (type == SHIP)
		drawShip(win);
	else if (type == ASTEROID)
		drawAsteroid(win);
	else if(type == SHIP_EXPLODING)
		drawShipExploding(win);
	

}

void SpaceObject::drawAsteroid(sf::RenderWindow& win) {
	//Configure a graphics object to be used for drawing our object
	//this code draws a simple pentagon.Feel free to modify it if you want.
	int points = 5;
	sf::CircleShape shape(radius, points); //radius from our SpaceObject

	sf::Vector2f midpoint(radius, radius);
	shape.setOrigin(midpoint);

	shape.setFillColor(sf::Color(0, 0, 0));
	shape.setOutlineThickness(1);
	shape.setOutlineColor(sf::Color(255, 255, 255));

	//apply our object position to the graphics object and draw it
	shape.setPosition(location.x, location.y);
	shape.setRotation(angleDeg);

	win.draw(shape);
}


void SpaceObject::drawShip(sf::RenderWindow& win) {
	// draw ship
	sf::ConvexShape shipShape;
	shipShape.setPointCount(3);
	shipShape.setPoint(0, sf::Vector2f(10, 0));
	shipShape.setPoint(1, sf::Vector2f(0, 25));
	shipShape.setPoint(2, sf::Vector2f(20, 25));

	sf::Vector2f midpoint(10, 15);
	shipShape.setOrigin(midpoint);

	shipShape.setFillColor(sf::Color(0, 0, 0));
	shipShape.setOutlineThickness(1);
	shipShape.setOutlineColor(sf::Color(255, 255, 255));

	shipShape.setPosition(location.x, location.y);
	shipShape.setRotation(angleDeg);
	win.draw(shipShape);
}

void SpaceObject::applyThrust() {
	if (this->type == SpaceObjType::SHIP) {
		double engineThrust = 0.05;
		double forcex = cos((angleDeg - 90) * PIE / 180) * engineThrust;
		double forcey = sin((angleDeg - 90) * PIE / 180) * engineThrust;
		velocity.x = velocity.x + forcex;
		velocity.y = velocity.y + forcey;
	}
}

bool SpaceObject::setType(int type) {
	if (type == 0)
		this->type = SpaceObjType::ASTEROID;
	if (type == 1)
		this->type = SpaceObjType::SHIP;
	if (type == 2)
		this->type = SpaceObjType::PHOTON_TORPEDO;



	return 0;

}

void SpaceObject::explode() {
	this->type = SpaceObjType::SHIP_EXPLODING;
	this->velocity.x = 0;
	this->velocity.y = 0;


}

void SpaceObject::drawShipExploding(sf::RenderWindow& win) {
	int points = 50;

	radius = radius + .1;

	if (radius > 40) {
		type = SHIP_GONE;
		std::cout << "Game Over" << "\n";
	}
	sf::CircleShape shipExploding(radius, points); //radius from our SpaceObject

	sf::Vector2f midpoint(radius, radius);
	shipExploding.setOrigin(midpoint);

	shipExploding.setFillColor(sf::Color(0, 0, 0));
	shipExploding.setOutlineThickness(1);
	shipExploding.setOutlineColor(sf::Color(255, 255, 255));

	//apply our object position to the graphics object and draw it
	shipExploding.setPosition(location.x, location.y);
	shipExploding.setRotation(angleDeg);

	win.draw(shipExploding);

}



