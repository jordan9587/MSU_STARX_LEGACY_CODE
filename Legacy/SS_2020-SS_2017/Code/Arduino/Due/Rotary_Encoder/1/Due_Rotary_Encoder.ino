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
   //REG_TC0_RC0 = 361;
   
   Serial.begin(9600);
   

}

void loop() {
  // put your main code here, to run repeatedly:
    int angle_initial = REG_TC0_CV0;
    int angle_final = REG_TC0_QISR;
    if (angle_initial == -361 || angle_final == -361){
      angle_initial = 0;
      angle_final = 0;
      REG_TC0_CV0 = 0;
      REG_TC0_QISR = 0;
      Serial.println(angle_initial % 362); 
      Serial.print("   ");
      Serial.println(angle_final % 362 >> 8);
    } else {
      Serial.println(angle_initial % 362); 
      Serial.print("   ");
      Serial.println(angle_final % 362 >> 8);
    }
    
    /*
    if (angle_initial != angle_final ) {
     Serial.println(angle_initial % 361); 
     Serial.print("   ");
     Serial.println(angle_final % 361 >> 8);
    }
    */
}
