

int pin2 = 2;
int pin3 = 3;

/*String s = "hello";
*float float_val = 3.222;
*bool t = true;

*for (int i = 0: i< 10: i++) {
  
}

int p = 0;

while (p < 10) {


 * 
 * code goes here
 */
/*  p++;
}



int fun(int k) {

   return k;
}
*/
void setup() {
  // put your setup code here, to run once:
  
  pinMode(pin2, INPUT);
  pinMode(pin3, INPUT);
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:

  int read_pin2 = digitalRead(pin2);
  int read_pin3 = digitalRead(pin3);
  Serial.println(read_pin2);
  Serial.println("BREAK A AND B HERE");
  Serial.println(read_pin3);
  //The default output of A is 1 
  //The default output of B is 1 
  //If the sensor detects something B will become 0
}
