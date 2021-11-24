#include<PID_v1.h>


// Pressure Sensor Parameters
const int PS_PIN = 11;  // Pressure Sesnor Pin Number (0-15)
const int PS_CP = 1;  // Clock Prescaler (1,8,64,256,1024) [Timer 1]
const double PS_SF = 1000;  // Sampling Frequency (Hz)
// Sensor gives 1000 inputs per milisecond.

// First-Order Low Pass Filter Parameters
const double LPF_COF_H = 0.75;  // Cut off Frequency (Hz)
const double LPF_COF_R = 2*PI*LPF_COF_H;  // Cut off Frequency (rad/s)
const double LPF_ST = 1/PS_SF;  // Sampling Time (seconds)

// PWM Pin Number (6 = OC4A, 7 = OC4B, 8 = OC4C);
// Timer is 4 for all. Each pin has a subsection. They should share same frequencies.
const int PWM_CP = 8;  // Clock prescaler (1,8,64,356,1024) [Timer 4]
const double PWM_F = 50;  // Wave Frequency (Hz)
const double PWM_DC = 50;  // Duty Cycle (%)

// Sinusoidal Wave Input Parameters:
const double SW_A = 5;  // Wave Amplitude
const double SW_F = 0.5;  // Wave Frequency (Hz)
const double SW_P = 0;  // Wave Phase
const double SW_O = 25;  // Wave Offset
const double SW_S = 4;  // Discretisation Scale Factor

// PID Controller Parameters:
const double PID_KP = 200.0;  // PID Kp gain
const double PID_KI = 5.0;  // PID Ki gain
const double PID_KD = 0.05;  // PID Kd gain
const double PID_MIN = 0;  // PID Min output value
const double PID_MAX = 100;  // PID Max output value
const double PID_SP = 30;  // PID Setpoint value
const double PID_ST = (1/PS_SF)*SW_S*1000;  // PID Sampling Time (ms)

// System Vairbales:
bool updateSystem = false;
int scaleSystem = 0;
double voltageValue, pressureValue,filteredPressureValue,scaledFilteredPressureValue,dutyCycleValue,timeValue,sineWave;

// PID Pressure Controller.
// PID pressurePID(&scaledFilteredPresureValue, &dutyCycleValue, &sineWave,PID_KP,PID_KI,PID_KD, DIRECT);
PID pressurePID(&scaledFilteredPressureValue,&dutyCycleValue,&PID_SP,PID_KP,PID_KI,PID_KD,DIRECT);
//pidcontroller(&input,&output,&setpoint,kp,ki,kd,direction);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(1000000);
  
  // Pre allocated variable if blue, either 0 or 1.
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);

  // PID Controller Setupu
  pressurePID.SetMode(AUTOMATIC);  // Turn On PID Controller.
  pressurePID.SetOutputLimits(PID_MIN, PID_MAX);  // Set PID Controller Output Limit.
  pressurePID.SetSampleTime(PID_ST); // Set PID Controller Sample Time (ms)

}

void loop() {
  /*
  // put your main code here, to run repeatedly:
  digitalWrite(7, HIGH);  // Write. 7 is a digital pin with a set resolution output.
  unsigned int value =  analogRead(0);  // 10-bit resolution. Between 0 -  1023.
  analogWrite(7, 225);  // 0-255, 8 bit resolution.
  */

}
