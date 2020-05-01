#ifndef OUTPUT_H
#define OUTPUT_H

#include <MD_MAX72xx.h>

// Define the number of devices we have in the chain and the hardware interface
// NOTE: These pin numbers will probably not work with your hardware and may
// need to be adapted
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4

#define CLK_PIN   9  // or SCK
#define DATA_PIN  8  // or MOSI
#define CS_PIN    7  // or SS



#define CLK_PIN_2   13  // or SCK
#define DATA_PIN_2  12  // or MOSI
#define CS_PIN_2    11 // or SS

enum position {left, right};

enum ledMatrix {display_1, display_2};

// Text parameters
#define CHAR_SPACING  1 // pixels between characters

// Global message buffers shared by Serial and Scrolling functions
#define BUF_SIZE  30

// * * * * * * * * * * *
// functions
// * * * * * * * * * * *

void setupOutput();
void printText(ledMatrix display, char *pMsg);
void printPoints(ledMatrix display, int pointP1, int pointsP2);
void printPlayerPosition(ledMatrix display, position player1Position);
void printSetPoints(ledMatrix display, int setPointsLeftPlayer, int setPointsRightPlayer, position rightOfService);
void arrowAnimation();

#endif