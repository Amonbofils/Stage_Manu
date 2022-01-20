#include <Arduino.h>
#include <NewPing.h>

#define TRIG_PIN 2
#define ECHO_PIN 3
#define CMD_RELAY 10
#define DISTANCE_DETECT 5
#define DISTANCE_MAX 20
#define TIME_DELAY 2000
bool bouteilleTrouvee = false;
NewPing sonar = NewPing(TRIG_PIN, ECHO_PIN,DISTANCE_MAX);

void setup(){
  Serial.begin(9600);
  pinMode(CMD_RELAY, OUTPUT);
  digitalWrite(CMD_RELAY, HIGH);
}


void loop(){
  float distance = sonar.ping_cm();
  if (0<distance && distance < DISTANCE_DETECT && bouteilleTrouvee == false){
    bouteilleTrouvee = true;
    digitalWrite(CMD_RELAY, LOW);
    delay(TIME_DELAY);
    digitalWrite(CMD_RELAY, HIGH);
  }
  else if(bouteilleTrouvee== true && (distance == 0 || distance >DISTANCE_DETECT)){
    bouteilleTrouvee = false;
    Serial.println("bouteille trouvée");
  }
}