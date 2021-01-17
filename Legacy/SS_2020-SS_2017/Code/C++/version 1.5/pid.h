// This is start of the header guard
#ifndef PID_H
#define PID_H

#include <stdio.h>
#include <sys/time.h>

class PID{
  public:
    // PID Constants
    #define MANUAL 0
  	#define AUTOMATIC 1
  	#define DIRECT 0
  	#define REVERSE 1
    // PID Variables
    bool inAuto = false;
    int controllerDirection = DIRECT;
    unsigned long sampleTime = 25; //milliseconds
    unsigned long lastTime = 0;
    double inputValue = 0.0;
    double outputValue = 0.0;
    double errorValue = 0.0;
    double setPoint = 0.0;
    double iTerm = 0.0;
    double dInput = 0.0;
    double lastInput = 0.0;
    double kpGain = 0.0;
    double kiGain = 0.0;
    double kdGain = 0.0;
    double outMin = 0.0;
    double outMax = 0.0;
    // PID Functions
    unsigned long millis(void);
    bool computeValues(void);
    void setTunings(double Kp, double Ki, double Kd);
    void setSampleTime(int newSampleTime);
    void setOutputLimits(double Min, double Max);
    void setMode(int Mode);
    void setControllerDirection(int Direction);
    void initialize(void);
};

// This is the end of the header guard
#endif
