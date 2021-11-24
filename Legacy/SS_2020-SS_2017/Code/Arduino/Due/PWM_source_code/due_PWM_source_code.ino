// Output a 40kHz PWM waveform at a resolution of 11-bits on pin DAC1 (PWML0)


int signal_pin = A0; // Reads the signal from the POT

void setup() {

  /*Heres the flow of enableing PWM
   * - Interface with the Power Manager controller (PMC) and turn power to the PWM on the pin. Only do this once.
   * - Set the clock rate. Only do this once.
   * - Toggle the peripheral control to turn the PWM function on on the pin
   * - Turn the peripherial disable register ON so the peripheral function of PWM can control the PIN
   * - Select the clock that will control the PWM cycle. I use the same clock for every channel.
   * - Set the frequency to 40kHz. Could choose others. Must do little algerba here. The dec number you enter is the x =(CLK frequency)/(Output Frequency)
   * - Enter the decimal number for the duty cylce. DIGIT = x * (%DTY_CYCLE). See examples below.
   * - Finally enable the PWM register.
   */

//############################################################################################################################################
  //PWM Set-up on pin: DAC1
  /*-------------------------------------------------------------------------------------
   * This is an example of the flow of activating a PWM channel. The channels we want open 
   * are found below.
   * --------------------------------------------------------------------------------------
  *REG_PMC_PCER1 |= PMC_PCER1_PID36;                     // Enable PWM using peripheral clock controller. Only need to do this once.
  *
  *REG_PIOB_ABSR |= PIO_ABSR_P16;                        // Set PWM pin perhipheral type A or B, in this case B
  *REG_PIOB_PDR |= PIO_PDR_P16;                          // Set PWM pin to an output ---> Peripherial disable register -> Shuts off regular input/output 
  *                                                         and turns on peripheral control, namely PWM
  *
  *REG_PWM_CLK = PWM_CLK_PREA(0) | PWM_CLK_DIVA(1);      // Set the PWM clock rate to 84MHz (84MHz/1) ----> I still don't really understand this line
  *REG_PWM_CMR0 = PWM_CMR_CPRE_CLKA;                     // Enable single slope PWM and set the clock source as CLKA. There are other clocks but I use
  *                                                         the same one everytime
  *
  *REG_PWM_CPRD0 = 2100;                                  // Set the PWM frequency 84MHz/40kHz = 2100 ---> This give a frequency of 40kHz. Algebra it.
  *
  *REG_PWM_CDTY0 = 1050;                                 // Set the PWM duty cycle 50% (2100/2=1050)
  *REG_PWM_ENA = PWM_ENA_CHID0;                          // Enable the PWM channel 
  */
//#############################################################################################################################################
  

  REG_PMC_PCER1 |= PMC_PCER1_PID36;                     // Enable PWM using peripheral clock controller. Only need to do this once.
  REG_PWM_CLK = PWM_CLK_PREA(0) | PWM_CLK_DIVA(1);      // Setting the clock rate to 84Mhz. Only do this once. 
  

 // PWM Set-up on Digital pin 9
  REG_PIOC_ABSR |= PIO_ABSR_P21;                       // Set PWM pin peripheral to type B which is PWM function
  REG_PIOC_PDR |= PIO_PDR_P21;                         // Set PWM disable register on so that it can be controlled by the peripheral functions
  REG_PWM_CMR4 = PWM_CMR_CPRE_CLKA;                    // We can keep the right hand side the same so they all use same clock. For the digit on
                                                       //      _CMRx look at the pinout diagram for PWMLx or PWMLHx. Just means PWM stars high/low
  
  REG_PWM_CPRD4 = 2100;                                // Sets the PWM frequency 84MHz/40 kHz = 2100
  REG_PWM_CDTY4 = 1050;                                // Now set the PWM duty cycle at 50% (2100/2 = 1050)
  REG_PWM_ENA = PWM_ENA_CHID4;                         // Enable the PWM channel. Again the digit is based on the pinout diagram --> PWMLx/PWMHx


  // PWM Set-up on pin: Digital pin 8
  REG_PIOC_ABSR |= PIO_ABSR_P22;                       // Set PWM pin peripheral type to type B (PWM function). Pin number is port pin from pinout 
                                                       // diagram  
  REG_PIOC_PDR |= PIO_PDR_P22;                         // Set PWM disable register to on so the the pin can be controlled by the peripheral function (PWM)
  REG_PWM_CMR5 = PWM_CMR_CPRE_CLKA;

  REG_PWM_CPRD5 = 2100;
  REG_PWM_CDTY5 = 650;
  REG_PWM_ENA = PWM_ENA_CHID5;

  // PWM Set-up on pin: Digital pin 7
  REG_PIOC_ABSR |= PIO_ABSR_P23;
  REG_PIOC_PDR  |= PIO_PDR_P23;
  REG_PWM_CMR6 = PWM_CMR_CPRE_CLKA;
  REG_PWM_CPRD6 = 2100;
  REG_PWM_CDTY6 = 1400;                               // Set a 66% duty cyle [2100 *(2/3)]
  REG_PWM_ENA = PWM_ENA_CHID6;

 // PWM Set-up pin: Digital pin 6

 REG_PIOC_ABSR |= PIO_ABSR_P24;
 REG_PIOC_PDR |= PIO_PDR_P24;
 REG_PWM_CMR7 = PWM_CMR_CPRE_CLKA;
 REG_PWM_CPRD7 = 2100;
 REG_PWM_CDTY7 = 1680;                                // Set a 80% duty cycle [2100* 0.8]
 REG_PWM_ENA = PWM_ENA_CHID7;



Serial.begin(9600);
  
}

void loop() {
/*for (int i=0;i<2100;i++){
    REG_PWM_CDTY6 = i ;

    delay(5);
  }
 * 
 */

// Control the duty cycle on digital pin 6 with pot signal
 int output = analogRead(signal_pin);   // read the signal pin

  // Map values from 0-1023 to 0-255

  int led_intensity = map(output,0,1023,0,2100);
  delay(1);

  REG_PWM_CDTY7 = led_intensity;
  
  Serial.println(output);
  }
