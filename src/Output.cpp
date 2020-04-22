#include <Output.h>

// SPI hardware interface
//MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
// Arbitrary pins
MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);
MD_MAX72XX mx2 = MD_MAX72XX(HARDWARE_TYPE, DATA_PIN_2, CLK_PIN_2, CS_PIN_2, MAX_DEVICES);

void printText(MD_MAX72XX & mx, uint8_t modStart, uint8_t modEnd, char *pMsg);

void setupOutput()
{
    mx.begin();
	mx2.begin();
}

// Print the text string to the LED matrix modules specified.
// Message area is padded with blank columns after printing.
void printTextDisplay1(char *pMsg)
{
	printText(mx, 0, MAX_DEVICES - 1, pMsg);
}


void printTextDisplay2(char *pMsg)
{
	printText(mx2, 0, MAX_DEVICES - 1, pMsg);
}



void printText(MD_MAX72XX & mx, uint8_t modStart, uint8_t modEnd, char *pMsg)
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


void printPointsDisplay1(int pointsLeftPlayer, int pointsRightPlayer)
{

	uint16_t  showLen;
	uint8_t   cBuf[8];
	char character[2];

	mx.control(0, 3, MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);

	// reset all columns
	for (int i = 0; i < 32; ++i)
  	{
    	mx.setColumn(i, 0);
  	}
	
	// colon
	mx.setColumn(15, 108);
	mx.setColumn(16, 108);

	// for generating numbers
	int temp;
	int positions[] = { 30, 24, 11, 5 };

	for (int j = 0; j < 4; ++j)
  	{
		switch (j)
		{
		case 0:
			temp = pointsLeftPlayer / 10;
			break;
		
		case 1:
			temp = pointsLeftPlayer;
			break;

		case 2:
			temp = pointsRightPlayer / 10;
			break;
		
		default:
			temp = pointsRightPlayer;
			break;		
		}

		sprintf(character, "%01d", temp);
		showLen = mx.getChar(*character, sizeof(cBuf)/sizeof(cBuf[0]), cBuf);
		for (uint8_t i = 0; i < showLen; ++i)
		{
			mx.setColumn(positions[j] - i, cBuf[i]);
		} 
  	} 

	mx.control(0, 3, MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
}


void printSetPointsDisplay1(int setPointsLeftPlayer, int setPointsRightPlayer, position rightOfService)
{

	uint16_t  showLen;
	uint8_t   cBuf[8];
	char character[2];

	mx.control(0, 3, MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);

	// reset all columns
	for (int i = 0; i < 32; ++i)
  	{
    	mx.setColumn(i, 0);
  	}
	
	// colon
	mx.setColumn(15, 108);
	mx.setColumn(16, 108);

	// for generating numbers
	int temp;
	int positions[] = { 24, 11 };

	for (int j = 0; j < 2; ++j)
  	{
		switch (j)
		{
		case 0:
			temp = setPointsLeftPlayer / 10;
			break;
		
		default:
			temp = setPointsRightPlayer;
			break;		
		}

		sprintf(character, "%01d", temp);
		showLen = mx.getChar(*character, sizeof(cBuf)/sizeof(cBuf[0]), cBuf);
		for (uint8_t i = 0; i < showLen; ++i)
		{
			mx.setColumn(positions[j] - i, cBuf[i]);
		} 
  	} 

	if (rightOfService = left)
	{
		
	}

	mx.control(0, 3, MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
}