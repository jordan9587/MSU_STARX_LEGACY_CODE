/**
 * \file actuatorPneumatic.cpp
 *
 * \author Sparty
 * Arduino Micro (ATmega2560)
 */


#include "actuatorPneumatic.h"
#include "pressureSensor.h"
#include "Arduino.h"

actuatorPneumatic::actuatorPneumatic()
{
  // input pins for valve switches
  pinMode(50, INPUT);
  pinMode(51, INPUT);
  pinMode(52, INPUT);
  pinMode(53, INPUT);

  // output pins for valve PWM
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

  // this operation (AND plus NOT), set the eight bits in TCCR registers to 0 
  // TCCRx - Timer/Counter Control Register. The pre-scaler can be configured here.
  int eightOnes = 255;  // This is 11111111 in binary
  // 17.11.2 TCCR3A – Timer/Counter 3 Control Register A
  TCCR3A &= ~eightOnes;
  // 17.11.6 TCCR3B – Timer/Counter 3 Control Register B
  TCCR3B &= ~eightOnes;
  // 17.11.3TCCR4A – Timer/Counter 4 Control Register A
  TCCR4A &= ~eightOnes;
  // 17.11.7TCCR4B – Timer/Counter 4 Control Register B
  TCCR4B &= ~eightOnes;

  // set waveform generation to frequency and phase correct, non-inverting PWM output
  // _BV is a macro which returns the "value" of a bit contained with the corresponding byte set (COM3A1, WGM33, ect). Similar to PIND for pin 7 during the workshops.
  // '|' represents or. More info on bitwise actions found here https://www.arduino.cc/reference/en/#bitwise-operators.
  TCCR3A = _BV(COM3A1);
  TCCR3B = _BV(WGM33) | _BV(CS32);
  
  TCCR4A = _BV(COM4A1) | _BV(COM4B1) | _BV(COM4C1);
  TCCR4B = _BV(WGM43) | _BV(CS42);
}


void actuatorPneumatic::pPWM(float pwmfreq, float pwmDC1, float pwmDC2, float pwmDC3, float pwmDC4) 
{

  // set PWM frequency by adjusting ICR (top of triangle waveform)
  // F_CPU is a constant that represents the set microcontroller CPU clock speed.
  // 17.11.30   ICR3H and ICR3L – Input Capture Register 3
  // 17.11.31   ICR4H and ICR4L – Input Capture Register 4
  ICR3 = F_CPU / (prescaler * pwmfreq * 2);
  ICR4 = F_CPU / (prescaler * pwmfreq * 2);
  
  // set duty cycles
  // 17.11.20   OCR3AH and OCR3AL – Output Compare Register 3 A
  // 17.11.23   OCR4AH and OCR4AL – Output Compare Register 4 A
  // 17.11.24   OCR4BH and OCR4BL – Output Compare Register 4 B
  // 17.11.25   OCR4CH and OCR4CL – Output Compare Register 4 C
  OCR3A = (ICR4) * (pwmDC1);
  OCR4A = (ICR4) * (pwmDC2 * 0.01);
  OCR4B = (ICR4) * (pwmDC3 * 0.01);
  OCR4C = (ICR4) * (pwmDC4 * 0.01);
  
  
}

void actuatorPneumatic::actuatorLoop() 
{
  potDC1 = 0; potDC2 = 0; potDC3 = 0; potDC4 = 0;

  // if statement for manual switch override
  // LOW is a constant which represents a voltage less than 1.5V is present at the pin (5V boards) or a voltage less than 1.0V 
  // (Approx) is present at the pin (3.3V boards)
  // Extremely similar to workshop with servo
  if (digitalRead(50) == LOW) 
  {
    potDC1 = analogRead(A1)*100.0/1024.0; // scale values from pot to 0 to 100, which gets used for duty cycle percentage
  }
 
  if (digitalRead(51) == LOW)
  { 
    potDC2 = analogRead(A2)*100.0/1024.0; // scale values from pot to 0 to 100, which gets used for duty cycle percentage
  }
  if (digitalRead(52) == LOW) 
  { 
    potDC3 = analogRead(A3)*100.0/1024.0; // scale values from pot to 0 to 100, which gets used for duty cycle percentage
  }
  if (digitalRead(53) == LOW) 
  { 
    potDC4 = analogRead(A4)*100.0/1024.0; // scale values from pot to 0 to 100, which gets used for duty cycle percentage
  }

  float potPWMfq = analogRead(A7)*100.0/1024.0; // scale values from pot to 0 to 100, which gets used for frequency (Hz)
  potPWMfq = round(potPWMfq/5)*5+1; //1 to 91 Hz in increments of 5 (rounding helps to deal with noisy pot)

  // update PWM output based on the above values from pots
  pPWM(potPWMfq,potDC1,potDC2,potDC3,potDC4);

  // transfer function for sensor Honeywell ASDXRRX100PGAA5 (100 psi, 5V, A-calibration)
  // Vout = 0.8*Vsupply/(Pmax - Pmin)*(Papplied - Pmin) + 0.1*Vsupply
  // Rearrange to get: Papplied = (Vout/Vsupply - 0.1)*(Pmax - Pmin)/0.8 + Pmin;
  pressureSensor pressureSensor1(A8, 'A');
  pressureSensor pressureSensor2(A9, 'A');
  pressureSensor pressureSensor3(A10, 'A');
  pressureSensor pressureSensor4(A11, 'A');
  pressureSensor pressureSensor5(A6, 'A');

  
  float P1 = pressureSensor1.readPressureSensor();
  float P2 = pressureSensor2.readPressureSensor();
  float P3 = pressureSensor3.readPressureSensor();
  float P4 = pressureSensor4.readPressureSensor();
  float P5 = pressureSensor5.readPressureSensor();
  float potDC6 = 0;

  // potDC6 will be use to alternate the pressure for all the pneumatic muscles found connected with P5.
  // When P5 pressure is set to <= 70 it will write to pin 9 and 10, 120 psi of pressure.
  for (potDC6; P5 <= 70; potDC6++) 
  {
    analogWrite(9, potDC6 = 120);
    analogWrite(10, potDC6 = 120); 
    break; 
  delay(20); 

  }
  // When P5 is greater than 70 it will write to pin 9 and 10, 0 psi of pressure.
  for (potDC6; P5 > 70; potDC6--) 
  {
    analogWrite(9, potDC6 = 0);
    analogWrite(10, potDC6 = 0);
    break;
  delay(20); 
  } 
  // Display pressure Sensors
  displayPressureReadings(P1, P2, P3, P4, P5);


}

void actuatorPneumatic::displayPressureReadings(float P1, float P2, float P3, float P4, float P5)
{
  // print pressure readings
  Serial.print("Pumps pressure Sensor = "); Serial.print(P5); Serial.print("\t"); //This is for monitoring input pressure directly from pump.
  Serial.print("pressure sensor 1 = "); Serial.print(P1); Serial.print("\t");
  Serial.print("pressure sensor 2 = "); Serial.print(P2); Serial.print("\t");
  Serial.print("pressure sensor 3 = "); Serial.print(P3); Serial.print("\t");
  Serial.print("pressure sensor 4 = "); Serial.print(P4);
   
  Serial.println();
  
  delay(200);
}