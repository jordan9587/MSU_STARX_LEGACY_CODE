#include "functions.h"
#include "arduinomicro.h"
#include <string>
using namespace std;



vector<string> functions::split(const string &s, char delim) {
    stringstream ss(s);
    string item;
    vector<string> tokens;
    while (getline(ss, item, delim)) {
        tokens.push_back(item);
    }
    return tokens;
}

float functions::convertVoltage (float v){
  float volts = (5.0f/1023.0f)*v;
  return volts;
}

float functions::convertPSI (float p){
  float psi = (p-5.1f)/.04f;
  return psi;
}

float functions::convertNewtons (float n){
  float newtons = (10.0f*5.0f/n-1.0f);
  return newtons;
}
