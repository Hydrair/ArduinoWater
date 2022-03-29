#include "serialComm.h"

char receivedChars[numChars];
char tempChars[numChars];
char messageFromPC[numChars] = {0};
int integerFromPC = 0;
int LED=0;
boolean newSerialData = false;


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

#ifdef DEBUG
void showParsedData()
{
    Serial.print("Message ");
    Serial.println(messageFromPC);
    Serial.print("Integer ");
    Serial.println(integerFromPC);
}
#endif

void serialHandler()
{
	// if( !strcmp(messageFromPC,"Plant1"))
    // {
    //     if( integerFromPC == 1 )
    //     {
    //         pf1.giessen();
    //     }
    //     else
    //     {
    //         pf1.setDauer(integerFromPC);
    //     }
    // }
    // if( !strcmp(messageFromPC,"Plant2"))
    // {
    //     if( integerFromPC == 1 )
    //     {
    //         pf1.giessen();
    //     }
    //     else
    //     {
    //         pf1.setDauer(integerFromPC);
    //     }
    // }
    // if( !strcmp(messageFromPC,"Plant3"))
    // {
    //     if( integerFromPC == 1 )
    //     {
    //         pf1.giessen();
    //     }
    //     else
    //     {
    //         pf1.setDauer(integerFromPC);
    //     }
    // }
}
// <Plant1,1>
// <Plant1,3>
// <Plant1,15>
// <Plant1,1>
// <Plant2,5>
// <Plant2,3>
// <Plant2,5>
// <Plant2,1>
// <Plant3,10>
// <Plant3,13>
// <Plant3,15>
// <Plant3,11>