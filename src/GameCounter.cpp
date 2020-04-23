#include <Arduino.h>
#include <Game.h>
#include <Input.h>
#include <Output.h>


// game
Game game = Game();

player playerLeft;
player playerRight;

char message[BUF_SIZE];

void changeover();

void changeover()
{
	player temp = playerLeft;
	playerLeft = playerRight;
	playerRight = temp;
}


void setup()
{
	setupInput();
	setupOutput();

	playerLeft  = player_1;
	playerRight = player_2;

	printPoints(display_1, 0, 0);

	sprintf(message, "P1 : P2");
	printText(display_2, message);
}

void loop()
{
	// check input
	int input_state = checkInput();

	bool updateDisplay = true;

	switch (input_state)
	{
		case PWR:
			game.resetGame();
			break;

		case EQ:
			game.revertGame();
			break;

		case BUTTON_2:
		case FOREWARD:
			game.playerGetPoint(playerRight);
			break;

		case BUTTON_1:
		case BACK:
			game.playerGetPoint(playerLeft);
			break;

		case PLAY:
			changeover();
			break;
		
		default:
			updateDisplay = false;
			break;
	}

	// change output
	if (updateDisplay)
	{
		if (game.getState() == running)
		{
			printPoints(display_1, game.getPoints(playerLeft), game.getPoints(playerRight));

			position rightOfService;
			if (playerLeft == game.getServingPlayer()){
				rightOfService = left;
			} else
			{
				rightOfService = right;
			}
			
			printSetPoints(display_2, game.getSetPoints(playerLeft), game.getSetPoints(playerRight), rightOfService);

			updateDisplay = false;
		} else
		{
			if (game.getState() == player1Wins)
			{
				// P1 wins
				sprintf(message, "P1 wins");
				printText(display_1, message);
				printText(display_2, message);
			} else
			{
				// P2 wins
				sprintf(message, "P2 wins");
				printText(display_1, message);
				printText(display_2, message);
			}
			
		} 

	}
}
