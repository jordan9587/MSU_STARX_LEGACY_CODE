float ANALOG_UNITS = 4095;  // 1023 for 10 bit, 4095 for 12 bit
float ARDUINO_VOLTAGE = 5;
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
  float map_pressure = map(analog_val, 0, ANALOG_UNITS, 0, 100);    // 0v (zero bars) to 10v (100 bars). Alternatively, you could maintain 1 decimal place of accuracy in bar if you keep with int values.
  //Failed: float voltage_resolution = analog_val * (ARDUINO_VOLTAGE / ANALOG_UNITS);    // Voltage
  // This was obtained by seeing that the maximum reading from AnalogRead is 4095, which corresponds to 3.3V on A0 (and which also means 10V output from the sensor.) If you read 4095 from A0, it means you are measuring 100bar: 
  // MapBarPressure = (sensorValue2 / ANALOG_UNITS ) * 100;
  float psi_Pressure =  map_pressure * 14.503773773;    // Conversion between bar and psi
  float A_calibration = (0.8 * (3.3))/(100 - 0.36) * (psi_Pressure - 0.36) + 0.10 * 3.3;
  float B_calibration = (0.9 * (3.3))/(100 - 0.36) * (psi_Pressure - 0.36) + 0.05 * 3.3;


  Serial.println(analog_val);             // debug value
  //Serial.println(B_calibration);             // debug value
  delay(300);    // 500 ms delay
  //Serial.println(analog_val);    
  //Serial.println(map_pressure);     
  //Serial.println(psi_Pressure);
  
  // Tools > Serial Plotter
}
