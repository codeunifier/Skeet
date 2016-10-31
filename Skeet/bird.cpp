/*************************************
* bird.cpp
* function bodies for the bird class 
**************************************/

#include "bird.h"

#include <math.h>
#define PI 3.14159
#define DEGTORAD(angle) ((double)angle*PI/180.0)

//for sounds
#ifdef _WIN32 || _WIN64
#include <Windows.h>
#pragma comment(lib, "Winmm.lib")
#endif //Windows

/************************************************
* advance() advances the bird across the screen
*************************************************/
void Bird::advance()
{
	position.addX(velocity.getDx());
	position.addY(velocity.getDy());
}

/***************************************************************
* hit() represents the bird being hit and should either:
* kill the bird and return an integer for the number of points
* OR decrement the number of hits remaining on the bird
****************************************************************/
int Bird::hit()
{
	hitPoints--;

	if (hitPoints == 0)
	{
		alive = false;

		#ifdef _WIN32 || _WIN64
		PlaySound("C:\\BIRD.WAV", NULL, SND_ASYNC);
		#endif

		if (type == 2)	//tough bird - +2 bonus
			return 3;
		else
			return reward;
	}
	else
		return 1;
}

/*************************************************************************************************
* initialize() initializes the variables for a bird
*      1. sets the alive variable to true
*      2. calculates the angle for trajectory
*      3. sets the initial position of the bird according to the following
*		     a. If the bird starts on the top half of the screen, 
*				it should have a generally downward velocity
*			 b. If the bird starts on the bottom half of the screen, 
*				it should have a generally upward velocity
*      4. calculates velocity according to the following
*			 a. The horizontal component of the velocity should be between 3 and 6 pixels/frame.
*			 b. The vertical component of the velocity should be between -4 and +4 pixels/frame
*				(positive or negative depending on whether it starts on the top or 
*				bottom half of the screen).
*			 c. To give the user a greater chance to hit the Tough Bird, 
*				it should move more slowly than the others. In particular, its horizontal velocity 
*				should be taken from the range: 2 to 4, and it's vertical velocity from 
*				the range -3 to +3.
*************************************************************************************************/
void Bird::initialize()
{
	//set bird to be alive
	alive = true;

	//set initial position
	position.setX(-190);
	position.setY(random(-190, 190));

	//calculate angle
	if (position.getY() > 0)
		angle = random(-80, -10);
	else
		angle = random(10, 80);

	//calculate velocity
	if (type == 2)
	{
		//tough bird moves slower
		velocity.setDx(cos(DEGTORAD(angle)) * random(2, 5));
		velocity.setDy(sin(DEGTORAD(angle)) * random(1, 4));
	}
	else
	{
		velocity.setDx(cos(DEGTORAD(angle)) * random(3, 7));
		velocity.setDy(sin(DEGTORAD(angle)) * random(1, 5));
	}
}