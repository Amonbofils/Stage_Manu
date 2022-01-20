// Programme de détection de bouteille avec actionneur de vérin
#include <Arduino.h>// Introduction de la bibliothèque Arduino
#include <NewPing.h>// Introduction de la bibiolthèque NewPin

#define TRIG_PIN 2// Capteur HC_SR04T 
#define ECHO_PIN 3
#define CMD_RELAY 10// Relais avec vérin 12V
#define DISTANCE_DETECT 5 // Détection de distance
#define DISTANCE_MAX 20 // Distance Maximale
#define TIME_DELAY 2000 // Délais d'attente
bool bouteilleTrouvee = false; // Résultat capteur
NewPing sonar = NewPing(TRIG_PIN, ECHO_PIN,DISTANCE_MAX); // Analyse capteur
const unsigned long eventInterval = 2000; // Definir l'interval de l'évenement
unsigned long previousTime = 0; // Créer une mise à jour
int currentTime; //Sortie de millis

void setup(){
  Serial.begin(9600);
  pinMode(CMD_RELAY, OUTPUT); // Action sur le vérin
  digitalWrite(CMD_RELAY, HIGH); // démarrage de la boucle vérin rentré

}
void loop(){ // Démarrage de la boucle
  float distance = sonar.ping_cm(); // Distance en décimal, donnée par NewPing
  if (0<distance && distance < DISTANCE_DETECT && bouteilleTrouvee == false){ //  Si 0 < distance > DISTANCE_DETECT et pas de bouteille trouvée
    bouteilleTrouvee = true; // Signaler la bouteille trouvée
    digitalWrite(CMD_RELAY, LOW); // Actionnement de vérin 
    delay(TIME_DELAY); // Vérin actionné pendant TIME_DELAY
    digitalWrite(CMD_RELAY, HIGH); // Rétractation du vérin
  }
  else if(bouteilleTrouvee== true && (distance == 0 || distance >DISTANCE_DETECT)){// Si une bouteille est trouvée,et que la distance est égale à zéro ou que la distance est supérieur à DISTANC_DETECT 
    bouteilleTrouvee = false;// Alors on marque bouteille pas trouvée 
    Serial.println("bouteille trouvée");// impression sur monitor 
  unsigned long currentTimes = millis();
  if( currentTime - previousTime >= eventInterval){// Comparaison temps passé et interval
      //Serial.println("retour");
      previousTime = currentTime;// Remise à jour
      }
  }
}