#include <PID_v1.h>
//Variables
double Setpoint, Input, Output;
//PID parameters
double Kp=0, Ki=10, Kd=0;

//Start PID instance
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

void setup()
{
  //Start a serial connection to send data by serial connection
  Serial.begin(9600);   
  //Set point : Here is the brightness target
  Setpoint = 100;
  //Turn the PID on
  myPID.SetMode(AUTOMATIC);
  //Adjust PID values
  myPID.SetTunings(Kp, Ki, Kd);
}

void loop()
{
  //Read the value from the light sensor. Analog input : 0 to 1024. We map is to a value from 0 to 255 as it's used for our PWM function.
  Input = map(analogRead(0), 0, 1024, 0, 255); 
  //PID calculation
  myPID.Compute();
  //Write the output as calculated by the PID function
  analogWrite(3,Output);
  //Send data by serial for plotting 
  Serial.print(Input);
  Serial.print(" ");
  Serial.println(Output);   
}
