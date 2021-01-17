#include "arduinomicro.h"

//#define portName "/dev/pts/2" // Virtual port
#define portName "/dev/ttyACM1" // Arduino port
#define baudRate 9600

ArduinoMicro board;
std::vector<std::string> dutyCycles = {"25","50","75","100"};

void initialize(){
  board.setupSerial(portName, baudRate);
  sleep(1); // Pause for 1 second
}

int main(){
  initialize();
  while(1){
    board.getADC();
    //board.setPWM(dutyCycles);
  }
  return 0;
}
