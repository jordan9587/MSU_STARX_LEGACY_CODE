void setup() {
  // put your setup code here, to run once:
  pinMode(A7, INPUT);
  Serial.begin(9600);
}
float u,y=0;
void EMG() {
  
  u = (float)analogRead(A7)*5/1024;
  y = 0.945*y+0.0549*u;
  Serial.print(u);
  Serial.print('\t');
  Serial.print(y);
  Serial.print('\n');

}
