#include <Arduino.h>
#include <NewPing.h>

#define trigPin 2
#define echoPin 3
#define cmdRelay 10
#define DISTANCE_DETECT 5
#define DISTANCE_MAX 20
#define TIME_DELAY 2000
bool bouteilleTrouvee = false;
NewPing sonar = NewPing(trigPin, echoPin,DISTANCE_MAX);

void setup(){
  Serial.begin(9600);
  pinMode(cmdRelay, OUTPUT);
  digitalWrite(cmdRelay, HIGH);
}


void loop(){
  float distance = sonar.ping_cm();
  if (0<distance && distance < DISTANCE_DETECT && bouteilleTrouvee == false ){
    bouteilleTrouvee = true;
    digitalWrite(cmdRelay, LOW);
    delay(TIME_DELAY);
    digitalWrite(cmdRelay, HIGH);
  }
  else if(bouteilleTrouvee== true && (distance == 0 || distance >DISTANCE_DETECT)){
    bouteilleTrouvee = false;
    Serial.println("bouteille trouvée");
  }
}