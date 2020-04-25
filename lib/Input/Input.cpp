#include <Input.h>

int button1State = HIGH;
unsigned long button1Time = 0;

int button2State = HIGH;
unsigned long button2Time = 0;

int button3State = HIGH;
unsigned long button3Time = 0;

IRrecv irrecv(irPin);
decode_results results;

void setupInput()
{	
    pinMode(buttonPin1, INPUT_PULLUP);
	pinMode(buttonPin2, INPUT_PULLUP);
	pinMode(buttonPin3, INPUT_PULLUP);
	irrecv.enableIRIn(); // Start the receiver
}

int checkInput()
{
	controls retval = noInput;
	// buttons
	unsigned long tempTime = millis();
	int buttonStateTemp = digitalRead(buttonPin1);
	if (buttonStateTemp == LOW and buttonStateTemp != button1State)
	{
		if (tempTime - button1Time > buttonIntervall)
		{
			retval = button_1;
		}
		button1Time = tempTime;
	} 
	button1State = buttonStateTemp;

	buttonStateTemp = digitalRead(buttonPin2);
	if (buttonStateTemp == LOW and buttonStateTemp != button2State)
	{
		if (tempTime - button2Time > buttonIntervall)
		{
			retval = button_2;
		}
		button2Time = tempTime;
	} 
	button2State = buttonStateTemp;


	buttonStateTemp = digitalRead(buttonPin3);
	if (buttonStateTemp == LOW and buttonStateTemp != button3State)
	{
		if (tempTime - button3Time > buttonIntervall)
		{
			retval = button_3;
		}
		button3Time = tempTime;
	} 
	button3State = buttonStateTemp;

	// IR
	if (irrecv.decode(&results)) {
		switch (results.value)
		{
		case IR_PWR:
			retval = pwr;
			break;
 
		case IR_FOREWARD:
			retval = foreward;
			break;

		case IR_BACK:
			retval = back;
			break;

		case IR_EQ:
			retval = eq;
			break;

		case IR_PLAY:
			retval = play;
			break;
		
		default:
			break;
		} 
		irrecv.resume(); // Receive the next value
  	}
	
	return retval;
}