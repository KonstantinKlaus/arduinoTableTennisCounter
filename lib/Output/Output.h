#ifndef OUTPUT_H
#define OUTPUT_H
#include <MD_MAX72xx.h>


class Output
{

public:

    enum position {left, right};

    enum ledMatrix {display_1, display_2};

    // functions
    Output(int clkPin, int dataPin, int csPin, int clkPinM2, int dataPinM2, int csPinM2);
    void setupOutput();
    void printText(ledMatrix display, char *pMsg);
    void printPoints(ledMatrix display, int pointP1, int pointsP2);
    void printPlayerPosition(ledMatrix display, position player1Position);
    void printSetPoints(ledMatrix display, int setPointsLeftPlayer, int setPointsRightPlayer, position rightOfService);
    void arrowAnimation();

private:
    // variables 
    // control instances for led matrices
    MD_MAX72XX mxLedMatrix_1;
    MD_MAX72XX mxLedMatrix_2;

    // functions
    void printText(MD_MAX72XX & mx, uint8_t modStart, uint8_t modEnd, char *pMsg);
};

#endif