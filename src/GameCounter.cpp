#include <Arduino.h>
#include <Game.h>
#include <Input.h>
#include <Output.h>

// * * * * * * * * * * * * * *
// constants
// * * * * * * * * * * * * * *

// time between display 2 toggles content
const long timeDisplayToggle = 5000; // 5 seconds

// * * * * * * * * * * * * * *
// global variables
// * * * * * * * * * * * * * *

// game
Game game = Game();



// string buffer
char message[BUF_SIZE];


// LED matrix 2 - content 
bool display2ShowPosition = true;

// timer
long timestamp;

// * * * * * * * * * * * * * *
// function prototypes
// * * * * * * * * * * * * * *



// * * * * * * * * * * * * * *
// functions
// * * * * * * * * * * * * * *


// setup function, is called once on startup
void setup()
{
	setupInput();
	setupOutput();

	printPoints(display_1, 0, 0);

	printPlayerPosition(display_2, left);
}


// loop function, is repeated infinitely
void loop()
{
	// check input
	int input_state = checkInput();

	bool updateDisplay = true;

	// react on input
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
			game.playerGetPoint(Game::pos_2);
			timestamp = millis();
			display2ShowPosition = false;
			break;

		case BUTTON_1:
		case BACK:
			game.playerGetPoint(Game::pos_1);
			timestamp = millis();
			display2ShowPosition = false;
			break;

		case PLAY:
			game.changeover();
			timestamp = millis();
			display2ShowPosition = true;
			break;
		
		default:
			updateDisplay = false;
			break;
	}

	// check for time events
	if (millis() - timestamp >= timeDisplayToggle)
	{
		timestamp = millis();
		display2ShowPosition = not display2ShowPosition;
		updateDisplay = true;
	} 

	// update LED matrices if necessary
	if (updateDisplay)
	{	
		if (game.getState() == Game::running)
		{
			// LED matrix 1
			printPoints(display_1, game.getPoints(Game::pos_1), game.getPoints(Game::pos_2));

			// LED matrix 2
			if (display2ShowPosition)
			{
				// show player position
				position p1Position;
				if (game.getPlayer(Game::pos_1) == Game::player_1)
				{
					p1Position = left;
				} else
				{
					p1Position = right;
				}
				printPlayerPosition(display_2, p1Position);
			} else {
				// show setPoints
				position rightOfService;
				if (game.getServingPosition() == Game::pos_1){
					rightOfService = left;
				} else
				{
					rightOfService = right;
				}
				printSetPoints(display_2, game.getSetPoints(Game::pos_1), game.getSetPoints(Game::pos_2), rightOfService);
			}
		} else
		{
			// if game finished
			if (game.getState() == Game::player1Wins)
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
		updateDisplay = false;
	}
}
