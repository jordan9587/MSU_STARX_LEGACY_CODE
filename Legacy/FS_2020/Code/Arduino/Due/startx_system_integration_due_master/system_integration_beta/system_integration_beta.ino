/* MSU STARX SOFTWARE SUB-TEAM 2019 - 2020
 * SYSTEM INTEGRATION CODE
 */

//#define encoder_cpr 128;
//#define encoder_quad (encoder_cpr*4);

//DEBUG Variables///////
bool debug = true;    //
                      //
////////////////////////

/*
 * PIN Mappings/////////////////////////////////////////////
 */                                                       //
                                                          //
//Pressure Sensor///////////////////////////////////////////
int pSensor0 = A0;                                        //
int pSensor1 = A1;                                        //
volatile float pressure0 = 0;                             //
volatile float pressure1 = 0;                             //
                                                          //
//Rotary Encoders (Torsion Sensors)/////////////////////////
//one encoder is sent to the QDEC and the second          //
int QDEC_TorsionPinA = 13;                                //
int QDEC_TorsionPinB = 2;                                 //
                                                          //
int INTRP_TorsionPinA = 3;                                //
int INTRP_TorsionPinB = 2;                                //
                                                          //
int PPR = 128;    // Pulses per revolution                //
int CPR = 192;  // Cycles per revolution                  //
int CLOCKWISE = 1;  // direction constant                 //
int COUNTER_CLOCKWISE = 2;  // direction constant         //
                                                          //
// volatile data type handles                             //
//interrupts that modify values                           //
volatile long inital_position = 0;                        //
volatile long interrupt_counter = 0;                      //
                                                          //
                                                          //
// Rotation direction: 0 = counter-clockwise;             //
//1 = clockwise                                           //
short current_direction = CLOCKWISE;                      //
                                                          //
// track last position so we know whether                 //
//it's worth printing new output                          //
long previous_position = 0;                               //
                                                          //
                                                          //
////////////////////////////////////////////////////////////

/*
 * Pwm Control Variables///////////////////////////////////
 */                                                      //
//duty cycle variables                                   //
 int chnl4_DtyCycl = 2100;                               //
 int chnl5_DtyCycl = 2100;                               //
 int chnl6_DtyCycl = 2100;                               //
 int chnl7_DtyCycl = 2100;                               //
                                                         //
//period variables                                       //
                                                         //
 int chnl4_Period = 1050;                                //
 int chnl5_Period = 1050;                                //
 int chnl6_Period = 1050;                                //
 int chnl7_Period = 1050;                                //
///////////////////////////////////////////////////////////

/*
 * Reads voltage pressure sensors and returns their pressure value
 * declared as void for now.
 */
float readPressureSensors(){
  // transfer function for sensor Honeywell ASDXRRX100PGAA5 (100 psi, 5V, A-calibration)
  // Vout = 0.8*Vsupply/(Pmax - Pmin)*(Papplied - Pmin) + 0.1*Vsupply
  // Rearrange to get: Papplied = (Vout/Vsupply - 0.1)*(Pmax - Pmin)/0.8 + Pmin;
  pressure0 = (analogRead(A0)/1024.0 - 0.1)*100.0/0.8;
  pressure1 = (analogRead(A1)/1024.0 - 0.1)*100.0/0.8;
}

/*
 * Interrupt for reading the rotary encoder
 * increments counters
 */
void interrupt_function() {
  // read both inputs
  int a = digitalRead(OUTPUTA_PIN);
  int b = digitalRead(OUTPUTB_PIN);
  if (a == b ) {
    // b is leading a (counter-clockwise)
    inital_position--;
    current_direction = COUNTER_CLOCKWISE;
  } else {
    // a is leading b (clockwise)
    inital_position++;
    current_direction = CLOCKWISE;
  }

  // track 0 to Pulses per Revolution (Max it can turn)
  inital_position = inital_position % PPR;

  // track the number of interrupts
  interrupt_counter++;
}


void setup() {
  // put your setup code here, to run once:
  
  interrupts(); //enable interrupts
  pinMode(OUTPUTA_PIN, INPUT);
  pinMode(OUTPUTB_PIN, INPUT);
  //attach interrupts
  attachInterrupt(digitalPinToInterrupt(OUTPUTA_PIN), interrupt_function, RISING); 
  /*
   * QDEC configuration 
   * DUE Datasheet chapter 36
   */
   //set pullups on torison inputs
   pinMode(QDEC_TorsionPinB, OUTPUT);
   pinMode(QDEC_TorsionPinA, OUTPUT);
   digitalWrite(QDEC_TorsionPinB, 1);
   digitalWrite(QDEC_TorsionPinA, 1);

   REG_PMC_PCER0 = (1<<27); // activate clock for TC0
   REG_TC0_CMR0 = (1<<0)|(1<<2)|(1<<8)|(1<<10) | (1 << 14); // reset counter on index
   REG_TC0_BMR = (1<<8)|(1<<9)|(1<<12); // activate with no filters
   REG_TC0_CCR0 = 5;  //enable clock and reset counter

   //reset counter on TC_CV == RC
   REG_TC0_RC0 = 360;
   
   /*
   * PWM congifuration
   * The PWM pins digital pins 9 - 6 will be reserved for
   * the solenoid valves.
   * PWML4-7 are the respective PWM channle for each digital pin
   * DUE Datasheet chapter 38 and 28
   */

   REG_PMC_PCER1 |= PMC_PCER1_PID36; //enable pwm module via PMC
   
   //set portC peripheralfunction to PWM
   REG_PIOC_ABSR |= PIO_ABSR_P21; // digital pin 9
   REG_PIOC_ABSR |= PIO_ABSR_P22; // digital pin 8
   REG_PIOC_ABSR |= PIO_ABSR_P23; // digital pin 7
   REG_PIOC_ABSR |= PIO_ABSR_P24; // digital pin 6
   
   //set portC data diraction (OUTPUT)
   REG_PIOC_PDR |= PIO_PDR_P21;
   REG_PIOC_PDR |= PIO_PDR_P22;
   REG_PIOC_PDR |= PIO_PDR_P23;
   REG_PIOC_PDR |= PIO_PDR_P24;

   //Set clock prescalers
   REG_PWM_CLK = PWM_CLK_PREA(0) | PWM_CLK_DIVA(1); 

   /*
    * channle configuration
    */
    //set channel prescalers
   REG_PWM_CMR4 = PWM_CMR_CPRE_CLKA; 
   REG_PWM_CMR5 = PWM_CMR_CPRE_CLKA; 
   REG_PWM_CMR6 = PWM_CMR_CPRE_CLKA; 
   REG_PWM_CMR7 = PWM_CMR_CPRE_CLKA; 
   //set period/frequency
   REG_PWM_CPRD4 = 2100; 
   REG_PWM_CPRD5 = 2100; 
   REG_PWM_CPRD6 = 2100; 
   REG_PWM_CPRD7 = 2100; 
   //set duty cycle
   REG_PWM_CDTY4 = 525;
   REG_PWM_CDTY5 = 1050;
   REG_PWM_CDTY6 = 525;
   REG_PWM_CDTY7 = 1050;
   //enable channles
   REG_PWM_ENA |= PWM_ENA_CHID4 |
                  PWM_ENA_CHID5 | 
                  PWM_ENA_CHID6 | 
                  PWM_ENA_CHID7;


  //Check for debug
  if (debug){Serial.begin(9600);}
  

}

void loop() {
  // put your main code here, to run repeatedly:
  //pid controller

  //DEBUG STATEMENT
  if (debug) {
    Serial.println(REG_TC0_CV0); 
    Serial.print("   ");
    Serial.println(REG_TC0_QISR >> 8);
  }

  // 
  if (inital_position != previous_position) ) {
    if (debug){
      Serial.println(inital_position, DEC); // Degree in which turn has change
      Serial.println("\t");
      Serial.println(current_direction == CLOCKWISE ? "clockwise" : "counter-clockwise");  // Indicating turning clockwise or anticlockwise
      Serial.println("\t");
    }
    //Serial.println(interrupt_counter, DEC);  // Amount of interrupts occouring
    previous_position = inital_position;  // Reset previous position
  }
}
