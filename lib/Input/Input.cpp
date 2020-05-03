#include <Input.h>

Input::Input(int buttonPin1, int buttonPin2, int buttonPin3, int irPin) : irrecv(irPin)
{
	Input::buttonPin1 = buttonPin1;
	Input::buttonPin2 = buttonPin2;
	Input::buttonPin3 = buttonPin3;
	Input::irPin = irPin;

	irrecv = IRrecv(irPin);
}

void Input::setupInput()
{	
    pinMode(buttonPin1, INPUT_PULLUP);
	pinMode(buttonPin2, INPUT_PULLUP);
	pinMode(buttonPin3, INPUT_PULLUP);
	irrecv.enableIRIn(); // Start the receiver
}

Input::controls Input::checkInput()
{
	controls retval = noInput;

	// buttons

	// button 1
	unsigned long curTime = millis();
	int buttonStateTemp = digitalRead(buttonPin1);
	if (buttonStateTemp == LOW and buttonStateTemp != button1State)
	{
		if (curTime - button1Time > buttonIntervall)
		{
			retval = button_1;
		}
		button1Time = curTime;
	} 
	button1State = buttonStateTemp;

	//button 2
	buttonStateTemp = digitalRead(buttonPin2);
	if (buttonStateTemp == LOW and buttonStateTemp != button2State)
	{
		if (curTime - button2Time > buttonIntervall)
		{
			retval = button_2;
		}
		button2Time = curTime;
	} 
	button2State = buttonStateTemp;

	// button 3
	buttonStateTemp = digitalRead(buttonPin3);
	if (buttonStateTemp == LOW and buttonStateTemp != button3State)
	{
		if (curTime - button3Time > buttonIntervall)
		{
			retval = button_3;
		}
		button3Time = curTime;
	} 
	button3State = buttonStateTemp;

	// hold
	if (buttonStateTemp == LOW)
	{
		if (curTime - button3HoldTime > buttonHoldTime)
		{
			retval = button3Hold;
		}
	} else
	{
		button3HoldTime = curTime;
	}
	

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