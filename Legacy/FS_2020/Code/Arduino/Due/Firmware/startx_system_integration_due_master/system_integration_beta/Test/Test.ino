
const int PinLocationA = 2;
const int PinLocationB = 13;
const unsigned int PinA = digitalPinToBitMask(PinLocationA);
const unsigned int PinB = digitalPinToBitMask(PinLocationB); 

void setup() {
    Serial.begin(9600); 
    delay(100);
   
    // activate peripheral functions for quad pins
    REG_PIOB_PDR = PinA;     // activate peripheral function (disables all PIO functionality)
    REG_PIOB_ABSR |= PinA;   // choose peripheral option B   
    REG_PIOB_PDR = PinB;     // activate peripheral function (disables all PIO functionality)
    REG_PIOB_ABSR |= PinB;   // choose peripheral option B
   
    // activate clock for TC0
    REG_PMC_PCER0 = (1<<27);
    // select XC0 as clock source and set capture mode
    REG_TC0_CMR0 = 5;
    // activate quadrature encoder and position measure mode, no filters
    REG_TC0_BMR = (1<<9)|(1<<8)|(1<<12);
    // enable the clock (CLKEN=1) and reset the counter (SWTRG=1)
    // SWTRG = 1 necessary to start the clock!!
    REG_TC0_CCR0 = 5;   
   
void loop() {
  Serial.println(REG_TC0_CV0,DEC);
  delay(500);
}
