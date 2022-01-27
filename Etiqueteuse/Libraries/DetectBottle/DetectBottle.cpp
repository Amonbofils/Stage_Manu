/*
  Morse.cpp - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/

#include "Arduino.h"
#include "DetectBottle.h"
#include "Bounce2.h"

DetectBottle::DetectBottle(int pin, int interval, bool activeState)
{
  Bounce _sensor = Bounce();
  _sensor.attach(pin,  INPUT_PULLUP );
  _sensor.interval(50); 
  _activeState = activeState;
}

void DetectBottle::isDetected()
{
  Serial.println("Coucou");
}