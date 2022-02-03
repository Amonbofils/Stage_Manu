/*
  Morse.h - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/
#ifndef Detector_h
#define Detector_h

#include <Arduino.h>
#include <Bounce2.h>

class Detector
{
  public:
    Detector(int type, int pin, bool activeState, int pinTrigger = 0, int detectDistance = 0);
    bool isDetected();
    bool risingEdge();
    bool fallingEdge();
  private:
    bool _activeState;
    bool _lastState;
    bool _rised;
    bool _fell;
    int _pin;
    int _pinTrigger;
    int _detectDistance;
    int _type;
    Bounce _detector;
};

#endif