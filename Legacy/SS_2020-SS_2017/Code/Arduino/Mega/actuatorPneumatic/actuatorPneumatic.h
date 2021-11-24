/**
 * \file actuatorPneumatic.h
 *
 * \author Sparty
 */


#ifndef actuatorPneumatic_h
#define actuatorPneumatic_h

#include "Arduino.h"

class actuatorPneumatic
{
  public:
    /**
    * Constructor
    */
    actuatorPneumatic();
    /*
    * Reads voltage pressure sensors and returns their pressure value
    * declared as void for now.
    */
    void pPWM(float pwmfreq, float pwmDC1, float pwmDC2, float pwmDC3, float pwmDC4);
    void actuatorLoop();
    void displayPressureReadings(float P1, float P2, float P3, float P4, float P5);


  private:
    // Set this to match whatever prescaler value you set in CS registers below
    int prescaler = 256;

    // Initalise values for the PWM duty cycle set by pots
    float potDC1 = 0;
    float potDC2 = 0;
    float potDC3 = 0;
    float potDC4 = 0;
};

#endif
