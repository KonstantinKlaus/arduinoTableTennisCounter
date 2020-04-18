#ifndef OUTPUT_H
#define OUTPUT_H

#include <MD_MAX72xx.h>

// Define the number of devices we have in the chain and the hardware interface
// NOTE: These pin numbers will probably not work with your hardware and may
// need to be adapted
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4

#define CLK_PIN   13  // or SCK
#define DATA_PIN  12  // or MOSI
#define CS_PIN    11  // or SS



// Text parameters
#define CHAR_SPACING  1 // pixels between characters

// Global message buffers shared by Serial and Scrolling functions
#define BUF_SIZE  30


void setupOutput();
void printText(uint8_t modStart, uint8_t modEnd, char *pMsg);

#endif