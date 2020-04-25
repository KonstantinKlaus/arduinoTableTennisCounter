#ifndef INPUT_H
#define INPUT_H

#include <Arduino.h>
#include <IRremote.h>

// buttons
const int buttonIntervall = 300;

const int buttonPin1 = 0;

const int buttonPin2 = 1;

const int buttonPin3 = 2;


// IR Remote
const int irPin = 5;


// IR Remote Keys
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

enum controls {noInput, button_1, button_2, button_3, pwr, play, foreward, back, eq};

void setupInput();
int checkInput();

#endif