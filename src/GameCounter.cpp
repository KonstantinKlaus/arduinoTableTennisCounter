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
	
	sprintf(message, "%02d : %02d", game.getPoints(PLAYER_1), game.getPoints(PLAYER_2));
	printTextDisplay1(message);
	sprintf(message, "_%01d : %01d_", game.getSetPoints(playerLeft), game.getSetPoints(playerRight));
	printTextDisplay2(message);

	playerLeft  = PLAYER_1;
	playerRight = PLAYER_2;
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
		sprintf(message, "%02d : %02d", game.getPoints(playerLeft), game.getPoints(playerRight));
		printTextDisplay1(message);

		sprintf(message, "_%01d : %01d_", game.getSetPoints(playerLeft), game.getSetPoints(playerRight));
		printTextDisplay2(message);

		updateDisplay = false;
	}
}
