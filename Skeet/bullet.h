/*****************************
* bullet.h
* defines the bullets
******************************/


#ifndef BULLET_H
#define BULLET_H

#include <iostream>

#include "flying.h"

using namespace std;

class Bullet : public Flying
{
public:
	Bullet();
	Bullet(int);
	void advance();
	void draw();
	void fire(Point, float);
private:
	int bulletSpeed;
};

#endif