float raw_fsr = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(A5, INPUT);
  Serial.begin(9600);
}
float y,u, hp =0;
void loop() {
  // put your main code here, to run repeatedly:
  u = (float)analogRead(A5);
  y = 0.945*y+0.0549*u;
  Serial.print(y);
  Serial.print('\n');
}
