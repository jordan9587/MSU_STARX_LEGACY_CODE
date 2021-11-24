#include <PID_v1.h>

//Pressure Sensor Parameters
const int PS_PIN = 11; // Pressure Sensor Pin Number (0-15)
const int PS_CP = 1; // Clock Prescaler (1,8,64,256,1024) [Timer 1]
const double PS_SF = 1000; // Sampling Frequency (Hz)

//First-Order LPF Parameters
const double LPF_COF_H = 0.75; //Cut-off Frequency
const double LPF_COF_R = 2*PI*LPF_COF_H; // Cut-off Frequency (rad/s)
const double LPF_ST = 1/PS_SF; // Sampling time

//PWM Pin Number (6 = OC4A, 7 = OC4B, 8 = OC4C) \\ PWM Parameters:
const int PWM_CP = 8; //Clock Prescaler (1,8,64,256,,1024) [timer 4]
const double PWM_F = 50; //Wave frequency (Hz)
const double PWM_DC = 50; //Duty cycle (%)

//Sinusoidal Wave Parameters
const double SW_A = 5; //Wave Amplitude
const double SW_F = 0.5; //Wave Frequency (Hz)
const double SW_P = 0; //Wave Phase
const double SW_O = 25; //Wave Offset
const double SW_S = 4; //Discretization Scale Factor (ms)

//PID Controller Parameters 
const double PID_KP = 200; //PID Kp Gain
const double PID_KI = 5.0; //PID Ki Gain
const double PID_KD = 0.05; // PID Kd Gain
const double PID_MIN = 0; //PID Minimum Oupute Value
const double PID_MAX = 100; //PID Maximum Output Value
const double PID_SP = 30; //PID Setpoint Value
const double PID_ST = (1/PS_SF)*SW_S*1000; //PID Sampling Time (ms)

//System Variables
bool updateSystem = false;
int scaleSystem = 0;
double voltageValue, pressureValue,filteredPressureValue,scaledFilteredPressureValue,dutyCycleValue,timeValue,sineWave;

//PID Pressure Controller
PID pressurePID(&scaledFilteredPressureValue,&dutyCycleValue,&sineWave,PID_KP,PID_KI,PID_KD,DIRECT);
//PID pressurePID(&scaledFilteredPressureValue,&dutyCycleValue,&PID_SP,PID_KP,PID_KI,PID_KD,DIRECT);
//pidcontroller(&input,&output,&setpoint,kp,ki,kd,direction)

void setup() {
  Serial.begin(1000000);
  
  cli(); // Disable Global Interrupts
  
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);

  //PID Controller Setup
  pressurePID.SetMode(AUTOMATIC); //Turn On the PID Controller
  pressurePID.SetOutputLimits(PID_MIN,PID_MAX); //Set PID Output limits
  pressurePID.SetSampleTime(PID_ST); //Set PID Sample Time (ms)

  // Pressure Sensor Setup:
  TCCR1A = 0;  // Reset Timer/Counter Control Register - Channel A
  TCCR1B = 0;  // Reset Timer/Counter Control Register - Channel B
  TCCR1B |= (1 << WGM12);  // Enable CTC Mode. Or equals (Bitscale Operation)
  TCCR1B |= (1 << CS10);  // Set Clock Prescaler = 1. Or equals (Bitscale Operation)
  TIMSK1 |= (1 << OCIE1A);  // Enable Timer 1 Interrupt every times OCR1A reaches a value, will take a measure in the sensor. Or equals (Bitscale Operation)
  OCR1A = (F_CPU/(PS_CP * PS_SF)) - 1;  // Set output compare register.

  // Pulse Width Modulation (PWM) Setup
  TCCR4A = 0;
  TCCR4B = 0;

  // Set Clock Prescaler
  TCCR4B |= (1 << CS41);

  // Set Non Inverting/ Inverting Mode
  TCCR4A |= ( 1 << COM4A1) | ( 1 << COM4B1) | ( 1 << COM4C1);  // Set Non-Inverting PWM Modulation

  // Set Fast/ Phase and Frequency Correct PWM Mode
  TCCR4A |= ( 1 << WGM41);  // Same behaviour as _BV(WGM41) // Fast-PWM (Mode 14, TOP - ICRn) - Part 1
  TCCR4A |= ( 1 << WGM41) | ( 1 << WGM42);  // Same behaviour as _BV(WGM41) | _BV(WGM42) . (Mode 14, TOP - ICRn) - Part 2
  ICR4 = F_CPU / (PWM_CP * PWM_F) - 1;  // Fast PWM (Input Capture Register) // F_CPU = 16 Mhz
  OCR4C = ICR4 * (PWM_DC / 100.0);  // Set Output Compare Register (%)

  sei(); // Enable Global Interrupts
}

void loop() {
  if(updateSystem) {
    updateSystem = false;
    doWave();
    doPID();
    doPWM();
    doPlot();
  }
}

void doWave() {
  timeValue = timeValue + (1/PS_SF)*SW_S;  // Update Time Value (Incrementing every 0.004 s)
  sineWave = SW_A*sin(2*PI*SW_F*(timeValue) + SW_P) + SW_O;  // Update Sinusodial Wave
}

void doPID() {
  scaledFilteredPressureValue = filteredPressureValue;  // Update PID Input Value
  pressurePID.Compute();  // Compute PID OUtput Value (PWM Duty Cycle [%])
}

void doPWM(){
  OCR4C = ICR4 * (dutyCycleValue / 100.0); // Update Output Compare Register (PWM)
}

void readSensor(){
  voltageValue = analogRead(PS_PIN) * (5.0 / 1023.0); // Digital to Analog Converter.
  pressureValue = (((voltageValue / 5.0) - 0.1) * (100.0 / 0.8));  // Voltage to 
  filteredPressureValue = exp(-LPF_COF_R * LPF_ST) * filteredPressureValue + (1 - exp(-LPF_COF_R * LPF_ST)) * pressureValue; // Discretized First-Order LPF Parameters
}

void doPlot() {
  Serial.print(sineWave);
  Serial.print(" ");
  Serial.println(scaledFilteredPressureValue);
}

ISR(TIMER1_COMPA_vect){
  readSensor();
  scaleSystem++;
  if (scaleSystem >= SW_S){
    scaleSystem = 0;
    updateSystem = true;
  }
}
