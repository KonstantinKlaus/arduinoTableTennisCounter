#include <Arduino.h>
#include <MD_MAX72xx.h>
#include <IRremote.h>
#include <Game.h>
#include <Input.h>
#include <Output.h>


// game
Game game = Game();

int playerLeft;
int playerRight;

bool updateDisplay = false;

char message[BUF_SIZE];

void changeover();

void changeover()
{
	int temp = playerLeft;
	playerLeft = playerRight;
	playerRight = temp;
}


void setup()
{
	setupInput();
	setupOutput();
	
	sprintf(message, "%02d : %02d", game.getPoints(0), game.getPoints(1));
	printText(0, MAX_DEVICES-1, message);

	playerLeft = Game::PLAYER_1;
	playerRight = Game::PLAYER_2;
}

void loop()
{
	// check input
	int input_state = checkInput();

	switch (input_state)
	{
		case PWR:
			game.resetGame();
			updateDisplay = true;
			break;

		case EQ:
			game.revertGame();
			updateDisplay = true;
			break;

		case BUTTON_2:
		case FOREWARD:
			game.playerGetPoint(playerRight);
			updateDisplay = true;
			break;

		case BUTTON_1:
		case BACK:
			game.playerGetPoint(playerLeft);
			updateDisplay = true;
			break;

		case PLAY:
			changeover();
			updateDisplay = true;
			break;
		
		default:
			break;
	} 

	// change output
	if (updateDisplay)
	{
		sprintf(message, "%02d : %02d", game.getPoints(playerLeft), game.getPoints(playerRight));
		printText(0, MAX_DEVICES-1, message);
		updateDisplay = false;
	}
}
