/*
  Morse.h - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/
#ifndef Morse_h
#define Morse_h

#include "Arduino.h"

class DetectBottle
{
  public:
    DetectBottle(int pin, int interval, bool activeState);
    void isDetected();
  private:
    bool _activeState;
};

#endif