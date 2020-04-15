#include <Arduino.h>
#include <MD_MAX72xx.h>
#include <IRremote.h>
#include <Game.h>


// Define the number of devices we have in the chain and the hardware interface
// NOTE: These pin numbers will probably not work with your hardware and may
// need to be adapted
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4

#define CLK_PIN   13  // or SCK
#define DATA_PIN  12  // or MOSI
#define CS_PIN    11  // or SS

// SPI hardware interface
//MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
// Arbitrary pins
MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

// Text parameters
#define CHAR_SPACING  1 // pixels between characters

// Global message buffers shared by Serial and Scrolling functions
#define BUF_SIZE  30
char message[BUF_SIZE];

// buttons
const int buttonIntervall = 300;

const int buttonPin1 = 0;
int button1State = HIGH;
unsigned long button1Time = 0;

const int buttonPin2 = 1;
int button2State = HIGH;
unsigned long button2Time = 0;

// IR Remote
const int irPin = 5;
IRrecv irrecv(irPin);
decode_results results;

// IR Remote Keys
#define PWR 		0xFFA25D
#define VOL_UP     	0xFF629D
#define FUNC		0xFFE21D
#define BACK    	0xFF22DD
#define PLAY    	0xFF02FD
#define FOREWARD    0xFFC23D
#define DOWN    	0xFFE01F
#define VOL_DOWN    0xFFA857
#define UP          0xFF906F
#define EQ          0xFF9867
#define ST          0xFFB04F
#define NUM_1       0xFF30CF
#define NUM_0       0xFD30CF
#define NUM_2       0xFF18E7
#define NUM_3       0xFF7A85
#define NUM_4       0xFF10EF
#define NUM_5       0xFF38C7
#define NUM_6       0xFF5AA5
#define NUM_7       0xFF42BD
#define NUM_8       0xFF4AB5
#define NUM_9       0xFF52AD       


//game
Game game = Game();

// function prototypes
void printText(uint8_t modStart, uint8_t modEnd, char *pMsg);
void checkInput();


// Print the text string to the LED matrix modules specified.
// Message area is padded with blank columns after printing.
void printText(uint8_t modStart, uint8_t modEnd, char *pMsg)
{
	uint8_t   state = 0;
	uint8_t   curLen;
	uint16_t  showLen;
	uint8_t   cBuf[8];
	int16_t   col = ((modEnd + 1) * COL_SIZE) - 1;

	mx.control(modStart, modEnd, MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);

	do     // finite state machine to print the characters in the space available
	{
		switch(state)
		{
			case 0: // Load the next character from the font table
				// if we reached end of message, reset the message pointer
				if (*pMsg == '\0')
				{
					showLen = col - (modEnd * COL_SIZE);  // padding characters
					state = 2;
					break;
				}

				// retrieve the next character form the font file
				showLen = mx.getChar(*pMsg++, sizeof(cBuf)/sizeof(cBuf[0]), cBuf);
				curLen = 0;
				state++;
				// !! deliberately fall through to next state to start displaying

			case 1: // display the next part of the character
				mx.setColumn(col--, cBuf[curLen++]);

				// done with font character, now display the space between chars
				if (curLen == showLen)
				{
					showLen = CHAR_SPACING;
					state = 2;
				}
				break;

			case 2: // initialize state for displaying empty columns
				curLen = 0;
				state++;
				// fall through

			case 3:	// display inter-character spacing or end of message padding (blank columns)
				mx.setColumn(col--, 0);
				curLen++;
				if (curLen == showLen)
					state = 0;
				break;

			default:
				col = -1;   // this definitely ends the do loop
		}
	} while (col >= (modStart * COL_SIZE));

	mx.control(modStart, modEnd, MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
}


void checkInput()
{
	// buttons
	unsigned long tempTime = millis();
	int buttonStateTemp = digitalRead(buttonPin1);
	if (buttonStateTemp == LOW and buttonStateTemp != button1State)
	{
		if (tempTime - button1Time > buttonIntervall)
		{
			game.playerGetPoint(0);
		}
		button1Time = tempTime;
	} 
	button1State = buttonStateTemp;

	buttonStateTemp = digitalRead(buttonPin2);
	if (buttonStateTemp == LOW and buttonStateTemp != button2State)
	{
		if (tempTime - button2Time > buttonIntervall)
		{
			game.playerGetPoint(1);
		}
		button2Time = tempTime;
	} 
	button2State = buttonStateTemp;

	// IR
	if (irrecv.decode(&results)) {
		switch (results.value)
		{
		case PWR:
			game.resetGame();
			break;

		case FOREWARD:
			game.playerGetPoint(1);
			break;

		case BACK:
			game.playerGetPoint(0);
			break;

		case EQ:
			game.revertGame();
			break;
		
		default:
			break;
		} 
		irrecv.resume(); // Receive the next value
  	}
}





void setup()
{
	pinMode(buttonPin1, INPUT_PULLUP);
	mx.begin();
	irrecv.enableIRIn(); // Start the receiver
	sprintf(message, "%02d : %02d", game.getPoints(0), game.getPoints(1));
	printText(0, MAX_DEVICES-1, message);
}


void loop()
{
	checkInput();
	if (game.isUpdateAvailible())
	{
		sprintf(message, "%02d : %02d", game.getPoints(0), game.getPoints(1));
		printText(0, MAX_DEVICES-1, message);
		game.resetUpdate();
	}
}
