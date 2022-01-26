// Programmation Etiqueteuse
#include <Arduino.h>
#include <NewPing.h>
#include <Bounce2.h>
#include "./Config/GlobalVars.h"
#include "./Config/Setup.h"
#include "./Graph7/Graph1.h"
#include "./Graph7/Graph2.h"
#include "./Graph7/Graph3.h"
#include "./Graph7/Graph4.h"
/**
 * @Graph1 => Graph du vérin d'entrée (0-3)
 * @Graph2 => Graph du vérin étiquette
 * @Graph3 => Graph étiquetteuse
 * @Graph4 => Graph Encombrement
 * @Graph5 => Graph Débuggage
 */

/**
 * @brief setup est exécuté lors du premier tour de cycle et ne sera pas jamais appellé.
 * @arg : none
 * @return : none
 */
void setup(){
  SetupInputOutput();
}

void loop(){ 
  Graph1();
  Graph2();
  Graph3();
  Graph4();
  Graph5();
}
/**
 * @brief Graph de Debbuggaga : Graph séquentiel de Débuggage
 * @arg none
 * @return none
 * 
 */
void Graph5(){
  /*  Declare locales */
  static unsigned long debbuggage;
  unsigned long currentTime;
  bool bugButton;
  debugButton.update();
  
  /* Graph */
  if (Graph5Step == 0) {
    /* Actions */
    bugButton = debugButton.read();
  if(bugButton){
    Serial.begin(9600);
      }
    /* Transitions */
    Graph5Step = 1;
  } 
  else  if (Graph5Step == 1) {
    /* Actions */
    debbuggage = millis();
    /* Transitions */
    Graph5Step = 2;
  } 
  else  if (Graph5Step == 2) {
    /* Actions */
    currentTime = millis();
    if (currentTime - debbuggage >= DEBUG_TIMER) {
      Serial.println( "********************");
      Serial.print("Graph 1 : ");
      Serial.println(Graph1Step);
      Serial.print("Graph 2 : ");
      Serial.println(Graph2Step);
      // Serial.println(Graph3Step);
      Serial.print("Graph 4 : ");
      Serial.println(Graph4Step);
      Serial.end();
    }
    /* Transitions */
    if (currentTime - debbuggage >= DEBUG_TIMER) {
      Graph5Step = 0;
    }
  } else {
    Graph5Step = 0;
  } 
}