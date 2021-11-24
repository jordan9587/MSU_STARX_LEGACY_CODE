int QDEC_TorsionPinA = 13;
int QDEC_TorsionPinB = 2; 
int PPR = 128;    // Pulses per revolution

void setup() {
   //set pullups on torison inputs
   pinMode(QDEC_TorsionPinB, OUTPUT);
   pinMode(QDEC_TorsionPinA, OUTPUT);
   digitalWrite(QDEC_TorsionPinB, 1);
   digitalWrite(QDEC_TorsionPinA, 1);

   REG_PMC_PCER0 = (1<<27); // activate clock for TC0
   //reset counter on TC_CV == RC for REC_TC0_CMR0 = (1 << 14);
   REG_TC0_CMR0 = (1<<0)|(1<<2)|(1<<8)|(1<<10)|(1 << 14); // reset counter on index
   REG_TC0_BMR = (1<<8)|(1<<9)|(1<<12); // activate with no filters
   REG_TC0_CCR0 = 5;  //enable clock and reset counter


   
   //reset counter on TC_CV == RC
   REG_TC0_RC0 = 361;
   
   Serial.begin(9600);
   

}

void loop() {
  // put your main code here, to run repeatedly:
    /*
     // -359 => -360 => -1 => -2 => -1 => 0 => 1 => 2
     // We start counting from 0, since this is C. Once REG_TC0_CV0 or REG_TC0_QISR hits -361, 
     // we would be at -360 and the next number should be -1. If EG_TC0_CV0 or REG_TC0_QISR hits
     // -361, we would be at -360 and the next number should be 1. This should take care of any
     // extreme cases of reaching max int like before.
    int initial_angle = REG_TC0_CV0;
    int final_angle = REG_TC0_QISR;
    if (initial_angle == -361 || final_angle == -361){
      initial_angle = -1;
      final_angle = -1;
      Serial.println(initial_angle);
      Serial.print("   ");
      Serial.println(final_angle >> 8);
    } else if (initial_angle == 361 || final_angle == 361){
      initial_angle = 1;
      final_angle = 1;
      Serial.println(initial_angle);
      Serial.print("   ");
      Serial.println(final_angle >> 8);
    } else {
      initial_angle = initial_angle % 362;
      final_angle = final_angle % 362;
      Serial.println(initial_angle); 
      Serial.print("   ");
      Serial.println(final_angle>> 8);
    }
    */
    
    // -359 => 0 => -1 => -2 => -1 => 0 => 1 => 2
    // We start counting from 0, since this is C. Once REG_TC0_CV0 or REG_TC0_QISR hits -360,
    // we would be at 0 and the next number should be -1. If EG_TC0_CV0 or REG_TC0_QISR hits -360, 
    // we would be at 0, since -360 and 0 are equivalent. This should take care of any extreme cases 
    // of reaching max int like before.
    int initial_angle = REG_TC0_CV0;
    int final_angle = REG_TC0_QISR;
    if (initial_angle == -359 || final_angle == -359 || initial_angle == 359 || final_angle == 359){
      initial_angle = 0;
      final_angle = 0;
      Serial.println(initial_angle);
      Serial.print("   ");
      Serial.println(final_angle >> 8);
    } else {
      initial_angle = initial_angle % 360;
      final_angle = final_angle % 360;
      Serial.println(initial_angle); 
      Serial.print("   ");
      Serial.println(final_angle>> 8);
    }
}
