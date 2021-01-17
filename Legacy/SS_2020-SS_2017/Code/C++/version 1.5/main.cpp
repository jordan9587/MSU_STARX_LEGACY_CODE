// MSU STARX Exosuit Software
// Version 1.5 (April 26, 2018)
// All rights reserved

#include "exosuit.h"

ArduinoMicro mcu;
ExoSuit Sparty;

int main(){
  Sparty.initialize();
  while(1){
    Sparty.updateADC();
    Sparty.updateSensors();
    Sparty.updatePressurePID();
    Sparty.updatePWM();
  }
  //
  return 0;
}
