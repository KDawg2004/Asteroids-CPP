#pragma once
#include <SFML/Graphics.hpp>

struct Point {
	double x;
	double y;
};

enum SpaceObjType { SHIP, ASTEROID, PHOTON_TORPEDO, SHIP_EXPLODING, SHIP_GONE};

class SpaceObject {

public:
	/*
	Initializes all parts of the space object, sets to an astriod
	*/
	SpaceObject();
	/*
	Given input into the parameters will allow you to change the params of the object
	*/
	SpaceObject(SpaceObjType type, double radius,
		Point location, Point velocity, double angle);
	//=============================================
	//mutators

/** --------------------------------------------------------------------------
*   Draws the spaceobject on the given window
*
* 	@param win - the window on which we’ll draw the ship
---------------------------------------------------------------------------- */
	void draw(sf::RenderWindow& win);

	/*
	set the radius to given value 
	@param radius - the radius of space object(radius<30)
	*/
	bool setRadius(int radius);
	/*
	set the location to X and Y value
	@param x - the location of X cordinate(x<screen width)
	@param y - the location of Y cordinate(y<screen height)
	*/
	bool setLocation(double x, double y);
	/*
	set the velocity to X and Y value
	@param velocityX - the velocity of X cordinate
	@param velocityY - the velocity of Y cordinate
	*/
	bool setVelocity(double velocityX, double velocityY);
	/*
	set the angle to a degree
	@param angDeg - the new set angle degree
	*/
	bool setAngle(double angDeg);
	/*
	change angle by given amount.
	@param deltaDeg - how much you want the angle to change by
	*/
	void changeAngle(double deltaDeg);

	bool setType(int type);

	void explode();

	//============================================
	//accessors
	/*
	Provides information through the console window about radius param
	*/
	double getRadius() const;
	/*
	Provides information through the console window about loaction(x,y) param
	*/
	Point getLocation() const;
	/*
	Provides information through the console window about velocity(x,y) param
	*/
	Point getVelocity() const;
	/*
	Provides information through the console window about angle param
	*/
	double getAngle() const;

	//============================================
	//others
	/*
	Updates the location based on the current velocity.  (adds the velocity vector values (x,y) to the location). 
	*/
	void updatePosition();
	/*
	Dumps all known data of the "spaceObject"
	*/
	void dumpData() const; 
	/*
	Apllys thrust to the rocket ship
	*/
	void applyThrust();
private:
	SpaceObjType type;	  //type of object
	Point location;	  //current location (x,y)
	Point velocity;	  //current velocity (in pixels/frame)
	double angleDeg;	  //angle object is facing (in degrees)
	double radius;        //gross radius of object (for collision detection)

/** --------------------------------------------------------------------------
*   Draws the spaceobject on the given window as a ship
*
* 	@param win - the window on which we’ll draw the ship
---------------------------------------------------------------------------- */
	void drawShip(sf::RenderWindow& win);
/*
*   Draws the spaceobject on the given window as an asteroid
*
* 	@param win - the window on which we’ll draw the ship
*/
	void drawAsteroid(sf::RenderWindow& win);

	void drawShipExploding(sf::RenderWindow& win);
};

