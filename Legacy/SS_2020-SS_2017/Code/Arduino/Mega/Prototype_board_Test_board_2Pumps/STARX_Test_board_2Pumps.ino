///////////////////////////////////////////////
// MSU STARX Soft Robotics Testing Board
// Assisted by The Soft Robotics Toolkit group
// Arduino Micro (ATmega2560)
// All rights reserved
///////////////////////////////////////////////

int prescaler = 256; // set this to match whatever prescaler value you set in CS registers below

// intialize values for the PWM duty cycle set by pots
float potDC1 = 0;
float potDC2 = 0;
float potDC3 = 0;
float potDC4 = 0;

void setup() {

  Serial.begin(9600);

  // input pins for valve switches
  // A1-A10
  pinMode(50, INPUT);
  pinMode(51, INPUT);
  pinMode(52, INPUT);
  pinMode(53, INPUT);

  // output pins for valve PWM
  // 9-4
  /*
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  */
  
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);

  int eightOnes = 255;  // this is 11111111 in binary
  TCCR3A &= ~eightOnes;   // this operation (AND plus NOT), set the eight bits in TCCR registers to 0;
  TCCR3B &= ~eightOnes;
  TCCR4A &= ~eightOnes;
  TCCR4B &= ~eightOnes;

  // set waveform generation to frequency and phase correct, non-inverting PWM output
  TCCR3A = _BV(COM3A1);
  TCCR3B = _BV(WGM33) | _BV(CS32);
  
  TCCR4A = _BV(COM4A1) | _BV(COM4B1) | _BV(COM4C1);
  TCCR4B = _BV(WGM43) | _BV(CS42);
}

void pPWM(float pwmfreq, float pwmDC1, float pwmDC2, float pwmDC3, float pwmDC4) {

  // set PWM frequency by adjusting ICR (top of triangle waveform)
  ICR3 = F_CPU / (prescaler * pwmfreq * 2);
  ICR4 = F_CPU / (prescaler * pwmfreq * 2);
  
  // set duty cycles
  OCR3A = (ICR4) * (pwmDC1);
  OCR4A = (ICR4) * (pwmDC2 * 0.01);
  OCR4B = (ICR4) * (pwmDC3 * 0.01);
  OCR4C = (ICR4) * (pwmDC4 * 0.01);
  
  
}

void portingDC(float *PinValue, float *counter)
{
  for (*counter; *PinValue <= 70; *counter++) 
  {
    analogWrite(4, *counter = 120);
    analogWrite(5, *counter = 120); 
    analogWrite(6, *counter = 120);
    analogWrite(7, *counter = 120); 
    analogWrite(8, *counter = 120);
    analogWrite(9, *counter = 120); 
    break; 
  delay(20); 
  }
  for (*counter; *PinValue > 70; *counter--) 
  {
    analogWrite(4, *counter = 0);
    analogWrite(5, *counter = 0);
    analogWrite(6, *counter = 0);
    analogWrite(7, *counter = 0);
    analogWrite(8, *counter = 0);
    analogWrite(9, *counter = 0);
    break;
  delay(20); 
  }
}

void loop() {

  potDC1 = 0; potDC2 = 0; potDC3 = 0; potDC4 = 0;

  // if statement for manual switch override
  if (digitalRead(50) == LOW) {
  potDC1 = analogRead(A1)*100.0/1024.0; // scale values from pot to 0 to 100, which gets used for duty cycle percentage
  }
 
  if (digitalRead(51) == LOW) { potDC2 = analogRead(A2)*100.0/1024.0; }
  if (digitalRead(52) == LOW) { potDC3 = analogRead(A3)*100.0/1024.0; }
  if (digitalRead(53) == LOW) { potDC4 = analogRead(A4)*100.0/1024.0; }

  float potPWMfq = analogRead(A7)*100.0/1024.0; // scale values from pot to 0 to 100, which gets used for frequency (Hz)
  potPWMfq = round(potPWMfq/5)*5+1; //1 to 91 Hz in increments of 5 (rounding helps to deal with noisy pot)

  // update PWM output based on the above values from pots
  pPWM(potPWMfq,potDC1,potDC2,potDC3,potDC4);

  // transfer function for sensor Honeywell ASDXRRX100PGAA5 (100 psi, 5V, A-calibration)
  // Vout = 0.8*Vsupply/(Pmax - Pmin)*(Papplied - Pmin) + 0.1*Vsupply
  // Rearrange to get: Papplied = (Vout/Vsupply - 0.1)*(Pmax - Pmin)/0.8 + Pmin;

  float P6 = (analogRead(A6)/1024.0 - 0.1)*100.0/0.8;
  float P7 = (analogRead(A7)/1024.0 - 0.1)*100.0/0.8;
  float P8 = (analogRead(A8)/1024.0 - 0.1)*100.0/0.8;
  float P9 = (analogRead(A9)/1024.0 - 0.1)*100.0/0.8;
  float P10 = (analogRead(A10)/1024.0 - 0.1)*100.0/0.8;
  /* Previous Code
  float P1 = (analogRead(A8)/1024.0 - 0.1)*100.0/0.8;
  float P2 = (analogRead(A9)/1024.0 - 0.1)*100.0/0.8;
  float P3 = (analogRead(A10)/1024.0 - 0.1)*100.0/0.8;
  float P4 = (analogRead(A11)/1024.0 - 0.1)*100.0/0.8;
  */

  //This is for monitoring input pressure directly from pump.
  float P1 = (analogRead(A1)/1024.0 - 0.1)*100.0/0.8;
  float P2 = (analogRead(A2)/1024.0 - 0.1)*100.0/0.8;
  float P3 = (analogRead(A3)/1024.0 - 0.1)*100.0/0.8;
  float P4 = (analogRead(A4)/1024.0 - 0.1)*100.0/0.8;
  float P5 = (analogRead(A5)/1024.0 - 0.1)*100.0/0.8;
  float potDC1 = 0;
  float potDC2 = 0;
  float potDC3 = 0;
  float potDC4 = 0;
  float potDC5 = 0;
  /* Previous Code
  float P5 = (analogRead(A6)/1024.0 - 0.1)*100.0/0.8;
  float potDC6 = 0;
  */

  //portingDC(&P1, &potDC1);
  //portingDC(&P2, &potDC2);
  //portingDC(&P3, &potDC3);
  //portingDC(&P4, &potDC4);
  //portingDC(&P5, &potDC5);


/* Previous Code
for (potDC6; P5 <= 70; potDC6++) {
  analogWrite(8, potDC6 = 120);
  analogWrite(9, potDC6 = 120); 
  break; 
delay(20); 

}
for (potDC6; P5 > 70; potDC6--) {
  analogWrite(8, potDC6 = 0);
  analogWrite(9, potDC6 = 0);
  break;
delay(20); 
}
*/
  // print pressure readings
  Serial.print("Pumps pressure Sensor P1 = "); Serial.print(P1); Serial.print("\t"); 
  Serial.print("Pumps pressure Sensor P2 = "); Serial.print(P2); Serial.print("\t"); 
  Serial.print("Pumps pressure Sensor P3 = "); Serial.print(P3); Serial.print("\t");
  Serial.print("Pumps pressure Sensor P4 = "); Serial.print(P4); Serial.print("\t"); 
  Serial.print("Pumps pressure Sensor P5 = "); Serial.print(P5); Serial.print("\t");

  
  Serial.print("pressure sensor 1 = "); Serial.print(P1); Serial.print("\t");
  Serial.print("pressure sensor 2 = "); Serial.print(P2); Serial.print("\t");
  Serial.print("pressure sensor 3 = "); Serial.print(P3); Serial.print("\t");
  Serial.print("pressure sensor 4 = "); Serial.print(P4); Serial.print("\t");
  Serial.print("pressure sensor 5 = "); Serial.print(P5); Serial.print("\t");
  Serial.print("pressure sensor 6 = "); Serial.print(P6); Serial.print("\t");
  Serial.print("pressure sensor 7 = "); Serial.print(P7); Serial.print("\t");
  Serial.print("pressure sensor 8 = "); Serial.print(P8); Serial.print("\t");
  Serial.print("pressure sensor 9 = "); Serial.print(P9); Serial.print("\t");
  Serial.print("pressure sensor 10 = "); Serial.print(P10); Serial.print("\t");

  /* Old Code
  Serial.print("Pumps pressure Sensor P5 = "); Serial.print(P5); Serial.print("\t");
  Serial.print("pressure sensor 1 = "); Serial.print(P1); Serial.print("\t");
  Serial.print("pressure sensor 2 = "); Serial.print(P2); Serial.print("\t");
  Serial.print("pressure sensor 3 = "); Serial.print(P3); Serial.print("\t");
  Serial.print("pressure sensor 4 = "); Serial.print(P4); Serial.print("\t");
  */
  
  
   
  Serial.println();
  
delay(200);
}
