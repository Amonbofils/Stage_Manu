/**
 * @brief Graph 1 : Graph séquentiel de fonctionnement de la partie alimentation en bouteilles de l'étiquetteuse
 * @arg none
 * @return none
 * 
 */
void Graph1(){
  /* Definir les variables / constantes locales */
  
  bool bottleFinded;
  captBottleStop1.update();
  bool bottlePassed;
  captBottleStop2.update();
  
    if (Graph1Step == 0){
    /* Action réalisée sur l'étape */

    /* Gestion de la transition */
    bottleFinded = !captBottleStop1.read();
    //Serial.println(captBottleStop2.read());
    if (bottleFinded && Graph4Step == 0){
      Graph1Step = 1;
    }
   } 
  else if (Graph1Step == 1){
    /* Action réalisée sur l'étape */
    digitalWrite(CMD_VER_STOP, HIGH);
    /* Gestion de la transition */
    bottleFinded = !captBottleStop1.read();
    bottlePassed = !captBottleStop2.read();
    if (bottlePassed) {
      Graph1Step = 2;
    }
  }
  else if (Graph1Step == 2){
    /* Action réalisée sur l'étape */
    digitalWrite(CMD_VER_STOP, LOW);
    /* Gestion de la transition */
    if(Graph2Step == 5){
      Graph1Step = 3;
    }

  }
  else if (Graph1Step == 3){
    /* Action réalisée sur l'étape */
    /* Gestion de la transition */

    if(Graph2Step == 0){
      Graph1Step = 0; 
    }    
  } 
  else {
    Graph1Step = 0;
  }
}