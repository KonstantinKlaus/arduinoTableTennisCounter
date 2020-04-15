#include <Game.h>

Game::Game()
{

}

void Game::playerGetSetPoint(int playerID)
{
    pointsP1 = 0;
    pointsP2 = 0;
	if (playerID == 0)
	{
		gamePointsP1 = gamePointsP1 + 1;
		updated = true;

	} else if (playerID == 1)
	{
		gamePointsP2 = gamePointsP2 + 1;
		updated = true; 
	}
}


void Game::playerGetPoint(int playerID)
{
	backupGameState();
	if (playerID == 0)
	{
		pointsP1 = pointsP1 + 1;
		updated = true;

		if (pointsP1 > 10 and (pointsP1 - pointsP2) > 1)
		{
			playerGetSetPoint(0);
		} 
	} else if (playerID == 1)
	{
		pointsP2 = pointsP2 + 1;
		updated = true; 
		if (pointsP2 > 10 and (pointsP2 - pointsP1) > 1)
		{
			playerGetSetPoint(1);
		} 
	}
}


void Game::resetGame()
{
	backupGameState();
	pointsP1 = 0;
	pointsP2 = 0;
	gamePointsP1 = 0;
	gamePointsP2 = 0;
	updated = true;
}


void Game::backupGameState()
{
	prevPointsP1 = pointsP1;
	prevPointsP2 = pointsP2;
	prevGamePointsP1 = gamePointsP1;
	prevGamePointsP2 = gamePointsP2;
}


void Game::revertGame()
{
	pointsP1 = prevPointsP1;
	pointsP2 = prevPointsP2;
	gamePointsP1 = prevGamePointsP1;
	gamePointsP2 = prevGamePointsP2;
	updated = true;
}


bool Game::isUpdateAvailible()
{
	return updated;
}


void Game::resetUpdate()
{
	updated = false;
}


int Game::getPoints(int playerID)
{
    if (playerID == 0)
    {
        return pointsP1;
    } else if (playerID == 1)
    {
        return pointsP2;
    } else
    {
       return 0;
    }
    
}