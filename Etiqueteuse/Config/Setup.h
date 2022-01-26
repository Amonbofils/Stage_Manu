
void SetupInputOutput() {
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