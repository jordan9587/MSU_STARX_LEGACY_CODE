#include <LiquidCrystal.h> // includes the LiquidCrystal Library 
LiquidCrystal lcd(1, 2, 4, 5, 6, 7); // Creates an LC object. Parameters: (rs, enable, d4, d5, d6, d7) 
#include "Arduino.h"

//defines for Rotary speed and counting
#define encoder0PinA 2
#define encoder0PinB 3
#define DataPin 9 // can be any other pin
      // My Encoder has 128 Clock pulses per revolution
      // note that 468750.0 = (60 seonds * 100000 microseconds)microseconds in a minute / 128 pulses in 1 revolution)
      // change the math to get the proper multiplier for RPM for your encoder
#define Multiplier 468750.0 // don't forget a decimal place to make this number a floating point number

long Counter; 

//Direction rotary inputs
int ncounter = 0; 
int currentStateCLK;
int previousStateCLK; 
String encdir ="";
//End Direction

//Pulse counting
volatile long EncoderCounter = 0;
volatile float SpeedInRPM = 0;

//128 pulses per revolution to degrees
float a = 360.0/128.0;


void onPin2CHANGECallBackFunction(uint32_t Time, uint32_t PinsChanged, uint32_t Pins){ 
    static uint32_t lTime; // Saved Last Time of Last Pulse
    uint32_t cTime; // Current Time
    cTime = micros(); // Store the time for RPM Calculations
    int32_t dTime; // Delt in time

// Encoder Code
    bool DataPinVal = digitalRead(DataPin);
// We know pin 2 just went high to trigger the interrupt
// depending on direction the data pin will either be high or low

  EncoderCounter += (encoder0PinB) ? 1 : -1;

// End Encoder Code



// calculate the DeltaT between pulses
    dTime = cTime - lTime; 
    lTime = cTime;
    SpeedInRPM = Multiplier / ((DataPinVal) ? dTime: (1 * dTime)); // Calculate the RPM Switch DeltaT to either positive or negative to represent Forward or reverse RPM
}

void setup() {
  noInterrupts (); 
// Because when the interrupt occurs the EncoderCounter and SpeedInRPM could be interrupted while they 
// are being used we need to say hold for a split second while we copy these values down. This doesn't keep the 
// interrupt from occurring it just slightly delays it while we maneuver values.
// if we don't do this we could be interrupted in the middle of copying a value and the result get a corrupted value.
 
  Counter = EncoderCounter;

  
  interrupts ();
  Serial.begin(115200); //115200
  // put your setup code here, to run once:
  pinMode(encoder0PinB, INPUT);  
  
  pinMode(DataPin, INPUT);
  attachInterrupt(0,onPin2CHANGECallBackFunction,RISING);

  //Rotary Direction
  pinMode(encoder0PinA, INPUT);
  previousStateCLK = digitalRead(encoder0PinA);
  //End Rotary Direction 
}

void loop() {



//Start Rotary Direction //

// Read the current state of inputCLK
   currentStateCLK = digitalRead(encoder0PinA);
    
   // If the previous and the current state of the inputCLK are different then a pulse has occured
   if (currentStateCLK != previousStateCLK){
       
     // If the inputDT state is different than the inputCLK state then 
     // the encoder is rotating counterclockwise
     if (digitalRead(encoder0PinB) != currentStateCLK) { 
       ncounter --;
       encdir ="CW";
      // digitalWrite(ledCW, LOW);
       //digitalWrite(ledCCW, HIGH);
       
     } else {
       // Encoder is rotating clockwise
       ncounter ++;
       encdir ="CCW";
       //digitalWrite(ledCW, HIGH);
       //digitalWrite(ledCCW, LOW); 
     }
//End Rotary Direction //

  float Speed;
  
  previousStateCLK = currentStateCLK;
  Speed = SpeedInRPM;

// use the speed and counter values for whatever you need to do.

if (ncounter >= 128 || ncounter <= -128) {
  
  
  ncounter = 0;
}

  static unsigned long SpamTimer;
  if ( (unsigned long)(millis() - SpamTimer) >= (100)) {
    SpamTimer = millis();
    //Serial.print(Counter );
    
    //Start Rotary Direction //
    Serial.print("\t");
    Serial.print("Direction: ");
    Serial.print(encdir);
    Serial.print(" -- Value: ");
    Serial.print(ncounter);
    //End Rotary Direction //
    
    Serial.print("\t");
    Serial.print(Speed , 3);
    Serial.print(" RPM");
    Serial.print("\t");
    Serial.println();
    SpeedInRPM = 0; // if no pulses occure in the next 100 miliseconds then we must assume that the motor has stopped

    
  }
   }
   }

