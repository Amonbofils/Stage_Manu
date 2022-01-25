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

NewPing captEtiq = NewPing(TRIG_CAPT_ETIQ, ECHO_CAPT_ETIQ, DISTANCE_MAX); 
Bounce captBottlStop = Bounce();

/**
 * @Graph1 => Graph du vérin d'entrée (0-3)
 * @Graph2 => Graph du vérin étiquette
 * @Graph3 => Graph étiquetteuse
 * @Graph4 => Graph Encombrement
 */
int Graph1Step = 0, Graph2Step = 0, Graph3step = 0, Graph4Step = 0;

/**
 * @brief setup est exécuté lors du premier tour de cycle et ne sera pas jamais appellé.
 * @arg : none
 * @return : none
 */
void setup(){
  Serial.begin(9600);
  pinMode(CMD_VER_STOP, OUTPUT);
  pinMode(CMD_VER_ETIQ, OUTPUT); 
  digitalWrite(CMD_VER_STOP, LOW); 
  digitalWrite(CMD_VER_ETIQ, HIGH); 
  captBottlStop.attach(CAPT_VER_STOP,  INPUT_PULLUP );
  captBottlStop.interval(50); 
  
}

void loop(){ 
  Graph1();
  Graph2();
  Graph3();
  Graph4();
}

/**
 * @brief Graph 1 : Graph séquentiel de fonctionnement de la partie alimentation en bouteilles de l'étiquetteuse
 * @arg none
 * @return none
 * 
 */
void Graph1(){
  if (Graph1Step == 0){

  } 
  else if (Graph1Step == 1){

  }
  else if (Graph1Step == 2){
    
  }
  else if (Graph1Step == 3){
    
  } else {
    Graph1Step = 0;
  }
}

/**
 * @brief Graph 2 : Graph séquentiel de fontionnement de la partie vérin pousseur de l'étiquetteuse
 * @arg none
 * @return none
 * 
 */
void Graph2(){
  /* Declare locales */
  bool findBottle;
  static unsigned long detectedBottle;
  captBottlStop.update();
  
  if (Graph2Step == 0){
    findBottle = captBottlStop.read();
    if (findBottle){
      /* Bottle detected on the labeler --> go to step 1*/
      Graph2Step = 1;
    }
  } 
  else if (Graph2Step == 1){
    /* Push bottle */
    digitalWrite(CMD_VER_ETIQ, LOW);
    /* Goto step 2 */
    Graph2Step = 2;
  }
  else if (Graph2Step == 2){
    /* Start labelling timer */
    if (detectedBottle == 0){
      detectedBottle = millis();
    }
    /* Goto step 3 */
    Graph2Step = 3;
  }
  else if (Graph2Step == 3){
    /* check if timer is over */
    if(millis() - detectedBottle >= detectedBottle){
      /* Timer is over */
      /* Go to step 4 */
       Graph2Step = 4;
    }
  }
  else if (Graph2Step == 4){
    /* Retract pusher */
    digitalWrite(CMD_VER_ETIQ, HIGH);
    /* reset Timer */
    detectedBottle = 0;
    
    findBottle = captBottlStop.read();
      if (!findBottle){
        Graph2Step = 5;
      }
  }
  else if (Graph2Step == 5){
    if (Graph1Step == 3){
      Graph2Step = 0;
    }
  } else {
    Graph2Step = 0;
  }
}

/**
 * @brief Graph 3 : Graph séquentiel de fonctionnement de l'étiquetteuse
 * @arg none
 * @return none
 * 
 */
void Graph3(){
  
}
/**
 * @brief Graph 4 : Graph séquentiel de fonctionnement de la table d'accumulation
 * @arg none
 * @return none
 * 
 */
void Graph4(){
  
}