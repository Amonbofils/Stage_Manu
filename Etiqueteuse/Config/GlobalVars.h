#include <Bounce2.h>
#define CMD_VER_STOP 11 
#define CMD_VER_LABEL 10 
#define DISTANCE_DETECT 5 
#define DISTANCE_MAX 20 
#define TIME_DELAY 2000
#define LABEL_TIMER 2000
#define DEBUG_TIMER 1000
#define SECURITY_TIMER 3000 
#define CAPT_VER_STOP1 2
#define CAPT_VER_STOP2 7
#define CAPT_LABEL 3
#define CAPT_END 6
#define DEBUG_BUTTON 8

int Graph1Step = 0, Graph2Step = 0, Graph3step = 0, Graph4Step = 0, Graph5Step = 0;

Bounce captBottleStop1 = Bounce();
Bounce captBottleStop2 = Bounce();
Bounce captBottleLabel = Bounce();
Bounce captBottleEnd = Bounce();
Bounce debugButton = Bounce();