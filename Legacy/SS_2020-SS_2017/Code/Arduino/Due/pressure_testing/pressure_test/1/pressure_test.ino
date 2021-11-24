float ANALOG_UNITS = 4095;  // 1023 for 10 bit, 4095 for 12 bit
float ARDUINO_VOLTAGE = 3.0;
int pressure_sensor_pin = A5;
/*
float analog_val = 0.0;
float voltage_resolution = 0.0;
float pressure_applied = 0.0;
float A_calibration = 0.0;
float B_calibration = 0.0;
*/
void setup()
{
  Serial.begin(9600);          //  setup serial
}


// A calibration 10% to 90%
// Output (volts) = [0.8 * V.(supply)]/[P.(max) - P.(min)] * (Pressure.(applied) - P.(min)) + 0.10 * V.(supply)
// = [0.8 * (3.3 Volts)]/[100 psi - 0.36 psi] * (Pressure.(applied) - (0.36 psi)) + 0.10 * (3.3 Volts)
// 0.36 psi is lowest 10 inches H20 conversion

// B calibration, 5% to 95%
// Output (volts) = [0.9 * V.(supply)]/[P.(max) - P.(min)] * (Pressure.(applied) - P.(min)) + 0.05 * V.(supply)
// = [0.9 * (3.3 Volts)]/[P.(max) - 0.36 psi] * (Pressure.(applied) - 0) + 0.05 * (3.3 Volts)
// 0.36 psi is lowest 10 inches H20 conversion

void loop()
{
  float analog_val = analogRead(pressure_sensor_pin);    // read the input pin
  float voltage_resolution = analog_val * (ARDUINO_VOLTAGE / ANALOG_UNITS);    // Voltage 
  float pressure_applied =  (voltage_resolution * 20) - 10;
  float A_calibration = (0.8 * (3.3))/(100 - 0.36) * (pressure_applied - 0.36) + 0.10 * 3.3;
  float B_calibration = (0.9 * (3.3))/(100 - 0.36) * (pressure_applied - 0.36) + 0.05 * 3.3;


  //Serial.println(A_calibration);             // debug value
  //Serial.println(B_calibration);             // debug value
  //delay(500);
  //Serial.println(analog_val);     // 622
  Serial.println(voltage_resolution);     // 0.48
  //Serial.println(pressure_applied);
  
  // Tools > Serial Plotter
}
