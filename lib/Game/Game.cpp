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
				return;
			}

		} else if (player == player_2)
		{
			setPointsP2 = setPointsP2 + 1;
			if (setPointsP2 == 3)
			{
				curState = player2Wins;
				return;
			}
			
		}

		// reset points
		pointsP1 = 0;
		pointsP2 = 0;

		// new set new server
		if ((setPointsP1 + setPointsP2) % 2 == 1)
		{
			rightOfService = player_2;
		} else {
			rightOfService = player_1;
		}

		playersChangeover();	
	}
}


 void Game::playerGetSetPoint(playerPosition pos)
 {
	if (pos == pos_1)
	{
		playerGetSetPoint(playerPos_1);
	} else
	{
		playerGetSetPoint(playerPos_2);
	}
 }


void Game::playerGetPoint(player player)
{
	if (curState == running)
	{
		backupGameState();

		// every two point, right of service switches
		if ((pointsP1 + pointsP2 + 1) % 2 == 0)
		{
			switchRightOfService();
		}

		if (player == player_1)
		{
			pointsP1 = pointsP1 + 1;

			// set point player 1
			if (pointsP1 > 10 and (pointsP1 - pointsP2) > 1)
			{
				playerGetSetPoint(player_1);
			} 
		} else if (player == player_2)
		{
			pointsP2 = pointsP2 + 1;

			// set point player 2
			if (pointsP2 > 10 and (pointsP2 - pointsP1) > 1)
			{
				playerGetSetPoint(player_2);
			} 
		}

		// when both players have 2 set points, changeover at 5
		if (setPointsP1 == 2 && setPointsP2 == 2)
			if ((player == player_1 && pointsP1 == 5 && pointsP2 < 5)|| (player == player_2 && pointsP2 == 5 && pointsP1 < 5))
			{
				playersChangeover();
			}
		{

		}
	}
}


 void Game::playerGetPoint(playerPosition pos)
 {
	if (pos == pos_1)
	{
		playerGetPoint(playerPos_1);
	} else
	{
		playerGetPoint(playerPos_2);
	}
 }


void Game::resetGame()
{
	backupGameState();
	pointsP1 = 0;
	pointsP2 = 0;
	setPointsP1 = 0;
	setPointsP2 = 0;
	rightOfService = player_1;
	curState = running;
	playerPos_1 = player_1;
	playerPos_2 = player_2;
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
	prevPlayerPos_1 = playerPos_1;
	prevPlayerPos_2 = playerPos_2;
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
	playerPos_1 = prevPlayerPos_1;
	playerPos_2 = prevPlayerPos_2;
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


int Game::getPoints(playerPosition pos)
{
	if (pos == pos_1)
	{
		return getPoints(playerPos_1);
	} else
	{
		return getPoints(playerPos_2);
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


int Game::getSetPoints(playerPosition pos)
{
	if (pos == pos_1)
	{
		return getSetPoints(playerPos_1);
	} else
	{
		return getSetPoints(playerPos_2);
	}
}


Game::player Game::getServingPlayer()
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


Game::gameState Game::getState()
{
	return curState;
}


Game::player Game::getPlayer(playerPosition pos)
{
	if (pos == pos_1)
	{
		return playerPos_1;
	} else
	{
		return playerPos_2;
	}
	
}


void Game::playersChangeover()
{
	Game::player temp = playerPos_1;
	playerPos_1 = playerPos_2;
	playerPos_2 = temp;

	curState = changeover;
}


void Game::confirmChangeover()
{
	curState = running;
}


Game::playerPosition Game::getServingPosition()
{
	if (getServingPlayer() == playerPos_1)
	{
		return pos_1;
	} else
	{
		return pos_2;
	}
	
}