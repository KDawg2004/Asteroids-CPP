/*
@Author Kaevin 
@Version 0.1
@File Polygons

In this program, there lies a created class that will 
provide the base functionality for all the things 
that move across the screen (asteroids, ship, bullets, etc..).
*/

#include "spaceObject.h"

int main() {
	SpaceObjType type = SpaceObjType::SHIP;
	Point location = { 100,100 };
	Point velocity = { 4,4 };

	SpaceObject asteroid; //provides basic build for astroid type

	asteroid.dumpData();
	asteroid.setLocation(401, -3);
	asteroid.setAngle(2.1);
	asteroid.setRadius(29);
	asteroid.setVelocity(2, 1);
	asteroid.dumpData();
	asteroid = SpaceObject(type, 25, location, velocity, 2.5);
	asteroid.dumpData();
	
	
	//TODO: add more test code.  Lots more test code.
}
