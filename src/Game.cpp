#include <Game.h>

Game::Game()
{

}

void Game::playerGetSetPoint(player player)
{
    pointsP1 = 0;
    pointsP2 = 0;
	if (player == player_1)
	{
		setPointsP1 = setPointsP1 + 1;

	} else if (player == player_2)
	{
		setPointsP2 = setPointsP2 + 1;
	}
}


void Game::playerGetPoint(player player)
{
	backupGameState();
	if (player == player_1)
	{
		pointsP1 = pointsP1 + 1;

		if (pointsP1 > 10 and (pointsP1 - pointsP2) > 1)
		{
			playerGetSetPoint(player_1);
		} 
	} else if (player == player_2)
	{
		pointsP2 = pointsP2 + 1;
		if (pointsP2 > 10 and (pointsP2 - pointsP1) > 1)
		{
			playerGetSetPoint(player_2);
		} 
	}

	// every two point, right of service switches
	if ((pointsP1 + pointsP2) % 2 == 0)
	{
		switchRightOfService();
	} 
}


void Game::resetGame()
{
	backupGameState();
	pointsP1 = 0;
	pointsP2 = 0;
	setPointsP1 = 0;
	setPointsP2 = 0;
	prevRightOfService = player_1;
}


void Game::backupGameState()
{
	prevPointsP1 = pointsP1;
	prevPointsP2 = pointsP2;
	prevSetPointsP2 = setPointsP2;
	prevSetPointsP1 = setPointsP1;
	prevRightOfService = rightOfService;
}


void Game::revertGame()
{
	pointsP1 = prevPointsP1;
	pointsP2 = prevPointsP2;
	setPointsP1 = prevSetPointsP1;
	setPointsP2 = prevSetPointsP2;
	rightOfService = prevRightOfService;
}


int Game::getPoints(player player)
{
    if (player == player_1)
    {
        return pointsP1;
    } else if (player == player_2)
    {
        return pointsP2;
    } else
    {
       return 0;
    }
    
}


int Game::getSetPoints(player player)
{
    if (player == player_1)
    {
        return setPointsP1;
    } else if (player == player_2)
    {
        return setPointsP2;
    } else
    {
       return 0;
    }
    
}


player Game::getServingPlayer()
{
	return rightOfService;
}


void Game::switchRightOfService()
{
	if (rightOfService == player_1)
	{
		rightOfService = player_2;
	} else {
		rightOfService = player_1;
	}
}