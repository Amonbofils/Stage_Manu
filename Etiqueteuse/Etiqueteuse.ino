// Programmation Etiqueteuse
#include <Arduino.h>
#include <NewPing.h>
#include <Bounce2.h>

#define TRIG_CAPT_LABEL 4
#define ECHO_CAPT_LABEL 3
#define CMD_VER_STOP 11 
#define CMD_VER_LABEL 10 
#define DISTANCE_DETECT 5 
#define DISTANCE_MAX 20 
#define TIME_DELAY 2000
#define TIMER_LABEL 2000
#define CAPT_VER_STOP 2

NewPing captLabel = NewPing(TRIG_CAPT_LABEL, ECHO_CAPT_LABEL, DISTANCE_MAX); 
Bounce captBottleStop = Bounce();
Bounce captBottleLabel = Bounce();

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
  pinMode(CMD_VER_LABEL, OUTPUT); 
  digitalWrite(CMD_VER_STOP, LOW); 
  digitalWrite(CMD_VER_LABEL, HIGH); 
  captBottleStop.attach(CAPT_VER_STOP,  INPUT_PULLUP );
  captBottleStop.interval(50); 
  //captBottleLabel.attach(TRIG_CAPT_LABEL, ECHO_CAPT_LABEL, INPUT_PULLUP);
  captBottleLabel.attach (50);
  
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
  /* Definir les variables / constantes locales */
  bool findBottle;
  captBottleStop.update();
  
  if (Graph1Step == 0){
    /* Action réalisée sur l'étape */

    /* Gestion de la transition */
    findBottle = captBottleStop.read();
    if (findBottle && Graph4Step == 0){
      Graph1Step = 1;
    }
   } 
  else if (Graph1Step == 1){
    /* Action réalisée sur l'étape */
    digitalWrite(CMD_VER_STOP, LOW);
    /* Gestion de la transition */
    findBottle = captBottleStop.read();
    if (findBottle == false) {
      Graph1Step = 2;
    }
  }
  else if (Graph1Step == 2){
    /* Action réalisée sur l'étape */
    digitalWrite(CMD_VER_STOP, HIGH);
    /* Gestion de la transition */
    if(Graph2Step == 5){
      Graph1Step = 3;
    }

  }
  else if (Graph1Step == 3){
    /* Action réalisée sur l'étape */
    
    /* Gestion de la transition */
    if(Graph2Step == 0){
      Graph1Step == 0; 
    }    
  } 
  else {
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
  captBottleLabel.update();
  
  if (Graph2Step == 0){
    findBottle = captBottleLabel.read();
    if (findBottle){
      /* Bottle detected on the labeler --> go to step 1*/
      Graph2Step = 1;
    }
  } 
  else if (Graph2Step == 1){
    /* Push bottle */
    digitalWrite(CMD_VER_LABEL, LOW);
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
    digitalWrite(CMD_VER_LABEL, HIGH);
    /* reset Timer */
    detectedBottle = 0;
    
    findBottle = captBottleStop.read();
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