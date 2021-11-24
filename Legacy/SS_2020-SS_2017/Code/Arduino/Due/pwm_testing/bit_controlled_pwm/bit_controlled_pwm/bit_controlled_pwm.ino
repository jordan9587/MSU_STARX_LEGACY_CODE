void setup()
{
  pinMode(12, OUTPUT);
}

void loop()
{
  /*
  analogWrite(pin, dutyCycle), whereDutyCycle is value between 0 to 255. AnalogWrite function 
  provides a simple interface to the hardware PWM, but doesn't provide any control over square
  wave/frequency.
  */
  digitalWrite(12, HIGH);
  delayMicroseconds(100); // Approximately 10% duty cycle @ 1KHz
  digitalWrite(12, LOW);
  delayMicroseconds(900);
  /*
   * This technique has the advantage that it can use any digital output pin. In addition, you 
   * have full control the duty cycle and frequency. One major disadvantage is that any interrupts 
   * will affect the timing, which can cause considerable jitter unless you disable interrupts. A 
   * second disadvantage is you can't leave the output running while the processor does something
     else. Finally, it's difficult to determine the appropriate constants for a particular duty cycle
     and frequency unless you either carefully count cycles, or tweak the values while watching an 
     oscilloscope.
   */
}
