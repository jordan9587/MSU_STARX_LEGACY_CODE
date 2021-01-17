#define encoder_cpr 32 // change to your encoder resolution
#define encoder_quad (encoder_cpr * 4); // quadrature counts is 4*CPR

void setup() {
  Serial.begin(115200);
  // set pullups on inputs
  pinMode(2, OUTPUT); //original
  pinMode(10, OUTPUT);
  
  digitalWrite(2, 1);
  
  pinMode(13, OUTPUT);//original
  pinMode(3, OUTPUT);
  
  pinMode(A6, OUTPUT);
  digitalWrite(A6, 1);

 // Setup Quadrature Encoder with index

 REG_PMC_PCER0 = (1<<27) | (1<<29); // activate clock for TC0 and TC2

 // select XC0 as clock source and set capture mode

 //REG_TC0_CMR0 = 5; // continous count
 // or
 REG_TC0_CMR0 = (1<<0)|(1<<2)|(1<<8)|(1<<10); // reset counter on index
 REG_TC2_CMR0 = (1<<0)|(1<<2)|(1<<8)|(1<<10); 

 // activate quadrature encoder and position measure mode, no filters

 REG_TC0_BMR = (1<<8)|(1<<9)|(1<<12);

 REG_TC2_BMR = (1<<8)|(1<<9)|(1<<12);
 

 // enable the clock (CLKEN=1) and reset the counter (SWTRG=1)

 REG_TC0_CCR0 = 5;  //
 REG_TC2_CCR0 = 5; 
 
}

void loop() {
//REG_TC0_CV0 Stores count from encoder
//(REG_TC0_QISR >> 8) & 0x1; gives 0 or 1 depends of direction

  int position = REG_TC0_CV0;
  int position2 = REG_TC2_CV0;
  if (position2 < 0) { position2 += encoder_quad; } 
  //Serial.println(position);
  Serial.println(position2);
  //delay(500);
}
