int QDEC_TorsionPinA = 13;
int QDEC_TorsionPinB = 2; 

void setup() {
   //set pullups on torison inputs
   pinMode(QDEC_TorsionPinB, OUTPUT);
   pinMode(QDEC_TorsionPinA, OUTPUT);
   digitalWrite(QDEC_TorsionPinB, 1);
   digitalWrite(QDEC_TorsionPinA, 1);

   REG_PMC_PCER0 = (1<<27); // activate clock for TC0
   //reset counter on TC_CV == RC
   REG_TC0_CMR0 = (1<<0)|(1<<2)|(1<<8)|(1<<10)|(1 << 14); // reset counter on index
   REG_TC0_BMR = (1<<8)|(1<<9)|(1<<12); // activate with no filters
   REG_TC0_CCR0 = 5;  //enable clock and reset counter

   REG_TC0_RC0 = 360;
   
   Serial.begin(9600);
   

}

void loop() {
  // put your main code here, to run repeatedly:
    Serial.println(REG_TC0_CV0); 
    Serial.print("   ");
    Serial.println(REG_TC0_QISR >> 8);

}
