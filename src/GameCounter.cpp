#include <Arduino.h>
#include <MD_MAX72xx.h>


// Define the number of devices we have in the chain and the hardware interface
// NOTE: These pin numbers will probably not work with your hardware and may
// need to be adapted
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4

#define CLK_PIN   13  // or SCK
#define DATA_PIN  11  // or MOSI
#define CS_PIN    10  // or SS

// SPI hardware interface
MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
// Arbitrary pins
//MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

// Text parameters
#define CHAR_SPACING  1 // pixels between characters

// Global message buffers shared by Serial and Scrolling functions
#define BUF_SIZE  30
char message[BUF_SIZE];
bool newMessageAvailable = true;

// button
const int buttonPin = 0;
int buttonState = HIGH;
int buttonStateTemp;

// game points
int pointsP1 = 0;
int pointsP2 = 0;

int gamePointsP1 = 0;
int gamePointsP2 = 0;

// function prototypes
void printText(uint8_t modStart, uint8_t modEnd, char *pMsg);
void checkInput();
void playerGetPoint(int playerID);


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
	buttonStateTemp = digitalRead(buttonPin);
	if (buttonStateTemp == LOW and buttonStateTemp != buttonState) 
	{
		playerGetPoint(0);
	} 
	buttonState = buttonStateTemp;
}

void playerGetSetPoint(int playerID)
{
    pointsP1 = 0;
    pointsP2 = 0;
	if (playerID == 0)
	{
		gamePointsP1 = gamePointsP1 + 1;
		newMessageAvailable = true;

	} else if (playerID == 1)
	{
		gamePointsP2 = gamePointsP2 + 1;
		newMessageAvailable = true; 
	}
}

void playerGetPoint(int playerID)
{
	if (playerID == 0)
	{
		pointsP1 = pointsP1 + 1;
		newMessageAvailable = true;

		if (pointsP1 > 10 and (pointsP1 - pointsP2) > 1)
		{
			playerGetSetPoint(0);
		} 
	} else if (playerID == 1)
	{
		pointsP2 = pointsP2 + 1;
		newMessageAvailable = true; 
		if (pointsP2 > 10 and (pointsP2 - pointsP1) > 1)
		{
			playerGetSetPoint(1);
		} 
	}
}

void setup()
{
	pinMode(buttonPin, INPUT_PULLUP);
	mx.begin();
	sprintf(message, "%02d : %02d", pointsP1, pointsP2);
	printText(0, MAX_DEVICES-1, message);
}


void loop()
{
	checkInput();
	if (newMessageAvailable)
	{
		sprintf(message, "%02d : %02d", pointsP1, pointsP2);
		printText(0, MAX_DEVICES-1, message);
		newMessageAvailable = false;
	}
}
