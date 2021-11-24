// Output a 40kHz PWM waveform at a resolution of 11-bits on pin DAC1 (PWML0)
void setup() {
  // PWM Set-up on pin: DAC1
  REG_PMC_PCER1 |= PMC_PCER1_PID36;                     // Enable PWM using peripheral clock controller (THIS REMAINS UNCHANGED)

  //CHANGE THESE VALUES TO THE PORT LETTER AND PIN NUMBER DESIRED
  REG_PIOC_ABSR |= PIO_ABSR_P21;                        // Set PWM pin perhipheral type A or B, in this case B
  REG_PIOC_PDR |= PIO_PDR_P21;                          // Set PWM pin to an output

  //Set clock prescalers
  REG_PWM_CLK = PWM_CLK_PREA(0) | PWM_CLK_DIVA(1);      // Set the PWM clock rate to 84MHz (84MHz/1) 

  //CHANNLE CONFIGURATINS 
  REG_PWM_CMR4 = PWM_CMR_CPRE_CLKA;                     // Enable single slope PWM and set the clock source as CLKA
  REG_PWM_CPRD4 = 2100;                                  // Set the PWM frequency 84MHz/40kHz = 2100 
  REG_PWM_CDTY4 = 1050;                                  // Set the PWM duty cycle 50% (2100/2=1050)
  REG_PWM_ENA = PWM_ENA_CHID4;                          // Enable the PWM channel     
}

void loop() {}
