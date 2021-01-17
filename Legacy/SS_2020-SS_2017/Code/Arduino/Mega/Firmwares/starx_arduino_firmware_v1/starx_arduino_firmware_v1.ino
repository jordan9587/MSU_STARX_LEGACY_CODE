/////////////////////////////
// MSU STARX ExoSuit
// Firmware v1.0 (Feb-2018)
// Arduino Micro (ATmega32U4)
// All rights reserved
/////////////////////////////

// Arduino Micro Pinouts //
/////////////////////////////////////////////////////////////////////////
// ADC: A0-A5, A6-A11 (4, 6, 8, 9, 10, 12) [10-bit resolution, 0~1023] //
// PWM: 3, 5, 6, 9, 10, 11, 13 [8-bit resolution, 0~255]               //
/////////////////////////////////////////////////////////////////////////

// Arduino Parameters
const int ADC_NUM = 12;     // Number of ADC pins available
const int PIN_NUM = 10;     // Number of GPIO pins available
const int PAC_PAR = 5;      // Maximum number of parameters in a packet
const char PAC_DEL = ',';   // Packet delimiter
const char PAC_TER = '\r';  // Packet terminator

// Arduino Commands
const String SendADCValuesString = "ADC";
const String SetGPIODirectionString = "PIN";
const String SetGPIODirectionInString = "IN";
const String SetGPIODirectionOutString = "OUT";
const String SetPWMDutyCycleString = "PWM";
const String SetFullStopString = "STP";
const String ErrorMessageString = "ERROR";
const String StartMessageString = "START";

// Arduino Messages
String packet = "";
String parameter[PAC_PAR] = {};

///////////////
// Functions
///////////////

// Sends the ADC values as 12 separate 10-bit words
void sendADC(){
  int pin_adc[ADC_NUM];
  String message = "";
  for(int i = 0; i < ADC_NUM; i++){
    pin_adc[i] = analogRead(i);
    message += String(pin_adc[i]);
    if(i < ADC_NUM - 1){
      message += PAC_DEL;
    }
    else{
      message += PAC_TER;
    }
  }
  Serial.print(message);
}

// Sets specific GPIO pins direction and state
void setGPIO(String parameter[]){
  int pin_gpio[PIN_NUM];
  String message = "";
  Serial.print(message);
}

// Sets the PWM duty cycles in percentage values
void setPWM(String parameter[]){
  int duty_cycle[4];
  String message = "";
  for(int i = 0; i < sizeof(duty_cycle)/sizeof(int); i++){
    duty_cycle[i] = parameter[i+1].toInt();
    message += String(duty_cycle[i]);
    if(i < sizeof(duty_cycle)/sizeof(int) - 1){
      message += PAC_DEL;
    }
    else{
      message += PAC_TER;
    }
  }
  Serial.print(message);
}

// Sets a full stop
void setStop(){
  
}

// Start function
void setup() {
  Serial.begin(9600);
  Serial.print(StartMessageString + PAC_TER);
}

// Main loop
void loop() {
  if (Serial.available() > 0) {
    // Store incoming packet
    packet = Serial.readStringUntil(PAC_TER);
    
    // Split packet into substrings
    if (packet.indexOf(PAC_DEL) != -1) {
      int location;
      for (int i = 0; i < PAC_PAR; i++) {
        location = packet.indexOf(PAC_DEL);
        if (location != -1) {
          parameter[i] = packet.substring(0, location);
          packet = packet.substring(location + 1, packet.length());
        }
        else {
          if (packet.length() > 0)
            parameter[i] = packet;
        }
      }
    }
    else {
      parameter[0] = packet;
    }

    ///////////////
    // Commands
    ///////////////
    
    if(parameter[0] == SendADCValuesString){
      sendADC();
    }
    else if(parameter[0] == SetGPIODirectionString){
      setGPIO(parameter);
    }
    else if(parameter[0] == SetPWMDutyCycleString){
      setPWM(parameter);
    }
    else if(parameter[0] == SetFullStopString){
      setStop();
    }
    else{
      Serial.print(ErrorMessageString + PAC_TER);
    }
  }
}
