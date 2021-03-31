#include "GameManager.h"

int main()
{

	// Initialize these two variables if you want
	pair<int, int> startingPosition(54, 20);
	Orientation orientation = Orientation::x;
	Levels levelType = Levels::unboxed;

	// State control variables
	bool fruitUnavailable = true;
	bool isHit = false;

	// Game manager object
	GameManager gameManager;

	// Get the player details and the difficulty level
	while(gameManager.GetPlayerData()) {}
	// Initialize settings for the console and the snake
	gameManager.InitializeSettings(startingPosition, levelType, orientation);
	// Add a fruit
	gameManager.AddFruit();
	fruitUnavailable = false;

	// Main game loop
	while(true)
	{
		// Check if the snake has made a hit
		if(!isHit)
		{
			// Add fruit if the fruit is eaten
			if(fruitUnavailable)
			{
				gameManager.AddFruit();
				fruitUnavailable = false;
			}

			// Update the snake by getting inputs
			gameManager.SnakeUpdate(gameManager.GetInput());

			// Check for hits
			switch(gameManager.GetHitType())
			{
				case HitType::fruit:
					gameManager.ScoreUpdate();
					fruitUnavailable = true;
					break;
				case HitType::self:
					isHit = true;
					break;
				default:
					break;
			}
		}
		else
		{
			// Do a kill effect
			gameManager.DoKillEffect();
			break;
		}
	}
	// Show the end screen
	gameManager.PrintEndScreen();
	return 0;
}