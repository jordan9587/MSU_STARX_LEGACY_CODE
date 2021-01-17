const int quad_A = 2;
const int quad_B = 13;
const unsigned int mask_quad_A = digitalPinToBitMask(quad_A);
const unsigned int mask_quad_B = digitalPinToBitMask(quad_B);  
const int z = 10;
volatile int reg_at_z=0;
volatile int zcount=0;
volatile int  lag;
unsigned int prevmillis;
unsigned int thismillis;
int t;
int prevt=0;
float rpm=0.0;

volatile int firsttime=1;

void setup() {
    Serial.begin(115200);  
    delay(100);
    
    // activate peripheral functions for quad pins
    REG_PIOB_PDR = mask_quad_A;     // activate peripheral function (disables all PIO functionality)
    REG_PIOB_ABSR |= mask_quad_A;   // choose peripheral option B    
    REG_PIOB_PDR = mask_quad_B;     // activate peripheral function (disables all PIO functionality)
    REG_PIOB_ABSR |= mask_quad_B;   // choose peripheral option B 
    
    // activate clock for TC0
    REG_PMC_PCER0 = (1<<27);
    // select XC0 as clock source and set capture mode
    REG_TC0_CMR0 = 5; 
    // activate quadrature encoder and position measure mode, no filters
    REG_TC0_BMR = (1<<9)|(1<<8)|(1<<12);
    // enable the clock (CLKEN=1) and reset the counter (SWTRG=1) 
    // SWTRG = 1 necessary to start the clock!!
    REG_TC0_CCR0 = 5;    
  
   pinMode(z, INPUT);       
   attachInterrupt(z, zrising, RISING);  

}    
void loop() {
  if (reg_at_z==1) {
    t=REG_TC0_CV0;    
    Serial.println((t-prevt),DEC);    
     thismillis=millis();
     rpm = 1.0/((thismillis-prevmillis)/60000.0);
    Serial.println(rpm,DEC);         
     reg_at_z=0;
     prevt=t;
     prevmillis=thismillis;
  }

}

void zrising() {
  reg_at_z=1;
}
