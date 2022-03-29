#pragma once
#include "Arduino.h"
#include <TimeLib.h>
#include <NtpClientLib.h>

const byte numChars = 32;
extern char receivedChars[numChars];
extern char tempChars[numChars];
extern char messageFromPC[numChars] ;
extern int integerFromPC;
extern int LED;
extern boolean newSerialData;
extern String valuesP1;
extern String valuesP2;
extern String valuesP3;
extern bool waterempty;

void recvWithStartEndMarkers();

void parseData();

// void showParsedData();

void serialHandler();

String clearFirstEntry(String);

void sendMessage(String, int);