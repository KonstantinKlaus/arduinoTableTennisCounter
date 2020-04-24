#include <Game.h>

Game::Game()
{

}

void Game::playerGetSetPoint(player player)
{
	if (curState == running)
	{
		if (player == player_1)
		{
			setPointsP1 = setPointsP1 + 1;
			if (setPointsP1 == 3)
			{
				curState = player1Wins;
			}

		} else if (player == player_2)
		{
			setPointsP2 = setPointsP2 + 1;
			if (setPointsP2 == 3)
			{
				curState = player2Wins;
			}
		}

		// reset points
		pointsP1 = 0;
		pointsP2 = 0;

		// new game new server
		if ((setPointsP1 + setPointsP2) % 2 == 1)
		{
			rightOfService = player_2;
		} else {
			rightOfService = player_1;
		}
	}
}


void Game::playerGetPoint(player player)
{
	if (curState == running)
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
}


void Game::resetGame()
{
	backupGameState();
	pointsP1 = 0;
	pointsP2 = 0;
	setPointsP1 = 0;
	setPointsP2 = 0;
	prevRightOfService = player_1;
	curState = running;
}


void Game::backupGameState()
{
	// save all status variables
	prevPointsP1 = pointsP1;
	prevPointsP2 = pointsP2;
	prevSetPointsP2 = setPointsP2;
	prevSetPointsP1 = setPointsP1;
	prevRightOfService = rightOfService;
	prevState = curState;
}


void Game::revertGame()
{
	// revert all status variables
	pointsP1 = prevPointsP1;
	pointsP2 = prevPointsP2;
	setPointsP1 = prevSetPointsP1;
	setPointsP2 = prevSetPointsP2;
	rightOfService = prevRightOfService;
	curState = prevState;
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


gameState Game::getState()
{
	return curState;
}