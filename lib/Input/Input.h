#ifndef INPUT_H
#define INPUT_H

#include <Arduino.h>
#include <IRremote.h>



// IR Remote Keys (Codes for Elegoo IR remote control, change for different remote controls)
#define IR_PWR 		    0xFFA25D
#define IR_VOL_UP       0xFF629D
#define IR_FUNC		    0xFFE21D
#define IR_BACK    	    0xFF22DD
#define IR_PLAY    	    0xFF02FD
#define IR_FOREWARD     0xFFC23D
#define IR_DOWN    	    0xFFE01F
#define IR_VOL_DOWN     0xFFA857
#define IR_UP           0xFF906F
#define IR_EQ           0xFF9867
#define IR_ST           0xFFB04F
#define IR_NUM_1        0xFF30CF
#define IR_NUM_0        0xFD30CF
#define IR_NUM_2        0xFF18E7
#define IR_NUM_3        0xFF7A85
#define IR_NUM_4        0xFF10EF
#define IR_NUM_5        0xFF38C7
#define IR_NUM_6        0xFF5AA5
#define IR_NUM_7        0xFF42BD
#define IR_NUM_8        0xFF4AB5
#define IR_NUM_9        0xFF52AD

class Input
{

public:
    // enum for possible inputs
    enum controls {noInput, button_1, button_2, button_3, button3Hold, pwr, play, foreward, back, eq};

    // buttons
    const unsigned buttonIntervall = 200;
    const unsigned buttonHoldTime = 1200;

    // functions
    Input(int buttonPin1, int buttonPin2, int buttonPin3, int irPin);
    
    void setupInput();
    controls checkInput();

private:

    // buttons
    int buttonPin1;
    int buttonPin2;
    int buttonPin3;

    int button1State = HIGH;
    unsigned long button1Time = 0;

    int button2State = HIGH;
    unsigned long button2Time = 0;

    int button3State = HIGH;
    unsigned long button3Time = 0;
    unsigned long button3HoldTime = 0;


    // IR Remote
    int irPin;

    decode_results results;
    IRrecv irrecv;

};




#endif