#define encoder_cpr 2000 // change to your encoder resolution
#define encoder_quad (encoder_cpr * 4); // quadrature counts is 4*CPR

void setup() {
  Serial.begin(115200);
  // set pullups on inputs
  pinMode(2, OUTPUT);
  digitalWrite(2, 1);
  pinMode(13, OUTPUT);
  digitalWrite(13, 1);
  pinMode(A6, OUTPUT);
  digitalWrite(A6, 1);

 // Setup Quadrature Encoder with index

 REG_PMC_PCER0 = (1<<27); // activate clock for TC0

 // select XC0 as clock source and set capture mode

 //REG_TC0_CMR0 = 5; // continous count
 // or
 REG_TC0_CMR0 = (1<<0)|(1<<2)|(1<<8)|(1<<10); // reset counter on index

 // activate quadrature encoder and position measure mode, no filters

 REG_TC0_BMR = (1<<8)|(1<<9)|(1<<12);

 // enable the clock (CLKEN=1) and reset the counter (SWTRG=1)

 REG_TC0_CCR0 = 5;  //
}

void loop() {
//REG_TC0_CV0 Stores count from encoder
//(REG_TC0_QISR >> 8) & 0x1; gives 0 or 1 depends of direction

  int position = REG_TC0_CV0;
  if (position < 0) { position += encoder_quad; } 
  Serial.println(position);
  delay(500);
}
