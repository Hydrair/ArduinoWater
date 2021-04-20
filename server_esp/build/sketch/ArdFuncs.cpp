#include "ArdFuncs.h"



void checkTime()
{
    static time_t lastTime = 0;
    static time_t compare=0;
    static bool flag = false;
    if( flag )
    {
        lastTime = millis();//NTP.getTime();
        flag = false;
    }


    compare = millis();// NTP.getTime();
//NTP returns epoch in seconds. so time/3600=hours, 60 is 9 seconds
    if( (compare - lastTime) > 30000 )
    {
        sendMessage("Timer",0);
        flag = true;
    }

}

