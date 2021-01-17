// This is start of the header guard
#ifndef ARDUINOMICRO_H
#define ARDUINOMICRO_H

#include "serial.h"
#include <vector>
#include <string>

class ArduinoMicro{
  public:
    // Arduino Serial
    SerialPort arduinoPort;
    int waitTime = 100; // Send and receive wait time (milliseconds)
    char* data;
    const char* packet;
    // Arduino Parameters
    const int ADCPinCount = 12;
    const int GPIOPinCount = 20;
    const double ADCVoltageMultipler = 5 / 1023;
    const std::string PacketDelimiterString = ",";
    const std::string PacketTerminatorString = "\r";
    // Arduino Commands
    const std::string GetADCValuesString = "ADC";
    const std::string SetGPIODirectionString = "PIN";
    const std::string SetGPIODirectionOutString = "OUT";
    const std::string SetGPIODirectionInString = "IN";
    const std::string SetPWMDutyCycleString = "PWM";
    const std::string SetFullStopString = "STP";
    // Arduino Functions
    void getADC(void);
    void setPWM(std::vector<std::string> dutyCycles);
    void setupSerial(std::string portName, int baudRate);
    std::string createPacket(std::string command, std::vector<std::string> parameters);
};

// This is the end of the header guard
#endif
