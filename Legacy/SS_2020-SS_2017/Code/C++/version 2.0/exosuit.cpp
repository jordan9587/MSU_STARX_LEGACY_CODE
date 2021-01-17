#include "exosuit.h"

void ExoSuit::updateADC(void){
  adcValues.clear();
  std::vector<std::string> str = cvt.splitString(board.getADC(), ',');
  for(int i=0; i < str.size(); i++){
    adcValues.push_back(cvt.stringToInt(str[i]));
    //std::cout << adcValues[i] << " ";
  }
  //printf("\n");
}

void ExoSuit::updateGPIO(void){

}

void ExoSuit::updateSensors(void){
  pressureStates.clear();
  forceStates.clear();
  emgStates.clear();
  for(int i = 0; i < SensorMax; i++){
    // Pressure Sensors
    if(i < pressurePins.size())
      pressureStates.push_back(cvt.convertToPressure(cvt.convertToVoltage(adcValues[pressurePins[i]], board.ADCVoltageMultiplier)));
    // Force Sensors
    if(i < forcePins.size())
      forceStates.push_back(cvt.convertToForce(cvt.convertToVoltage(adcValues[forcePins[i]], board.ADCVoltageMultiplier)));
    // EMG Sensors
    if(i < emgPins.size())
      emgStates.push_back(cvt.convertToVoltage(adcValues[emgPins[i]], board.ADCVoltageMultiplier));
  }
  for(int i = 0; i < pressureStates.size(); i++){
    std::cout << pressureStates[i] << " ";
  }
  for(int i = 0; i < emgStates.size(); i++){
    std::cout << emgStates[i] << " ";
  }
  std::cout << std::endl;
}

void ExoSuit::updatePressurePID(void){
  outputStates.clear();
  for(int i = 0; i < pressurePID.size(); i++){
    pressurePID[i].inputValue = pressureStates[i];
    //pressurePID[i].setPoint = setpointStates[i];
    pressurePID[i].setPoint = setpointValue;
    pressurePID[i].computeValues();
    outputStates.push_back(pressurePID[i].outputValue);
    std::cout << outputStates[i] << " ";
  }
  std::cout << std::endl;
}

void ExoSuit::updatePWM(void){
  dutyCycleStates.clear();
  dutyCycles.clear();
  for(int i = 0; i < outputStates.size(); i++){
      dutyCycleStates.push_back((int)std::round(outputStates[i]));
      dutyCycles.push_back(cvt.intToString(dutyCycleStates[i]));
  }
  board.setPWM(dutyCycles);
  //board.setPWM({"75","0","0","0"});
}

void ExoSuit::initialize(void){
  // Sensor States
  adcValues.clear();
  pressureStates.clear();
  forceStates.clear();
  emgStates.clear();
  adcValues.resize(board.ADCPinCount);
  pressureStates.resize(pressurePins.size());
  forceStates.resize(forcePins.size());
  emgStates.resize(emgPins.size());
  // Pressure Controller States
  pressurePID.clear();
  outputStates.clear();
  setpointStates.clear();
  dutyCycleStates.clear();
  dutyCycles.clear();
  pressurePID.resize(pressurePins.size());
  outputStates.resize(pressurePins.size());
  setpointStates.resize(pressurePins.size());
  dutyCycleStates.resize(pressurePins.size());
  dutyCycles.resize(pressurePins.size());
  for(int i = 0; i < pressurePID.size(); i++){
    pressurePID[i].setMode(pressurePID[i].AUTOMATIC);
    pressurePID[i].setOutputLimits(outputMin, outputMax);
    pressurePID[i].setTunings(Kp, Ki, Kd);
  }
  // Serial Port
  board.setupSerial(portName, baudRate);
  sleep(1); // Pause for 1 second
}
