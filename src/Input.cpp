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

void checkInput(Game & game)
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