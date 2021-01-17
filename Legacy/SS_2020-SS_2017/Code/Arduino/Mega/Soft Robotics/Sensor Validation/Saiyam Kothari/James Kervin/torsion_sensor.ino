/* Orange: B output on data sheet
 *  Green: Ground
 *  Yellow: A output on data sheet
 *  Red: 5 VoltDC
 */

#define pinB 2 // color wire orange
#define pinA 3 // color wire yellow
#define light 4


int i = 0; 
int angle = 0;
int temp = 0; 
int tempB = 0;

void setup() {
  
  pinMode(pinB, INPUT);
  pinMode(pinA, INPUT);
  pinMode(light, OUTPUT);
  Serial.begin(9600);
  
}

void loop() {
  int read_pinB = digitalRead(pinB);
  int read_pinA = digitalRead(pinA);

  Serial.println(angle);
  if(read_pinA != temp){
    temp = read_pinA;
    angle++;
    digitalWrite(light, HIGH);
  }
// the next if statment should in therory repeatdedly say the direction it is turning based on which one changes first

if(tempB = read_pinB && read_pinA != temp){
  Serial.println("Clockwise" + angle); }
else{
  Serial.println("not counter clockwise" + angle);
}


  if(read_pinB != tempB){
    tempB = read_pinB;
    angle++;
    digitalWrite(light, HIGH);
  }

  if(read_pinB == tempB && read_pinA == temp){
    digitalWrite(light, LOW);
  }
  //The default output of A is 1 
  //The default output of B is 1 
  //If the sensor detects something B will become 0
  
}
