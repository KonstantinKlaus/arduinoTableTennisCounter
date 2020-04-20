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
		case RESET:
			game.resetGame();
			break;

		case REVERT:
			game.revertGame();
			break;

		case POINT_P1:
			game.playerGetPoint(Game::PLAYER_1);
			break;

		case POINT_P2:
			game.playerGetPoint(Game::PLAYER_2);
			break;

		case CHANGEOVER:
			changeover();
			break;
		
		default:
			break;
	} 

	// change output
	if (game.isUpdateAvailible())
	{
		sprintf(message, "%02d : %02d", game.getPoints(playerLeft), game.getPoints(playerRight));
		printText(0, MAX_DEVICES-1, message);
		game.resetUpdate();
	}
}
