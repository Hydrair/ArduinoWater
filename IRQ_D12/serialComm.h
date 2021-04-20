#pragma once
#include "Arduino.h"

const byte numChars = 32;
extern char receivedChars[numChars];
extern char tempChars[numChars];
extern char messageFromPC[numChars] ;
extern int integerFromPC;
extern int LED;
extern boolean newSerialData;

void recvWithStartEndMarkers();

void parseData();

#ifdef DEBUG
void showParsedData();
#endif

void serialHandler();