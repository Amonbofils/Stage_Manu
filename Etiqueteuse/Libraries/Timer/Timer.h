#ifndef Timer_h
#define Timer_h

#include "Arduino.h"

class Timer
{
    public:
        Timer(int period);
        void setPeriod(int period); // permet de changer la période
        void start(); // permet de démarrer le Timer
        void stop(); // permet de stopper le Timer
        void reset(); // remise à zéro
        bool isActive(); // permet de donner l'état du Timer
        bool isDone();
        unsigned long remainTimer();
    private:
        bool _done;
        bool _start;
        bool _running;
        int _period;
        unsigned long _timer_start;
        
};
#endif