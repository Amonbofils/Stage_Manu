// Programmation Etiqueteuse
#include <Arduino.h>
#include <NewPing.h>

#define TRIG_CAPTETIQ 2
#define ECHO_CAPTETIQ 3
#define CMD_VERSTOP 11 
#define CMD_VERETIQ 10 
#define DISTANCE_DETECT 5 
#define DISTANCE_MAX 20 
#define TIME_DELAY 2000

NewPing etiquette = NewPing(TRIG_CAPTETIQ, ECHO_CAPTETIQ, DISTANCE_MAX); 

unsigned long eventInterval = 2000; 
unsigned long eventDetected = 0; 
unsigned long currentTime; 

bool bouteilleTrouvee = false; 
bool timerStarted = false;

void setup(){
  Serial.begin(9600);
  
  pinMode(CMD_VERSTOP, OUTPUT);
  pinMode(CMD_VERETIQ, OUTPUT); 
  digitalWrite(CMD_VERSTOP, HIGH); 
  digitalWrite(CMD_VERETIQ, HIGH); 
}
void loop(){ 


  float distance = etiquette.ping_cm(); 
  if (0<distance && distance < DISTANCE_DETECT && !bouteilleTrouvee){ 
    bouteilleTrouvee = true; 
    digitalWrite(CMD_VERSTOP, LOW); 
    eventDetected = millis();
    
    timerStarted = true; 
    digitalWrite(CMD_VERETIQ, LOW);
    
  }
  else if(bouteilleTrouvee && !timerStarted && (distance == 0 || distance >DISTANCE_DETECT)){ 
    bouteilleTrouvee = false; 
  }
  
  currentTime = millis();
  if(timerStarted && (currentTime - eventDetected >= eventInterval)){ 
    digitalWrite(CMD_VERETIQ, HIGH);
    timerStarted = false;
    digitalWrite(CMD_VERSTOP, HIGH); 
  } 

}
