/////////////////////////////
// MSU STARX ExoSuit
// Firmware v6.0 (May-2019)
// Arduino Micro (ATmega32U4)
// All rights reserved
/////////////////////////////

// Arduino Micro Pinouts //
/////////////////////////////////////////////////////////////////////////
// ADC: A0-A5, A6-A11 (4, 6, 8, 9, 10, 12) [10-bit resolution, 0~1023] //
// PWM: 3, 5, 6, 9, 10, 11, 13 [8-bit resolution, 0~255]               //
/////////////////////////////////////////////////////////////////////////

// Arduino Parameters
const int BAU_RAT = 9600; //115200; // Serial baud rate
const int PWM_FRQ = 50;     // PWM frequency
const int PRE_SCA = 256;    // Prescaler value
const int PWM_PIN[] = {13, 9, 10, 11}; // PWM pins
int duty_cycle[] = {50,50,50,50}; // { Right hamstring, Left Quad, Left Hamstring, Right Quad}
   bool ii = false;

// Start function
void setup() {

  noInterrupts (); // no interrrupts during setup

  int bits = 255;
  Serial.begin(BAU_RAT);

  pinMode(13, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  TCCR1A &= ~bits;
  TCCR1B &= ~bits;

  TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(COM1C1);
  TCCR1B = _BV(WGM13) | _BV(CS12);

  //Timer/Counter4 used to generate PWM
  DDRC = (1<<DDC7)|(1<<DDC6);
  TCCR4A = (0<<COM4A1)|(1<<COM4A0)|(1<<PWM4A);
  TCCR4B = (1<<PSR4);
  TCCR4B = (0<<DTPS41)|(0<<DTPS40)|(1<<CS43)|(1<<CS42)|(1<<CS41)|(1<<CS40); 
  TCCR4D = (0<<WGM41)|(0<<WGM40);

  //PLL Clock registers (Disabled so code will upload)
  PLLFRQ = _BV(PLLUSB) | _BV(PLLTM1) | _BV(PDIV3) | _BV(PDIV1);
  PLLCSR = _BV(PINDIV) | _BV(PLLE);

   interrupts (); // enable global interrupts
   
  // Sets PWM frequency [F_CPU = 16 MHz]
  ICR1 = F_CPU / (2 * PRE_SCA * PWM_FRQ); //625 or 0x271
  OCR4C = ICR1 - 35; // Based on ICR1

}

/* FOR EMG */
//float EMG1,EMG2,FEMG1,FEMG2=0;
//void EMG() {
//  EMG1 = (float)analogRead(A4)*5/1024; // Read EMG sensor 1
//  EMG2 = (float)analogRead(A5)*5/1024; // Read EMG sensor 2
//  FEMG1 = 0.945*FEMG1+0.0549*EMG1; // A simple lowpass filter
//  FEMG2 = 0.945*FEMG2+0.0549*EMG2; // A simple lowpass filter
//  Serial.print(FEMG1);
//  Serial.print('\t');
//  Serial.print(FEMG2);
//  Serial.print('\n');
//
//}

void loop() {
  // Sets PWM duty cycle 
  if (ii){
    duty_cycle[0] = 100;
    duty_cycle[1] = 100;
    duty_cycle[2]= 0;
    duty_cycle[3] = 0;
    ii=false;
  }
  else {
    duty_cycle[0] = 0;
    duty_cycle[1] = 0;
    duty_cycle[2]= 100;
    duty_cycle[3] = 100;
    ii=true;
  }

  OCR4A = OCR4C * (duty_cycle[0] / 100.0); // 13
  OCR1A = ICR1 * (duty_cycle[1] / 100.0); // 9
  OCR1B = ICR1 * (duty_cycle[2] / 100.0); // 10
  OCR1C = ICR1 * (duty_cycle[3] / 100.0); // 11
  Serial.print(ii);
  Serial.print('\n');
  delay(3000);
  
}
