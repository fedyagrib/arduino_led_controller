#ifndef NTP_CLIENT_HPP_
#define NTP_CLIENT_HPP_

#include <NTPClient.h>
#include <WiFiUdp.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP,"0.pool.ntp.org");

int alarmHours = 7;
int alarmMinutes = 0;
bool alarmSwitch = false;

byte timer=0;

void timeInit(int timeZone){
    timeClient.setTimeOffset(timeZone * 3600);
    timeClient.begin();
}

void setAlarmHours(int hours){
    alarmHours = hours;
    alarmSwitch=true;
}

void setAlarmMinutes(int minutes){
    alarmMinutes = minutes;
    alarmSwitch=true;
}

void setAlarm(int value){
    if(value)
        alarmSwitch = true;
    else
        alarmSwitch = false;
}

int getAlarm(){
    return alarmHours * 24 + alarmMinutes;
}
int getTime(){
    return timeClient.getHours() * 24 + timeClient.getMinutes();
}

int isAlarm(byte interval){

    if(timer == 255){
        timer = 0;
        if(alarmSwitch){
            timeClient.update();
            int alarmMin=getAlarm() - getTime();
            if(abs(alarmMin)<=interval)
                return abs(alarmMin); 
            else if(alarmMin == -interval)
                alarmSwitch = false;
        }
    }
        timer++;
        return -1;
}




#endif // NTP_CLIENT_HPP_