/****************************************************
* bird-types.h
* defines the three different bird types
* each bird type has a dependency on the bird class
*   which has a dependency on the flying class
*****************************************************/

#ifndef BIRDTYPES_H
#define BIRDTYPES_H

#include "bird.h"
#include "uiDraw.h"

#define BIRD_DIAMETER 15

//three bird types defined here
/****************************************
* Regular bird class
*   -destroyed with one hit
*   -awards one point when destroyed
*****************************************/
class Regular : public Bird
{
public:
	Regular() { initialize(); 
				reward = 1;
				hitPoints = 1; 
				type = 1; }
	
	void draw() { drawCircle(position, BIRD_DIAMETER); }
private:
};

/*
* Tough bird class
*   -destroyed in three hits
*   -awards one point for each hit
*   -2 bonus points if destroyed
*/
class Tough : public Bird
{
public:
	Tough() { initialize(); 
			  reward = 1; 
			  hitPoints = 3; 
			  type = 2; }

	void draw() { drawToughBird(position, BIRD_DIAMETER, hitPoints); }
private:
};

/***************************************
* Sacred bird class
*   -rendered as a star
*   -this bird should not be hit
*   -destroyed with one hit
*   -pentaly of 10 points if destroyed
****************************************/
class Sacred : public Bird
{
public:
	Sacred() { initialize(); 
			   hitPoints = 1; 
			   reward = -10; 
			   type = 3; }

	void draw() { drawSacredBird(position, BIRD_DIAMETER); }
private:
};

#endif