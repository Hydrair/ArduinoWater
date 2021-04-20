#include "serialComm.h"

char receivedChars[numChars];
char tempChars[numChars];
char messageFromPC[numChars] = {0};
int integerFromPC = 0;
int LED=0;
boolean newSerialData = false;
bool waterempty;

void recvWithStartEndMarkers()
{
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;
    while (Serial.available() > 0 && newSerialData == false) {
        rc = Serial.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newSerialData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}


void parseData()
{

    char * strtokIndx;

    strtokIndx = strtok(tempChars,",");
    strcpy(messageFromPC, strtokIndx);

    strtokIndx = strtok(NULL, ",");
    integerFromPC = atoi(strtokIndx);
}


// void showParsedData()
// {
//     Serial.print("Message ");
//     Serial.println(messageFromPC);
//     Serial.print("Integer ");
//     Serial.println(integerFromPC);
// }


void serialHandler()
{
    static int countP1=0;
    static int countP2=0;
    static int countP3=0;
	if( !strcmp(messageFromPC,"MeasurePlant1"))//name
    {
        if( countP1 >= 10)
        {
            valuesP1 = clearFirstEntry(valuesP1);
        }
        valuesP1 += "['";
        valuesP1 += NTP.getTimeStr();
        valuesP1 += "', ";
        valuesP1 += integerFromPC;
        valuesP1 += "],\n";
        countP1++;
        Serial.println(valuesP1);
    }
    if( !strcmp(messageFromPC,"MeasurePlant2"))
    {
        if( countP2 >= 10)
        {
            valuesP2 = clearFirstEntry(valuesP2);
        }
        valuesP2 += "['";
        valuesP2 += NTP.getTimeStr();
        valuesP2 += "', ";
        valuesP2 += integerFromPC;
        valuesP2 += "],\n";
        countP2++;
    }
    if( !strcmp(messageFromPC,"MeasurePlant3"))
    {
        if( countP3 >= 10)
        {
            valuesP3 = clearFirstEntry(valuesP3);
        }
        valuesP3 += "['";
        valuesP3 += NTP.getTimeStr();
        valuesP3 += "', ";
        valuesP3 += integerFromPC;
        valuesP3 += "],\n";
        countP3++;
    }
    if( !strcmp(messageFromPC,"Empty"))
    {
        waterempty = integerFromPC;
    }
}

String clearFirstEntry(String str)
{
    for (int i = 0; i < str.length(); i++)
    {
        if (str.substring(i, i+2) == "],")
        {
            str.substring(0, i);
            str = str.substring(i+2);
            break;
        }
    }
    return str;
}

void sendMessage(String param, int num)
{
    digitalWrite(2, HIGH);
    delay(1000);
    digitalWrite(2, LOW);

    String message = "<" + param + "," + num + ">";
    Serial.println(message);
}
// <Measure1,1>
// <Measure1,3>
// <Measure1,15>
// <Measure1,3>
// <Measure1,5>
// <Measure1,3>
// <Measure1,5>
// <Measure1,5>
// <Measure1,10>
// <Measure1,13>
// <Measure1,15>
// <Measure2,5>
// <Measure2,3>
// <Measure2,5>
// <Measure1,11>
// <Measure2,1>
// <Measure3,10>
// <Measure3,13>
// <Measure3,15>
// <Measure3,11>