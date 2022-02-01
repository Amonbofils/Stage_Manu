#include "classTimer.h"
#include <Arduino.h>

#define TIMER_MAX;

Timer::Timer()
{
    Serial.begin(9600);
    unsigned long time_start;
    time_start = millis();
}

void Timer::start(){
    
    time_start = 0;
    bool isActive=1;

}

void Timer::stop(){
    if(millis()-time_start >= TIME_MAX){
        timer_start = 0;
        bool isActive=0;}
    else if();
}

void Timer::isActive(){

    digitalread(isActive);
    Serial.println("TimerActf");
}

void Timer::setPeriod(){
    if (time_start
}
void Timer::reset(){

}