#include <Input.h>

int button1State = HIGH;
unsigned long button1Time = 0;

int button2State = HIGH;
unsigned long button2Time = 0;

IRrecv irrecv(irPin);
decode_results results;

void setupInput()
{	
    pinMode(buttonPin1, INPUT_PULLUP);
	pinMode(buttonPin2, INPUT_PULLUP);
	irrecv.enableIRIn(); // Start the receiver
}

int checkInput()
{
	int retval = NO_INPUT;
	// buttons
	unsigned long tempTime = millis();
	int buttonStateTemp = digitalRead(buttonPin1);
	if (buttonStateTemp == LOW and buttonStateTemp != button1State)
	{
		if (tempTime - button1Time > buttonIntervall)
		{
			retval = POINT_P1;
		}
		button1Time = tempTime;
	} 
	button1State = buttonStateTemp;

	buttonStateTemp = digitalRead(buttonPin2);
	if (buttonStateTemp == LOW and buttonStateTemp != button2State)
	{
		if (tempTime - button2Time > buttonIntervall)
		{
			retval = POINT_P2;
		}
		button2Time = tempTime;
	} 
	button2State = buttonStateTemp;

	// IR
	if (irrecv.decode(&results)) {
		switch (results.value)
		{
		case PWR:
			retval = RESET;
			break;
 
		case FOREWARD:
			retval = POINT_P2;
			break;

		case BACK:
			retval = POINT_P1;
			break;

		case EQ:
			retval = REVERT;
			break;

		case PLAY:
			retval = CHANGEOVER;
			break;
		
		default:
			break;
		} 
		irrecv.resume(); // Receive the next value
  	}
	
	return retval;
}