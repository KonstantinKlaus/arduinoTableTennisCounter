#include <Game.h>

Game::Game()
{

}

void Game::playerGetSetPoint(int playerID)
{
    pointsP1 = 0;
    pointsP2 = 0;
	if (playerID == PLAYER_1)
	{
		setPointsP1 = setPointsP1 + 1;

	} else if (playerID == PLAYER_2)
	{
		setPointsP2 = setPointsP2 + 1;
	}
}


void Game::playerGetPoint(int playerID)
{
	backupGameState();
	if (playerID == PLAYER_1)
	{
		pointsP1 = pointsP1 + 1;

		if (pointsP1 > 10 and (pointsP1 - pointsP2) > 1)
		{
			playerGetSetPoint(0);
		} 
	} else if (playerID == PLAYER_2)
	{
		pointsP2 = pointsP2 + 1;
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
	setPointsP1 = 0;
	setPointsP2 = 0;
}


void Game::backupGameState()
{
	prevPointsP1 = pointsP1;
	prevPointsP2 = pointsP2;
	prevSetPointsP2 = setPointsP2;
	prevSetPointsP1 = setPointsP1;
}


void Game::revertGame()
{
	pointsP1 = prevPointsP1;
	pointsP2 = prevPointsP2;
	setPointsP1 = prevSetPointsP1;
	setPointsP2 = prevSetPointsP2;
}


int Game::getPoints(int playerID)
{
    if (playerID == PLAYER_1)
    {
        return pointsP1;
    } else if (playerID == PLAYER_2)
    {
        return pointsP2;
    } else
    {
       return 0;
    }
    
}


int Game::getSetPoints(int playerID)
{
    if (playerID == PLAYER_1)
    {
        return setPointsP1;
    } else if (playerID == PLAYER_2)
    {
        return setPointsP2;
    } else
    {
       return 0;
    }
    
}