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
    bottleFinded = !captBottleEnd.read();
    if(!bottleFinded){
      Graph4Step = 0;
    }
  } 
  else {
    Graph4Step = 0;
  }

}