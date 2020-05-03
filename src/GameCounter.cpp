#include <Arduino.h>
#include <Game.h>
#include <Input.h>
#include <Output.h>

// * * * * * * * * * * * * * *
// constants
// * * * * * * * * * * * * * *

// Global message buffers
#define BUF_SIZE  30

// pins
// buttons
#define buttonPin1  0
#define buttonPin2  1
#define buttonPin3  2

// IR Remote
#define irPin 5

// LED Matrices 1
#define CLK_PIN   13  // or SCK
#define DATA_PIN  12  // or MOSI
#define CS_PIN    11  // or SS

// LED Matrices 2
#define CLK_PIN_2   9  // or SCK
#define DATA_PIN_2  8  // or MOSI
#define CS_PIN_2    7 // or SS


// time between display 2 toggles content
const long timeDisplayToggle = 5000; // 5 seconds

// * * * * * * * * * * * * * *
// global variables
// * * * * * * * * * * * * * *

// game
Game game = Game();

// Input
Input input = Input(buttonPin1, buttonPin2, buttonPin3, irPin);

// Ouput

Output output = Output(CLK_PIN, DATA_PIN, CS_PIN, CLK_PIN_2, DATA_PIN_2, CS_PIN_2);

// string buffer
char message[BUF_SIZE];

// LED matrix 2 - content 
bool display2ShowPosition = true;

// timer
long timestamp;

// update display flag
bool updateDisplayFlag = false;


// * * * * * * * * * * * * * *
// functions
// * * * * * * * * * * * * * *


// setup function, is called once on startup
void setup()
{
	input.setupInput();

	output.setupOutput();
	output.printPoints(Output::display_1, 0, 0);
	output.printPlayerPosition(Output::display_2, Output::left);
}


// loop function, is repeated infinitely
void loop()
{
	// check input
	int input_state = input.checkInput();

	// check for time events
	if (millis() - timestamp >= timeDisplayToggle)
	{
		timestamp = millis();
		display2ShowPosition = not display2ShowPosition;
		updateDisplayFlag = true;
	} 

	bool updateDisplay = true;

	// react on input
	switch (input_state)
	{
		case Input::button3Hold:
		case Input::pwr:
			game.resetGame();
			break;

		case Input::button_3:
		case Input::eq:
			game.revertGame();
			break;

		case Input::button_2:
		case Input::foreward:
			game.playerGetPoint(Game::pos_2);
			timestamp = millis();
			display2ShowPosition = false;
			break;

		case Input::button_1:
		case Input::back:
			game.playerGetPoint(Game::pos_1);
			timestamp = millis();
			display2ShowPosition = false;
			break;

		case Input::play:
			game.playersChangeover();
			timestamp = millis();
			display2ShowPosition = true;
			break;
		
		default:
			updateDisplay = false;
			break;
	}

	// check flag
	if (updateDisplayFlag)
	{
		updateDisplayFlag = false;
		updateDisplay = true;
	}

	// update LED matrices if necessary
	if (updateDisplay)
	{	
		updateDisplay = false;

		if (game.getState() == Game::running)
		{
			// LED matrix 1
			 output.printPoints(Output::display_1, game.getPoints(Game::pos_1), game.getPoints(Game::pos_2));

			// LED matrix 2
			if (display2ShowPosition)
			{
				// show player position
				Output::position p1Position;
				if (game.getPlayer(Game::pos_1) == Game::player_1)
				{
					p1Position = Output::left;
				} else
				{
					p1Position = Output::right;
				}
				output.printPlayerPosition(Output::display_2, p1Position);
			} else {
				// show setPoints
				Output::position rightOfService;
				if (game.getServingPosition() == Game::pos_1){
					rightOfService = Output::left;
				} else
				{
					rightOfService = Output::right;
				}
				output.printSetPoints(Output::display_2, game.getSetPoints(Game::pos_1), game.getSetPoints(Game::pos_2), rightOfService);
			}
		} else if (game.getState() == Game::changeover)
		{
			// if changeover takes place
			output.arrowAnimation();
			game.confirmChangeover();
			updateDisplayFlag = true;
		
		} else if (game.getState() == Game::player1Wins)
		{
			// P1 wins
			sprintf(message, "P1 wins");
			output.printText(Output::display_1, message);
			output.printText(Output::display_2, message);
		} else
		{
			// P2 wins
			sprintf(message, "P2 wins");
			output.printText(Output::display_1, message);
			output.printText(Output::display_2, message);
		}		
	}
}
