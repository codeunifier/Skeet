/*************************************************************
 * File: game.cpp
 *
 * Description: Contains the implementations of the
 *  method bodies for the game class.
 *
 * Please DO NOT share this code with other students from
 *  other sections or other semesters. They may not receive
 *  the same code that you are receiving.
 *************************************************************/

#include "game.h"

 //for sounds
#ifdef _WIN32 || _WIN64
#include <Windows.h>
#pragma comment(lib, "Winmm.lib")
#endif //Windows

#include <vector>
using namespace std;

#define OFF_SCREEN_BORDER_AMOUNT 5


/***************************************
 * GAME CONSTRUCTOR
 ***************************************/
Game :: Game(Point tl, Point br)
 : topLeft(tl), bottomRight(br), rifle(br)
{
   // Set up the initial conditions of the game
   score = 0;

   bird = NULL;
}

/****************************************
 * GAME DESTRUCTOR
 ****************************************/
Game :: ~Game()
{
   // TODO: Check to see if there is currently a bird allocated
   //       and if so, delete it.
	if (bird != NULL)
		delete bird;
}

/***************************************
 * GAME :: ADVANCE
 * advance the game one unit of time
 ***************************************/
void Game :: advance()
{
   advanceBullets();
   advanceBird();

   handleCollisions();
   cleanUpZombies();
}

/***************************************
 * GAME :: ADVANCE BULLETS
 * Go through each bullet and advance it.
 ***************************************/
void Game :: advanceBullets()
{
   // Move each of the bullets forward if it is alive
   for (int i = 0; i < bullets.size(); i++)
   {
      if (bullets[i].isAlive())
      {
         // this bullet is alive, so tell it to move forward
         bullets[i].advance();

         if (!isOnScreen(bullets[i].getPoint()))
         {
            // the bullet has left the screen
            bullets[i].kill();
         }
         
      }
   }
}

/**************************************************************************
 * GAME :: ADVANCE BIRD
 *
 * 1. If there is no bird, create one with some probability
 * 2. If there is a bird, and it's alive, advance it
 * 3. Check if the bird has gone of the screen, and if so, "kill" it
 **************************************************************************/
void Game :: advanceBird()
{
   if (bird == NULL)
   {
      // there is no bird right now, possibly create one
      
      // "resurrect" it will some random chance
      if (random(0, 30) == 0)
      {
         // create a new bird
         bird = createBird();
      }
   }
   else
   {
      // we have a bird, make sure it's alive
      if (bird->isAlive())
      {
         // move it forward
         bird->advance();
         
         // check if the bird has gone off the screen
         if (!isOnScreen(bird->getPoint()))
         {
            // We have missed the bird
            bird->kill();
         }
      }
   }  
}

/**************************************************************************
 * GAME :: CREATE BIRD
 * Create a bird of a random type according to the rules of the game.
 **************************************************************************/
Bird* Game :: createBird()
{
   Bird* newBird = NULL;
   
   // TODO: Fill this in
   switch (random(1, 4))
   {   
   case 1:
	   //regular bird
	   newBird = new Regular;
	   break;
   case 2:
	   //tough bird
	   newBird = new Tough;
	   break;
   case 3:
	   //sacred bird
	   newBird = new Sacred;
	   break;
   }
   
   return newBird;
}

/**************************************************************************
 * GAME :: IS ON SCREEN
 * Determines if a given point is on the screen.
 **************************************************************************/
bool Game :: isOnScreen(const Point & point)
{
   return (point.getX() >= topLeft.getX() - OFF_SCREEN_BORDER_AMOUNT
      && point.getX() <= bottomRight.getX() + OFF_SCREEN_BORDER_AMOUNT
      && point.getY() >= bottomRight.getY() - OFF_SCREEN_BORDER_AMOUNT
      && point.getY() <= topLeft.getY() + OFF_SCREEN_BORDER_AMOUNT);
}

/**************************************************************************
 * GAME :: HANDLE COLLISIONS
 * Check for a collision between a bird and a bullet.
 **************************************************************************/
void Game :: handleCollisions()
{
   // now check for a hit (if it is close enough to any live bullets)
   for (int i = 0; i < bullets.size(); i++)
   {
      if (bullets[i].isAlive())
      {
         // this bullet is alive, see if its too close

         // check if the bird is at this point (in case it was hit)
         if (bird != NULL && bird->isAlive())
         {
            // BTW, this logic could be more sophisiticated, but this will
            // get the job done for now...
            if (fabs(bullets[i].getPoint().getX() - bird->getPoint().getX()) < CLOSE_ENOUGH
                && fabs(bullets[i].getPoint().getY() - bird->getPoint().getY()) < CLOSE_ENOUGH)
            {
               //we have a hit!
               
               // hit the bird
               int points = bird->hit();
               score += points;
               
               // the bullet is dead as well
               bullets[i].kill();
            }
         }
      } // if bullet is alive
      
   } // for bullets
}

/**************************************************************************
 * GAME :: CLEAN UP ZOMBIES
 * Remove any dead objects (take bullets out of the list, deallocate bird)
 **************************************************************************/
void Game :: cleanUpZombies()
{
   // check for dead bird
   if (bird != NULL && !bird->isAlive())
   {
      // the bird is dead, but the memory is not freed up yet
      
      // TODO: Clean up the memory used by the bird
	   delete bird;
	   bird = NULL;
   }
   
   // Look for dead bullets
   vector<Bullet>::iterator bulletIt = bullets.begin();
   while (bulletIt != bullets.end())
   {
      Bullet bullet = *bulletIt;
      // Asteroids Hint:
      // If we had a list of pointers, we would need this line instead:
      //Bullet* pBullet = *bulletIt;
      
      if (!bullet.isAlive())
      {
         // If we had a list of pointers, we would need to delete the memory here...
         
         
         // remove from list and advance
         bulletIt = bullets.erase(bulletIt);
      }
      else
      {
         bulletIt++; // advance
      }
   }
   
}

/***************************************
 * GAME :: HANDLE INPUT
 * accept input from the user
 ***************************************/
void Game :: handleInput(const Interface & ui)
{
	if (!frozen)
	{
		// Change the direction of the rifle
		if (ui.isLeft())
		{
			rifle.moveLeft();
		}

		if (ui.isRight())
		{
			rifle.moveRight();
		}

		// Check for Spacebar
		if (ui.isSpace())
		{
			#ifdef _WIN32 || _WIN64
			PlaySound("C:\\LASER.WAV", NULL, SND_ASYNC);
			#endif

			Bullet newBullet(difficulty);
			newBullet.fire(rifle.getPoint(), rifle.getAngle());

			bullets.push_back(newBullet);
		}
	}
	else
	{
		if (ui.isRight())
			difficulty = 1;		//easy
		if (ui.isDown())
			difficulty = 2;		//medium
		if (ui.isLeft())
			difficulty = 3;		//hard

		if (ui.isSpace())
		{
			if (difficulty > 0 && difficulty < 4)
				frozen = false;
		}
	}
}

/*********************************************
 * GAME :: DRAW
 * Draw everything on the screen
 *********************************************/
void Game :: draw(const Interface & ui)
{
	if (!frozen)
	{
		// draw the bird
		if (bird != NULL && bird->isAlive())
			bird->draw();

		// draw the rifle
		rifle.draw();

		// draw the bullets, if they are alive
		for (int i = 0; i < bullets.size(); i++)
		{
			if (bullets[i].isAlive())
			{
				bullets[i].draw();
			}
		}

		// Put the score on the screen
		Point scoreLocation;
		scoreLocation.setX(topLeft.getX() + 5);
		scoreLocation.setY(topLeft.getY() - 5);

		drawNumber(scoreLocation, score);
	}
	else
	{
		displayMenu();
	}

}

/******************************************************************************
* displayMenu() displays the game menu at the start of the game
*		the user is able to select difficulty level by pressing arrow keys
*		pressing the spacebar will begin the game, and the menu will disappear
*******************************************************************************/
void Game::displayMenu()
{
	float menuX = -90;
	float menuY = 80;
	Point p = { menuX, menuY };

	drawText(p, "Welcome to the game of Skeet!");
	p = { menuX, menuY - 20 };
	drawText(p, "Press the spacebar to start the game");

	p = { menuX, menuY - 40 };
	drawText(p, "Please select your difficulty:");
	p = { menuX, menuY - 55 };
	drawText(p, "Easy: right arrow key");
	p = { menuX, menuY - 70 };
	drawText(p, "Medium: down arrow key");
	p = { menuX, menuY - 85 };
	drawText(p, "Hard: left arrow key");

	p = { menuX, menuY - 105 };
	switch (difficulty)
	{
	case 1:
		drawText(p, "Selected difficulty: easy");
		break;
	case 2:
		drawText(p, "Selected difficulty: medium");
		break;
	case 3:
		drawText(p, "Selected difficulty: hard");
		break;
	}
}

//getter for the frozen variable
bool Game::getFrozen()
{
	return frozen;
}

//setter for the frozen variable
void Game::setFrozen(bool f)
{
	frozen = f;
}