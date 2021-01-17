#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include<iostream>
using std::cout; using std::endl; using std::ostream;
#include<string>
using std::string;
#include <vector>
using std::vector;
#include <sstream>

class functions {
  public:

    const std::string PacketDelimiterString = ","; //from arduinomicro.h
    void split(const string& s, vector<string>& v);
    vector<int> convertInt (vector<string> v2);
    vector<float> convertFloat (vector<int> intVect);
    float convertVoltage (float v);
    float convertPSI (float p);
    float convertNewtons (float n);
    vector<float> convertADC (string rawDataStr); //update
};

#endif
