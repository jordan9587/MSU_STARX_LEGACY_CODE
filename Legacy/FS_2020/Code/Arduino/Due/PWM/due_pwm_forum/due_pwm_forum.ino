// Output a 40kHz PWM waveform at a resolution of 11-bits on pin DAC1 (PWML0)
void setup() {
  // PWM Set-up on pin: DAC1
  REG_PMC_PCER1 |= PMC_PCER1_PID36;                     // Enable PWM using peripheral clock controller
  REG_PIOB_ABSR |= PIO_ABSR_P16;                        // Set PWM pin perhipheral type A or B, in this case B
  REG_PIOB_PDR |= PIO_PDR_P16;                          // Set PWM pin to an output
  REG_PWM_CLK = PWM_CLK_PREA(0) | PWM_CLK_DIVA(1);      // Set the PWM clock rate to 84MHz (84MHz/1) 
  REG_PWM_CMR0 = PWM_CMR_CPRE_CLKA;                     // Enable single slope PWM and set the clock source as CLKA
  REG_PWM_CPRD0 = 2100;                                  // Set the PWM frequency 84MHz/40kHz = 2100 
  REG_PWM_CDTY0 = 1050;                                  // Set the PWM duty cycle 50% (2100/2=1050)
  REG_PWM_ENA = PWM_ENA_CHID0;                          // Enable the PWM channel     
}

void loop() {}
