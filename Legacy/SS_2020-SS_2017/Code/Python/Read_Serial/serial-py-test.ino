void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

int count = 0;

void loop() {
  // put your main code here, to run repeatedly:
  
  Serial.print("Hello World \n");
  delay(1000);
  if (count == 3){
    Serial.print("stop\n");
  }
  count++;
}
