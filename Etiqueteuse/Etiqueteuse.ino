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
#define LABEL_TIMER 2000
#define DEBUG_TIMER 1000
#define SECURITY_TIMER 3000 
#define CAPT_VER_STOP 2
#define CAPT_END 6
NewPing captLabel = NewPing(TRIG_CAPT_LABEL, ECHO_CAPT_LABEL, DISTANCE_MAX); 
Bounce captBottleStop = Bounce();
Bounce captBottleLabel = Bounce();
Bounce captBottleEnd = Bounce();


/**
 * @Graph1 => Graph du vérin d'entrée (0-3)
 * @Graph2 => Graph du vérin étiquette
 * @Graph3 => Graph étiquetteuse
 * @Graph4 => Graph Encombrement
 * @Graph5 => Graph Débuggage
 */
int Graph1Step = 0, Graph2Step = 0, Graph3step = 0, Graph4Step = 0, Graph5Step = 0;

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
  captBottleEnd.attach(CAPT_END, INPUT_PULLUP);
  captBottleEnd.interval(50);

}

void loop(){ 
  Graph1();
  Graph2();
  Graph3();
  Graph4();
  Graph5();
}

/**
 * @brief Graph 1 : Graph séquentiel de fonctionnement de la partie alimentation en bouteilles de l'étiquetteuse
 * @arg none
 * @return none
 * 
 */
void Graph1(){
  /* Definir les variables / constantes locales */
  
  bool bottleFinded;
  captBottleStop.update();

  
  
  if (Graph1Step == 0){
    /* Action réalisée sur l'étape */

    /* Gestion de la transition */
    bottleFinded = !captBottleStop.read();
    if (bottleFinded && Graph4Step == 0){
      Graph1Step = 1;
    }
   } 
  else if (Graph1Step == 1){
    /* Action réalisée sur l'étape */
    digitalWrite(CMD_VER_STOP, LOW);
    /* Gestion de la transition */
    bottleFinded = captBottleStop.read();
    if (bottleFinded == false) {
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
  bool bottleFinded;
  static unsigned long bottleDetected;
  
  if (Graph2Step == 0){
    bottleFinded = detectBottle(captLabel.ping_cm(),DISTANCE_DETECT);
    if (bottleFinded){
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
    if (bottleDetected == 0){
      bottleDetected = millis();
    }
    /* Goto step 3 */
    Graph2Step = 3;
  }
  else if (Graph2Step == 3){
    /* check if timer is over */
    if(millis() - bottleDetected >= LABEL_TIMER){
      /* Timer is over */
      /* Go to step 4 */
       Graph2Step = 4;
    }
  }
  else if (Graph2Step == 4){
    /* Retract pusher */
    digitalWrite(CMD_VER_LABEL, HIGH);
    /* reset Timer */
    bottleDetected = 0;
    bottleFinded = detectBottle(captLabel.ping_cm(),DISTANCE_DETECT);
      if (!bottleFinded){
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
  /* Declare locales */
  /*  Action réalisée sur l'étape */
  /* Gestion de la transition */
}
/**
 * @brief Graph 4 : Graph séquentiel de fonctionnement de la table d'accumulation
 * @arg none
 * @return none
 * 
 */

void Graph4(){
  /* Definir les variables / constantes locales */
  bool bottleFinded;
  captBottleEnd.update();
  static unsigned long bottleDetected;
  if (Graph4Step == 0){
    /* Action réalisée sur l'étape */
    /* Gestion de la transition */
    bottleFinded = !captBottleEnd.read();
    if (bottleFinded){
      Graph4Step = 1;
    }
   } 
  else if (Graph4Step == 1){
    /* Action réalisée sur l'étape */
    if (bottleDetected == 0){
      bottleDetected = millis();
    }
    /* Gestion des transitions */
    /* Transition vers étape 10 */
    bottleFinded = captBottleEnd.read();
    if (!bottleFinded) {
      Graph4Step = 10;
    }
    /* Transition vers étape 20 */ 
    else if (millis() - bottleDetected >= SECURITY_TIMER){
      /* Timer is over */
      /* Go to step 20 */
      Graph4Step = 20;
    }
  }
  else if (Graph4Step == 10){
    /* Action réalisée sur l'étape */
    bottleDetected=0;
    /* Gestion de la transition */
    Graph4Step=0;
  }

  else if ( Graph4Step == 20){
     /* Action réalisée sur l'étape */
    bottleDetected=0; 
     /* Gestion de la transition */
    bottleFinded = captBottleEnd.read();
    if(!bottleFinded){
      Graph4Step = 0;
    }
  } 
  else {
    Graph4Step = 0;
  }

}

/**
 * @brief transformation d'une distance en trtue ou false pour bottleFinded
 * 
 * @param distance mesure du capteur pour une disstance 
 * @param distanceDetected seuil de détection
 * @return true 
 * @return false 
 */
bool detectBottle(float distance, float distanceDetected){
  if(distance>0 && distance <= distanceDetected){
    return true;
  }
  if (distance == 0 || distance > distanceDetected){
    return false;
  }
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
  /* Graph */
  if (Graph5Step == 0) {
    /* Actions */
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
    }
    /* Transitions */
    if (currentTime - debbuggage >= DEBUG_TIMER) {
      Graph5Step = 0;
    }
  } else {
    Graph5Step = 0;
  } 
}