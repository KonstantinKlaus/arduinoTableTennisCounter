#include <Arduino.h>
#include <MD_MAX72xx.h>
#include <IRremote.h>
#include <Game.h>
#include <Input.h>
#include <Output.h>


// game
Game game = Game();


char message[BUF_SIZE];


void setup()
{
	setupInput();
	setupOutput();
	
	sprintf(message, "%02d : %02d", game.getPoints(0), game.getPoints(1));
	printText(0, MAX_DEVICES-1, message);
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
			game.playerGetPoint(0);
			break;

		case POINT_P2:
			game.playerGetPoint(1);
			break;
		
		default:
			break;
	} 

	// change output
	if (game.isUpdateAvailible())
	{
		sprintf(message, "%02d : %02d", game.getPoints(0), game.getPoints(1));
		printText(0, MAX_DEVICES-1, message);
		game.resetUpdate();
	}
}
