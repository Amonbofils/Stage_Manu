#ifndef classTimer_h
#define classTimer_h

#include <Arduino.h>
#define TIMER_MAX;
class Timer
{
    public:
        void setPeriod(); // permet de changer la période
    private:
        int delay = 1000;
        void start(); // permet de démarrer le Timer
        void stop(); // permet de stopper le Timer
        void reset(); // remise à zéro
        bool isActive(); // permet de donner l'état du Timer
};
#endif

