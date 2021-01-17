int pinB = 2;
int pinA = 3;
int i = 0; 
int angle = 0;
int temp = 0; 
int tempB = 0;

void setup() {
  // put your setup code here, to run once:
  
  pinMode(pinB, INPUT);
  pinMode(pinA, INPUT);
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  int read_pinB = digitalRead(pinB);
  int read_pinA = digitalRead(pinA);
  //(i<80){
    //i++;
    //Serial.print("A:");
    //Serial.println(read_pinA);
    //Serial.print("B:");
    //Serial.println(read_pinB);
    //Serial.print("I: ");
    //Serial.println(i);
    Serial.println(angle);
  //}
  if(read_pinA != temp){
    temp = read_pinA;
    angle++;
  }
  if(read_pinB != tempB){
    tempB = read_pinB;
    angle++;
  }
  //The default output of A is 1 
  //The default output of B is 1 
  //If the sensor detects something B will become 0
  
}
