/***************************************************
* bird.h
* defines the bird class
* bird IS-A flying object - bird has a dependency 
*    on the flying class
***************************************************/

#ifndef BIRD_H
#define BIRD_H

#include <iostream>

#include "flying.h"

using namespace std;

class Bird : public Flying
{
public:
	void advance();
	virtual void draw() = 0;
	int hit();
protected:
	int reward;
	void initialize();
	int type;
	int hitPoints;
private:
};

#endif