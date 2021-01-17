/* MSU STARX SOFTWARE SUB-TEAM 2019 - 2020
 * SYSTEM INTEGRATION CODE
 */

/*
 * PIN Mappings/////////////////////////////////////////////
 */                                                       //
                                                          //
//Pressure Sensor                                         //
int pSensor1 = A0;                                        //
int pSensor2 = A1;                                        //
                                                          //
//Rotary Encoders (Torsion Sensors)                       //
//one encoder is sent to the QDEC and the second          //
int QDEC_TorsionPinA = 13;                                //
int QDEC_TorsionPinB = 2;                                 //
                                                          //
int INTRP_TorsionPinA;      //TBD                         //
int INTRP_TorsionPinB;      //TBD                         //
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

void setup() {
  // put your setup code here, to run once:

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
   //set duryz cycle
   REG_PWM_CDTY4 = 525;
   REG_PWM_CDTY5 = 1050;
   REG_PWM_CDTY6 = 525;
   REG_PWM_CDTY7 = 1050;
   //enable channles
   REG_PWM_ENA |= PWM_ENA_CHID4 |
                  PWM_ENA_CHID5 | 
                  PWM_ENA_CHID6 | 
                  PWM_ENA_CHID7;
}

void loop() {
  // put your main code here, to run repeatedly:
  //pid controller
}
