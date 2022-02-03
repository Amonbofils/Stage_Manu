// Programmation Etiqueteuse
#include <Arduino.h>
#include <Bounce2.h>
#include <Detector.h>

#define CMD_VER_STOP 12 
#define CMD_VER_LABEL 11
#define DISTANCE_DETECT 5 
#define DISTANCE_MAX 20 
#define TIME_DELAY 2000
#define LABEL_TIMER 2000
#define DEBUG_TIMER 1000
#define SECURITY_TIMER 3000 
#define CAPT_VER_STOP1 2
#define CAPT_VER_STOP2 3
#define CAPT_LABEL 6
#define CAPT_END 7
#define DEBUG_BUTTON 8

Bounce captBottleStop1 = Bounce(); 
/* AVANT
Bounce captBottleStop2 = Bounce();
*/
/* APRES */
//Detector captBottleStop1(0, CAPT_VER_STOP1, true);
Bounce captBottleStop2 = Bounce();
Bounce captBottleLabel = Bounce();
Bounce captBottleEnd = Bounce();
Bounce debugButton = Bounce();



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
  pinMode(CMD_VER_STOP, OUTPUT);
  pinMode(CMD_VER_LABEL, OUTPUT); 
  digitalWrite(CMD_VER_STOP, LOW); 
  digitalWrite(CMD_VER_LABEL, HIGH);
  captBottleStop1.attach(CAPT_VER_STOP1,  INPUT_PULLUP );
  captBottleStop1.interval(50);
  captBottleStop2.attach(CAPT_VER_STOP2,  INPUT_PULLUP );
  captBottleStop2.interval(50);
  captBottleEnd.attach(CAPT_END, INPUT_PULLUP);
  captBottleEnd.interval(50);
  debugButton.attach(DEBUG_BUTTON, INPUT_PULLUP);
  debugButton.interval(50);
  captBottleLabel.attach(CAPT_LABEL, INPUT_PULLUP);
  captBottleLabel.interval(50);
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
 */

void Graph1(){
  /* Definir les variables / constantes locales */
  /* exemple */
    /* AVANT
  bool bottleFinded;
  captBottleStop1.update(); 
  */

  bool bottlePassed;
  captBottleStop2.update();

  switch(Graph1Step){
    
      /* Action réalisée sur l'étape */
      /* Gestion de la transition */

    /* exemple */
   /*AVANT
    case 0:
      bottleFinded = !captBottleStop1.read();
      if (bottleFinded && Graph4Step == 0){
        Graph1Step = 1;
      }
      break;
     // */
     /* APRES */
      case 0:
      if (captBottleStop1.read() && Graph4Step== 0) 
         Graph1Step = 1;
      break;
    /* fin exemple */

    
    case 1:
      /* Action réalisée sur l'étape */
      digitalWrite(CMD_VER_STOP, HIGH);
      /* Gestion de la transition */
      bottlePassed = !captBottleStop2.read();
      if (bottlePassed) {
        Graph1Step = 2;
      }
      break;
    case 2:
      /* Action réalisée sur l'étape */
      digitalWrite(CMD_VER_STOP, LOW);
      /* Gestion de la transition */
      if(Graph2Step == 5){
        Graph1Step = 3;
      }
      break;
    case 3:
      /* Action réalisée sur l'étape */
      /* Gestion de la transition */
      if(Graph2Step == 0){
        Graph1Step = 0;
      }    
      break;
    default:
      Graph1Step = 0;
      break;
  }    
}

/**
 * @brief Graph 2 : Graph séquentiel de fontionnement de la partie vérin pousseur de l'étiquetteuse
 * @arg none
 * @return none
 */
void Graph2(){
  /* Declare locales */
  captBottleLabel.update();
  bool bottleFinded;
  static unsigned long bottleDetected;
  switch(Graph2Step){
    case 0:
      bottleFinded = !captBottleLabel.read();
      if(bottleFinded){
      /* Bottle detected on the labeler --> go to step 1*/
        Graph2Step = 1;
      }
      break;
   
    case 1:
      /* Push bottle */
      digitalWrite(CMD_VER_LABEL, LOW);
      /* Goto step 2 */
      Graph2Step = 2;
      break;

    case 2:
      /* Start labelling timer */
      if (bottleDetected == 0){
        bottleDetected = millis();
        /* Goto step 3 */
        Graph2Step = 3;
      }
      break;
  
    case 3:
      /* check if timer is over */
      if(millis() - bottleDetected >= LABEL_TIMER){
        /* Timer is over */
        /* Go to step 4 */
        Graph2Step = 4;
      }
      break;

    case 4:
      /* Retract pusher */
      digitalWrite(CMD_VER_LABEL, HIGH);
      /* reset Timer */
      bottleDetected = 0;
      bottleFinded = !captBottleLabel.read();
        if (!bottleFinded){
          Graph2Step = 5;
        }
      break;

    case 5:
      if (Graph1Step == 3){
        Graph2Step = 0;
      }
      break;

    default:
      Graph2Step = 0;
      break;
  }
}

/**
 * @brief Graph 3 : Graph séquentiel de fonctionnement de l'étiquetteuse
 * @arg none
 * @return none
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
 */
void Graph4(){
  switch(Graph4Step){
  /* Definir les variables / constantes locales */
  bool bottleFinded;
  captBottleEnd.update();
  static unsigned long bottleDetected;
    case 0:
      /* Action réalisée sur l'étape */
      /* Gestion de la transition */
      bottleFinded = !captBottleEnd.read(); 
      if (bottleFinded){
        Graph4Step = 1;
      }
      break; 
    case 1:
      /* Action réalisée sur l'étape */
      if (bottleDetected == 0){
        bottleDetected = millis();
      }
      /* Gestion des transitions */
      /* Transition vers étape 10 */
      bottleFinded = !captBottleEnd.read(); 
      if (!bottleFinded) {
        Graph4Step = 10;
      }
      /* Transition vers étape 20 */ 
      else if (millis() - bottleDetected >= SECURITY_TIMER){
      /* Timer is over */
      /* Go to step 20 */
      Graph4Step = 20;
      }
      break;

  case 10:
    /* Action réalisée sur l'étape */
    bottleDetected=0;
    /* Gestion de la transition */
    Graph4Step=0;
    break;

  case 20:
     /* Action réalisée sur l'étape */
    bottleDetected=0;
     /* Gestion de la transition */
    bottleFinded = !captBottleEnd.read();
    if(!bottleFinded){ 
      Graph4Step = 0;
    }
    break;

  default:
    Graph4Step = 0;
    break;
  }
}
/**
 * @brief Graph de Debbuggaga : Graph séquentiel de Débuggage
 * @arg none
 * @return none
 */
void Graph5(){
  /*  Declare locales */
  static unsigned long debbuggage;
  unsigned long currentTime;
  bool bugButton;
  debugButton.update();
  switch(Graph5Step){
    case 0:
      /* Actions */
      bugButton = debugButton.read();
      if(bugButton){
        Serial.begin(9600);
      }
        /* Transitions */
        Graph5Step = 1;
      break;

    case 1:
      /* Actions */
      debbuggage = millis();
      /* Transitions */
      Graph5Step = 2;
      break;

  case 2:
    /* Actions */
    currentTime = millis();
    if (currentTime - debbuggage >= DEBUG_TIMER) {
      Serial.println( "********************");
      Serial.print("Graph 1 : ");
      Serial.println(Graph1Step);
      Serial.print("Graph 2 : ");
      Serial.println(Graph2Step);
      Serial.print("Graph 4 : ");
      Serial.println(Graph4Step);
      Serial.end();
    }
    /* Transitions */
    if (currentTime - debbuggage >= DEBUG_TIMER) {
      Graph5Step = 0;
    }
    break;

  default:
    Graph5Step = 0;
    break;
  }
}
