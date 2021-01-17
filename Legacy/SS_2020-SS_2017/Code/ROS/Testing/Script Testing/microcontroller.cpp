#include "arduinomicro.h"
#include "functions.h"
#include <iostream>
#include <iomanip>

//#define portName "/dev/pts/2" // Virtual port
#define portName "/dev/ttyACM0" // Arduino port
#define baudRate 9600

ArduinoMicro board;
functions f;
std::vector<std::string> dutyCycles = {"25","50","75","100"};
vector<float> ADCvalues = {};

void initialize(){
  board.setupSerial(portName, baudRate);
  sleep(1); // Pause for 1 second
}

int main(){
int i=0;

 initialize();
  while(1){
//    for (i=0,i<12, i++){
    board.getADC();
    string str = board.data;
    ADCvalues = f.convertADC(str);

    cout << "volts: " << std::fixed << std::setprecision(3) << ADCvalues [0] << ", " << ADCvalues[1]<< ", " << ADCvalues [2] << ", " << ADCvalues[3] << endl;
    cout << "psi:" << std::fixed << std::setprecision(3) << ADCvalues[4] << ", " << ADCvalues[5]<< ", " << ADCvalues[6] << ", " << ADCvalues[7] << endl;
    cout << "newtons:" << std::fixed << std::setprecision(3) << ADCvalues[8] << ", " << ADCvalues[9]<< ", " << ADCvalues[10] << ", " << ADCvalues[11] << endl;

};

    //board.setPWM(dutyCycles); */


  return 0;
}
