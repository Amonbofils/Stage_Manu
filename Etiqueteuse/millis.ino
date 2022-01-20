#include <Arduino.h>
#include<NewPing.h>

const unsigned long eventInterval = 2000;// Definir l'interval de l'évenement
unsigned long previousTime = 0; // Créer une variable pour mettre à jour
int currentTime;// Sortie de millis

void loop(){
    unsigned long currentTimes = millis();
 if( currentTime - previousTime >= eventInterval){ // si le temps écoulé est superrieur ou égal à
      //Serial.println("retour");
      previousTime = currentTime;
      }
}