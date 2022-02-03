/*
  Morse.cpp - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/

#include "Arduino.h"
#include "Detector.h"
#include "Bounce2.h"
/* Constantes pour le timeout */
const unsigned long MEASURE_TIMEOUT = 25000UL; // 25ms = ~8m à 340m/s

/* Vitesse du son dans l'air en mm/us */
const float SOUND_SPEED = 340.0 / 1000;

/**
 * @brief Construct a new Detector:: Detector object
 * 
 * @param type sensor type (0: On/Off sensor; 1: distance sensor)
 * @param pin type 0: pin of sensor, type 1: echo's pin
 * @param activeState if active state = 1 of 0
 * @param pinTrigger for type 1 : trigger pin
 * @param detectDistance  for type 1 : Minimum distance to declare object detected
 */
Detector::Detector(int type, int pin, bool activeState = true, int pinTrigger = 0, int detectDistance = 0) {
  _activeState = activeState;
  _type = type;
  _pin = pin;
  _pinTrigger = pinTrigger;
  switch (type) {
    case 0: 
      _detector = Bounce();
      _detector.attach(pin,  INPUT_PULLUP );
      _detector.interval(50); 
      break;
    case 1:
      pinMode(pinTrigger, OUTPUT);
      digitalWrite(pinTrigger, LOW); // La broche TRIGGER doit être à LOW au repos
      pinMode(pin, INPUT);
      break;
  }
}

bool Detector::isDetected()
{
  _detector.update();
  switch (_type) {
    case 0:
      return (!_activeState)?_detector.read():!_detector.read();
      break;
    case 1: 
      _lastState= (measure(_pinTrigger, _pin)<=_detectDistance)?true:false;
      return _lastState;
      break;
  }
}

bool Detector::rinsingEdge(){
   _detector.update();
  switch (_type) {
    case 0:
      return (!_activeState)?_detector.risingEdge():!_detector.fallingEdge();
      break;
    case 1:
    /* to do */
      break;
  }
}

bool Detector::fallingEdge(){
  switch (_type) {
    case 0:
      return (!_activeState)?_detector.fallingEdge():!_detector.risingEdge();
      break;
    case 1:
      /* to do */
      break;
  }
}

float measure(int TRIGGER_PIN, int ECHO_PIN){
  float SOUND_SPEED = 340.0 / 1000;
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  long read = pulseIn(ECHO_PIN, HIGH, MEASURE_TIMEOUT);
  float distance_mm = read / 2.0 * SOUND_SPEED;
  return (distance_mm/10.0);
}