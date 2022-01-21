// Programme de détection de bouteille avec actionneur de vérin
//
//
#include <Arduino.h>// Introduction de la bibliothèque Arduino
#include <NewPing.h>// Introduction de la bibiolthèque NewPin

#define TRIG_PIN 2// Capteur HC_SR04T Détecteur de bouteille
#define ECHO_PIN 3
#define CMD_RELAY1 11 // Relais vérin Stoppeur
#define CMD_RELAY2 10 // Relais avec vérin Pousseur
#define DISTANCE_DETECT 5 // Détection de distance
#define DISTANCE_MAX 20 // Distance Maximale
#define TIME_DELAY 2000 // Délais d'attente

NewPing sonar = NewPing(TRIG_PIN, ECHO_PIN,DISTANCE_MAX); // Analyse capteur

unsigned long eventInterval = 2000; // Definir l'interval de l'évenement
unsigned long eventDetected = 0; // Créer une mise à jour
unsigned long currentTime; //Sortie de millis

bool bouteilleTrouvee = false; // Résultat capteur
bool timerStarted = false; // Impression état Timer

int detection; // Détection capteur d'encombrement
int led = 5; // Led capteur d'encombrement
int capteur = 4; // Capteur d'encombrement

void setup(){
  Serial.begin(9600);
  pinMode(led, OUTPUT); // Sortie led 
  pinMode(capteur, INPUT); // Entré capteur
  pinMode(CMD_RELAY1, OUTPUT); // Sortie vérin Stoppeur 
  pinMode(CMD_RELAY2, OUTPUT); // Sortie vérin Pousseur
  digitalWrite(CMD_RELAY1, HIGH); // Démarrage de la boucle vérin stoppeur rentré
  digitalWrite(CMD_RELAY2, HIGH); // Démarrage de la boucle vérin Pousseur rentré
}
void loop(){ // Démarrage de la boucle
  //detection = digitalRead(capteur);
  //if(detection == 0){
    //digitalWrite(led, HIGH);
    //digitalWrite(CMD_RELAY1, HIGH);
//}

  float distance = sonar.ping_cm(); // Distance en décimal, donnée par NewPing
  if (0<distance && distance < DISTANCE_DETECT && !bouteilleTrouvee){ //  Si 0 < distance > DISTANCE_DETECT et pas de bouteille trouvée
    bouteilleTrouvee = true; // Signaler la bouteille trouvée
    digitalWrite(CMD_RELAY1, LOW); // Action du vérin Stoppeur
    eventDetected = millis(); // EventDetect est égal à la fonction millis
    // Serial.println("trouvee"); 
    timerStarted = true; // Timer commencé
    digitalWrite(CMD_RELAY2, LOW); // Actionnement de vérin 
    //delay(TIME_DELAY); // Vérin actionné pendant TIME_DELAY
  }
  else if(bouteilleTrouvee && !timerStarted && (distance == 0 || distance >DISTANCE_DETECT)){ // Si une bouteille est trouvée,et que la distance est égale à zéro ou que la distance est supérieur à DISTANC_DETECT 
    bouteilleTrouvee = false; // Alors on marque bouteille pas trouvée 
    Serial.println("bouteille partie"); // impression sur monitor 
  }
  
  currentTime = millis(); // CurrentTime est égal à millis
  if(timerStarted && (currentTime - eventDetected >= eventInterval)){ // Comparaison temps passé et interval
    digitalWrite(CMD_RELAY2, HIGH); // Rétractation du vérin Pousseur
    timerStarted = false; //  Timer terminé
    // Serial.print("timer");
    digitalWrite(CMD_RELAY1, HIGH); // Rétractation du vérin Stoppeur
  } 

  detection = digitalRead(capteur); // Lecture du capteur d'encombrement
  Serial.println(detection);
  if(detection == 0){ // Pas d'encombrement sur la ligne
        digitalWrite(CMD_RELAY1, HIGH); // Vérin stoppeur rentré
        digitalWrite(led, HIGH); // Led encombrement éteinte
       
   }
  else if(detection == 1) { // Encombrement sur la ligne
      digitalWrite(led, LOW); // Led encombrement allumée
      digitalWrite(CMD_RELAY1, LOW); // vérin stoppeur sorti
    
     }
    
}
