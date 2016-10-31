/**************************************************************
* flying.h
* defines the flying class
* flying class has dependants: bird class (and each bird type)
***************************************************************/

#ifndef FLYING_H
#define FLYING_H

#include "point.h"
#include "velocity.h"
#include "uiDraw.h"

class Flying
{
public:
	Flying();
	Point getPoint();
	void setPoint(Point);
	Velocity getVelocity();
	void setVelocity(Velocity);
	bool isAlive();
	void setAlive(bool);
	void kill();
protected:
	Point position;
	bool alive;
	Velocity velocity;
	float angle;
private:
};

#endif