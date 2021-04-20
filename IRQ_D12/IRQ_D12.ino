#include "PinChangeInterrupt.h"
#include <avr/sleep.h>
#include <avr/power.h>
#include "serialComm.h"
// #include "sleepInt.h"

#define pinBlink 1
#define LED 12
#define LEDSLEEP 7

int seconds=0;



void blinkLed(void)
{
	digitalWrite(LED, !digitalRead(LED));
	detachPCINT(digitalPinToPCINT(pinBlink));
}

void enterSleep(void)
{
	attachPCINT(digitalPinToPCINT(pinBlink), blinkLed, CHANGE);
	delay(100);

	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	sleep_enable();
	sleep_mode();
	// UNO is sleeping
	sleep_disable();
	Serial.println("Woke UP.");
	digitalWrite(LEDSLEEP,LOW);
	waitForInput();
}

void waitForInput(void)
{
	int rec = 1;
	Serial.println("Waiting for Input.");
	while( rec )
	{
		recvWithStartEndMarkers();
		if (newSerialData == true) {
			strcpy(tempChars, receivedChars);
			parseData();
			#ifdef DEBUG
			showParsedData();
			#endif
			serialHandler();
			newSerialData = false;
			rec = 0;
		}
	}
}

void setup()
{
	pinMode(pinBlink, INPUT_PULLUP);
	pinMode(LED, OUTPUT);
	pinMode(LEDSLEEP,OUTPUT);
	pinMode(4,OUTPUT);

	Serial.begin(9600);
	Serial.println("Enter data in this style <HelloWorld, 12>  ");
	Serial.println("Initialisation complete.");

}


void loop()
{
	delay(1000);
	seconds++;

	Serial.print("Awake for ");
	Serial.print(seconds, DEC);
	Serial.println(" second");

	if(seconds == 3)
	{
		Serial.println("Entering sleep");
		delay(200);
		seconds=0;
		digitalWrite(LEDSLEEP,HIGH);
		enterSleep();
	}
}



