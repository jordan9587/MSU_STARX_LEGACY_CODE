#include <Chrono.h>
#include <LightChrono.h>


Chrono myChrono;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
}
  float P1 = 0;
  int count = 0;
void loop() {
  // put your main code here, to run repeatedly:

  // transfer function for sensor Honeywell ASDXRRX100PGAA5 (100 psi, 5V, A-calibration)
  // Vout = 0.8*Vsupply/(Pmax - Pmin)*(Papplied - Pmin) + 0.1*Vsupply
  // Rearrange to get: Papplied = (Vout/Vsupply - 0.1)*(Pmax - Pmin)/0.8 + Pmin;
  P1 = (analogRead(A0)/1024.0 - 0.1)*100.0/0.8;
  
  Serial.print(P1);
  Serial.print(" ");
  Serial.print(myChrono.elapsed()/1000.0);
  Serial.print("\n");

  if (myChrono.elapsed()/1000.0 == 10.0){
    Serial.print("stop\n");
  }
  
}
