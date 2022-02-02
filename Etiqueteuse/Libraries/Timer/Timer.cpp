#include "Timer.h"
#include "Arduino.h"

Timer::Timer(int period){
    _timer_start = 0;
    _start = false;
    _done = false;
    _running = false;
    _period = period;
}

void Timer::setPeriod(int period){
    if(!_running)
        _period = period;
}

void Timer::start(){
    if(!_running){
        _start = true;
        _running = true;
        _done = false;
        _timer_start = millis();
    }
}

void Timer::stop(){
    _start = false;
    _running = false;
    _done = false;
    _timer_start = 0;
}

void Timer::reset(){
    stop();
    start();
}

bool Timer::isActive(){
    return _running;
}

bool Timer::isDone(){
    if(_period <= millis()-_timer_start){
        _start = false;
        _running = false;
        _done = true;
        _timer_start = 0;
    }
    return _done;
}

unsigned long Timer::remainTimer(){
    if (!isDone()){
        return (_period-(millis()-_timer_start));
    } else {
        return 0;
    }
} 