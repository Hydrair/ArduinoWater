#pragma once
#include <Arduino.h>
#include <ESP8266WebServer.h>
#include "serialComm.h"

extern ESP8266WebServer server;
extern String chart;
extern String valuesP1;
extern String valuesP2;
extern String valuesP3;
extern int plant1stat;
extern int plant2stat;
extern int plant3stat;
extern bool waterempty;

void createRoot();

void handleRoot();

void handleNotFound();

