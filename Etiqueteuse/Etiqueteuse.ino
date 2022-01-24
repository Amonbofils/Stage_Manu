// Programmation Etiqueteuse
#include <Arduino.h>
#include <NewPing.h>

#define TRIG_CAPT_ETIQ 4
#define ECHO_CAPT_ETIQ 3
#define CMD_VER_STOP 11 
#define CMD_VER_ETIQ 10 
#define DISTANCE_DETECT 5 
#define DISTANCE_MAX 20 
#define TIME_DELAY 2000
#define TIMER_LABEL 2000

NewPing captEtiq = NewPing(TRIG_CAPT_ETIQ, ECHO_CAPT_ETIQ, DISTANCE_MAX); 

unsigned long detectedBottle = 0; 

bool findBottle = false; 
bool timerLabelStarted = false;

void setup(){
  Serial.begin(9600);
  
  pinMode(CMD_VER_STOP, OUTPUT);
  pinMode(CMD_VER_ETIQ, OUTPUT); 
  digitalWrite(CMD_VER_STOP, HIGH); 
  digitalWrite(CMD_VER_ETIQ, HIGH); 
}
void loop(){ 


  float distance = captEtiq.ping_cm(); 
  if (0<distance && distance < DISTANCE_DETECT && !findBottle){ 
    findBottle = true; 
    digitalWrite(CMD_VER_STOP, LOW); 
    detectedBottle = millis();
    
    timerLabelStarted = true; 
    digitalWrite(CMD_VER_ETIQ, LOW);
    
  }
  else if(findBottle && !timerLabelStarted && (distance == 0 || distance >DISTANCE_DETECT)){ 
    findBottle = false; 
  }
  
  
  if(timerLabelStarted && (millis() - detectedBottle >= TIMER_LABEL)){ 
    digitalWrite(CMD_VER_ETIQ, HIGH);
    timerLabelStarted = false;
    digitalWrite(CMD_VER_STOP, HIGH); 
  } 

}
