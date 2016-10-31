/**************************************
* bullet.cpp
* function bodies for the bullet class
***************************************/

#include "bullet.h"
#include "flying.h"

#include <math.h>
#define PI 3.14159
#define DEGTORAD(angle) ((double)angle*PI/180.0)

//default constructor
Bullet::Bullet()
{
}

//non-defaul constructor which accepts an int representing game difficulty
Bullet::Bullet(int diff)
{
	switch (diff)
	{
	case 1:
		bulletSpeed = 13;
		break;
	case 2:
		bulletSpeed = 10;
		break;
	case 3:
		bulletSpeed = 7;
		break;
	}
}

/*****************************
* draw() draws the bullet
******************************/
void Bullet::draw()
{
	drawDot(position);
}

/*********************************************************************
* advance() advances the bullet's position
* the slope of an angle is the tangent of that angle (rise over run)
**********************************************************************/
void Bullet::advance()
{
	position.addX(velocity.getDx() * bulletSpeed);
	position.addY(velocity.getDy() * bulletSpeed);
}

/****************************************************
* fire() fires a bullet
* pos = starting position for the bullet
* angle = directional angle for the bullet's travel
*****************************************************/
void Bullet::fire(Point position, float angle)
{
	this->position = position;
	this->angle = angle;
	velocity.setDx(-(cos(DEGTORAD(angle))));
	velocity.setDy(sin(DEGTORAD(angle)));
	alive = true;
}