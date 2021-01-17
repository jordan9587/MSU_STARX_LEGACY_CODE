float rot_pos = 0;
float last_pos = 0;
int current_time = 0;
int last_time = 0;
float rot_vel = 0;
float del_rot = 0;
int del_t =  0;

//interrupt vector when DIGITAL PIN2 is written HIGH 
//from the torsion sensor
//Function: Increments the rotational position (360 deg / 128(pulses per deg) = 2.8125 deg)
// and calculates the rotational speed 

void check2() {
  if( digitalRead(4) && digitalRead(8)){
    //increment rotational position and get current time
    rot_pos += 2.8125;
    
    //Serial.print(rot_pos);
    //Serial.print('\t');
    
    del_rot = (rot_pos - last_pos);
    current_time = millis();
    del_t = current_time - last_time;
    rot_vel = (del_rot/del_t)*1000;
    last_pos = rot_pos;
    last_time = current_time;
    last_pos = rot_pos;

  } else {
    //get current position
    rot_pos -= 2.8125;
    
    //Serial.print(rot_pos);
    //Serial.print('\t');
    
    del_rot = (rot_pos - last_pos);
    current_time = millis();
    del_t = current_time - last_time;
    rot_vel = (del_rot/del_t)*1000;
    last_pos = rot_pos;
    last_time = current_time;
    last_pos = rot_pos;
    

  }

  
  //calculate rotational speed

  
  Serial.print(rot_vel);
  Serial.print('\t');
  Serial.print(del_t);
  Serial.print('\n');
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(4, INPUT);
  pinMode(8, INPUT);
  attachInterrupt(digitalPinToInterrupt(4),check2,RISING);
}

void loop() {

  if (rot_pos > 360.0){
    rot_pos = 0;
  } else if (rot_pos < 0) {
    rot_pos = 360;
  }

    
    
}
