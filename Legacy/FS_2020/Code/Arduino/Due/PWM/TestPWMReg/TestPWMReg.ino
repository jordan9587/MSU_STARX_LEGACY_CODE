

// Arduino Parameters
const int BAU_RAT = 1000000;            // Serial baud rate
const int ADC_NUM = 12;                 // Number of ADC pins available
const int PIN_NUM = 10;                 // Number of GPIO pins available
const int PWM_FRQ = 50;                 // PWM frequency
const int PRE_SCA = 256;                // Prescaler value
const int PAC_PAR = 5;                  // Maximum number of parameters in a packet
const char PAC_DEL = ',';               // Packet delimiter
const char PAC_TER = '\r';              // Packet terminator
const int PWM_PIN[] = {5, 9, 10, 11};   // PWM pins

// Arduino Commands
const String SendADCValuesString = "ADC";
const String SetGPIODirectionString = "PIN";
const String SetGPIODirectionInString = "IN";
const String SetGPIODirectionOutString = "OUT";
const String SetPWMDutyCycleString = "PWM";
const String SetFullStopString = "STP";
const String ErrorMessageString = "ERROR";
const String StartMessageString = "START";


// Start function
void setup() {
    int bits = 255;
    Serial.begin(BAU_RAT);

    pinMode(5, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);

    TCCR1A &= ~bits;
    TCCR1B &= ~bits;
    TCCR3A &= ~bits;
    TCCR3B &= ~bits;

    TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(COM1C1);
    TCCR1B = _BV(WGM13) |  _BV(CS10);
    TCCR3A = _BV(COM3A1);
    TCCR3B = _BV(WGM33) | _BV(CS30);

    //Clock is set to clk/1
}


void loop() {

    int duty_cycle[] = {70,70,70,70};
    int frequency = PWM_FRQ;
    
      // Sets PWM frequency [F_CPU = 16 MHz]
    ICR1 = F_CPU / (2 * PRE_SCA * PWM_FRQ);
    ICR3 = 0xFFFF; //F_CPU / (2 * PRE_SCA * PWM_FRQ); //625
    // Sets PWM duty cycle
    OCR3A = 0x7FFF; //ICR3 * (duty_cycle[0] / 100.0); // 5
//    OCR1A = ICR1 * (duty_cycle[1] / 100.0); // 9
//    OCR1B = ICR1 * (duty_cycle[2] / 100.0); // 10
//    OCR1C = ICR1 * (duty_cycle[3] / 100.0); // 11
    
}
