void setup() {
  // put your setup code here, to run once:
  
  /*
  configure the power management controller (PMC) to enable
  the timer counter module. data sheet chapter 28 and 9
  */
  
  
  REG_PMC_PCER0 &= 0;
  //REG_PMC_PCER0 |= PMC_PCER0_PID27;
  REG_PMC_PCER0 |= 0x08000000;
  
  
  
  /*
  set the peripheral functions for the respecitive
  pins on port B to TIOA0 and TIOB0. These peripherals
  drive the quadriture decoder (QDEC). data sheet chapter 31,
  36, and 9
  */
  
  REG_PIOB_PDR &= 0;
  REG_PIOB_PDR |= 0x0A000000;
  
  REG_PIOB_ABSR |= 0x0A000000;
  

  /*
  set the channle mode register to capture mode
  data sheet chapter 36
  */
  
  REG_TC0_CMR0 &= 0;
  REG_TC0_CMR0 |= 0x0000500; 

  /*
  set the channle block mode register to enable both position reading
  and the QDEC and edge detection data sheet chapter 36
  */
  REG_TC0_BMR |= 0x00013000;


  /*
   Enable TC channel, data sheet chatper 36
  */
   REG_TC0_CCR0 &= 0;
   REG_TC0_CCR0 |= 0x00000005;

  Serial.begin(9600);
  
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  int16_t count = REG_TC0_CV0;
  Serial.println(count);
  //Serial.println(REG_PMC_WPSR);
  //Serial.println(REG_PMC_PCSR0);

}
