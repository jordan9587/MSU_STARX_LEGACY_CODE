#define CLK 3
#define DT 4
#define SW 5
int counter = 0;
int CLKstate;
int CLKLaststate; 

void setup() {
  pinMode(CLK,INPUT);
  pinMode(DT,INPUT);
  pinMode(SW,INPUT);
  pinMode(9,OUTPUT);
  Serial.begin(9600);

  CLKLaststate = digitalRead(CLK);
}

void loop() {
  CLKstate = digitalRead(CLK);
  if(CLKstate != CLKLaststate)
  {
    if(digitalRead(DT) != CLKstate)
    {
      counter++;
      counter = constrain(counter, 0, 255);
      
      }
      else
      {
        counter--;
        counter = constrain(counter, 0, 255);
        }
  
         Serial.println(counter);
  }
  
  if(digitalRead(SW) != 1)
  {
    counter=0;
    Serial.println(counter);
    }
    CLKLaststate= CLKstate;
   analogWrite(9,counter);
   }
  
