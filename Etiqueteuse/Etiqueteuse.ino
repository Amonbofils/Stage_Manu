// Programmation Etiqueteuse
#include <Arduino.h>
#include <NewPing.h>
#include <Bounce2.h>

#define TRIG_CAPT_ETIQ 4
#define ECHO_CAPT_ETIQ 3
#define CMD_VER_STOP 11 
#define CMD_VER_ETIQ 10 
#define DISTANCE_DETECT 5 
#define DISTANCE_MAX 20 
#define TIME_DELAY 2000
#define TIMER_LABEL 2000
#define CAPT_VER_STOP 2
//#define CAPT_VER 12

NewPing captEtiq = NewPing(TRIG_CAPT_ETIQ, ECHO_CAPT_ETIQ, DISTANCE_MAX); 
Bounce captBottlStop = Bounce();
//Bounce captBottlencomb = Bounce();
unsigned long detectedBottle = 0; 

bool findBottleStop = false;
bool findBottleEtiq = false; 
bool timerLabelStarted = false;
//bool passBottleEtiq = false;
//bool passBottleStart = false;

void setup(){

  Serial.begin(9600);

  //passBottleEtiq = true;
  //passBottleStart = false;
  pinMode(CMD_VER_STOP, OUTPUT);
  pinMode(CMD_VER_ETIQ, OUTPUT); 
  digitalWrite(CMD_VER_STOP, LOW); 
  digitalWrite(CMD_VER_ETIQ, HIGH); 

  captBottlStop.attach(CAPT_VER_STOP,  INPUT_PULLUP );
  captBottlStop.interval(50); 
  //captBottlStop.attach(CAPT_VER_,  INPUT_PULLUP );
 // captBottlStop.interval(50); 
}
void loop(){ 

  captBottlStop.update();
  findBottleStop = captBottlStop.read();

  if (findBottleStop) {
    digitalWrite(CMD_VER_STOP, LOW);
    //passBottleEtiq = 0;
    //passBottleStart = 1;
    Serial.println("stop1");
  }
  else if(!findBottleStop){
    digitalWrite(CMD_VER_STOP,HIGH);

    Serial.println("passer1");
  }

  float distance = captEtiq.ping_cm(); 

  if (0<distance && distance < DISTANCE_DETECT && !findBottleEtiq){ 
    findBottleEtiq = true;
    //passBottleEtiq = true;
    //digitalWrite(CMD_VER_STOP, LOW); 
    detectedBottle = millis();
    timerLabelStarted = true; 
    digitalWrite(CMD_VER_ETIQ, LOW);
    
  }
  else if(findBottleEtiq && !timerLabelStarted && (distance == 0 || distance >DISTANCE_DETECT)){ 
    findBottleEtiq = false; 
  }
  
  if(timerLabelStarted && (millis() - detectedBottle >= TIMER_LABEL)){ 
    digitalWrite(CMD_VER_ETIQ, HIGH);
    timerLabelStarted = false;
    //digitalWrite(CMD_VER_STOP, HIGH); 
  } 
   captBottlStop.update();
  findBottleStop = captBottlStop.read();

  /*if (findBottleStop) {
    digitalWrite(CAPT_VER_STOP, LOW);
    Serial.println("stop");
  }
  else if(!findBottleStop){
    digitalWrite(CAPT_VER_STOP,HIGH);
    Serial.println("passer");*/
  
  

}
