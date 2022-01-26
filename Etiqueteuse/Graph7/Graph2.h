/**
 * @brief Graph 2 : Graph séquentiel de fontionnement de la partie vérin pousseur de l'étiquetteuse
 * @arg none
 * @return none
 * 
 */
void Graph2(){
  /* Declare locales */
  captBottleLabel.update();
  bool bottleFinded;
  static unsigned long bottleDetected;

  if (Graph2Step == 0){
    bottleFinded = !captBottleLabel.read();
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
    bottleFinded = !captBottleLabel.read();
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