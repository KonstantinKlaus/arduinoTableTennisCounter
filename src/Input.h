#ifndef INPUT_H
#define INPUT_H

#include <Arduino.h>
#include <IRremote.h>

// buttons
const int buttonIntervall = 300;

const int buttonPin1 = 0;

const int buttonPin2 = 1;


// IR Remote
const int irPin = 5;


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

// IR Remote Keys
#define NO_INPUT 	0
#define POINT_P1    1
#define POINT_P2    2
#define REVERT      3
#define RESET       4
#define CHANGEOVER  5


void setupInput();
int checkInput();

#endif