int Input = A0;
int Output = 4;
double difference;
// USER INPUT
int Setpoint = map(4,0,7.25,0,255); // First parameter value between 0-7.25.



void setup() {
  Serial.begin(115200);  // initialize serial communication at 115200 bits per second

  pinMode(Input, INPUT);
  pinMode(Output, OUTPUT);
  
  //retract(); // retracts the stroke on startup
  delay(500); // Delay half a second.
}

void extend(int Setpoint, int increment) // this function enables the motor to run
{
  int delta = Setpoint + increment;
  analogWrite(Output, delta);
}

void retract(int Setpoint, int increment) // this function reverses the direction of motor
{
  int delta = Setpoint - increment;
  analogWrite(Output, delta);
}

void run_stop() // this function disables the motor
{
  
}

void loop() {
  int Input_Current = analogRead(Input);     // reads the current input value between 0 - 1023.

  difference = Setpoint - Input_Current;

  if (difference > Input_Current) // Setpoint is greater length than current length.
  {
    retract(Input, 1); // retract the stroke
  }
 
  else if (difference < Input_Current) // Setpoint is less than length of current length.
  {
    extend(Input, 1); // extend the stroke
  }
  else // Setpoint is eqivalent length than current length.
  {
    
  }
  // 5ms delay.
  delay(5);
}
