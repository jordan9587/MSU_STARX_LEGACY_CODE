#include "arduinomicro.h"
#include <algorithm>
#include <iostream>
#include "functions.h"
#include <iomanip>
#include <string>
#include "PID_v1.h"
using namespace std;
//#define portName "/dev/pts/1" // Virtual port
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
double* output;
int main(){
  initialize();
  while(1){
    board.getADC();
    string output = string(board.data);
    //cout<<"output"<<output<<endl;
    board.setPWM(dutyCycles);
    vector<string> result = f.split(output,',');
    //ADCvalues = f.convertADC(result);
    vector<float> vectFlt = {};
    for(int i=0; i<result.size();i++){
      float f = stof(result[i]);
      vectFlt.push_back(f);
      //cout<<"value"<<vectFlt[i]<<endl;
    }
    for(int i=0;i<vectFlt.size();i++){
      vectFlt[i] = f.convertVoltage(vectFlt[i]);
      cout << "EMG sensor volts: " << std::fixed << std::setprecision(3) << vectFlt [i]<<endl;
    }

    //for(int i=0; i < 4;i++){
      //cout << "EMG sensor volts: " << std::fixed << std::setprecision(3) << vectFlt [0]<<endl;
      //PID myPID(ADCvalues[0],output,0,12,12,12,1 );
      //myPID.Compute();
      //cout<<"new output"<<*(myPID.myOutput)<<endl;

    //}

    /*cout << "psi:" << std::fixed << std::setprecision(3) << ADCvalues[4] << ", " << ADCvalues[5]<< ", " << ADCvalues[6] << ", " << ADCvalues[7] << endl;
    cout << "newtons:" << std::fixed << std::setprecision(3) << ADCvalues[8] << ", " << ADCvalues[9]<< ", " << ADCvalues[10] << ", " << ADCvalues[11] << endl;
*/

  }
  return 0;
}
