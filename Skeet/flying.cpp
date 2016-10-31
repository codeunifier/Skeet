/**************************************************************
* flying.cpp
* function bodies for the flying class
* flying class has dependants: bird class (and each bird type)
***************************************************************/

#include "flying.h"
#include <iostream>

Flying::Flying()
{
}

//getter for the Point variable
Point Flying::getPoint()
{
	return position;
}

//setter for the Point variable
void Flying::setPoint(Point position)
{
	this->position = position;
}

//getter for the Velocity variable
Velocity Flying::getVelocity()
{
	return velocity;
}

//setter for the Velocity variable
void Flying::setVelocity(Velocity velocity)
{
	this->velocity = velocity;
}

/***************************************************************
* returns alive boolean variable
****************************************************************/
bool Flying::isAlive()
{
	return alive;
}

/***************************************************************
* sets the alive boolean variable
****************************************************************/
void Flying::setAlive(bool alive)
{
	this->alive = alive;
}

/**************************************************************
* kill() kills the flying object in the event of a collision 
* or when the object leaves the screen
***************************************************************/
void Flying::kill()
{
	alive = false;
}