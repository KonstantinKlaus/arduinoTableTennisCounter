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
			retval = BUTTON_1;
		}
		button1Time = tempTime;
	} 
	button1State = buttonStateTemp;

	buttonStateTemp = digitalRead(buttonPin2);
	if (buttonStateTemp == LOW and buttonStateTemp != button2State)
	{
		if (tempTime - button2Time > buttonIntervall)
		{
			retval = BUTTON_2;
		}
		button2Time = tempTime;
	} 
	button2State = buttonStateTemp;

	// IR
	if (irrecv.decode(&results)) {
		switch (results.value)
		{
		case IR_PWR:
			retval = PWR;
			break;
 
		case IR_FOREWARD:
			retval = FOREWARD;
			break;

		case IR_BACK:
			retval = BACK;
			break;

		case IR_EQ:
			retval = EQ;
			break;

		case IR_PLAY:
			retval = PLAY;
			break;
		
		default:
			break;
		} 
		irrecv.resume(); // Receive the next value
  	}
	
	return retval;
}