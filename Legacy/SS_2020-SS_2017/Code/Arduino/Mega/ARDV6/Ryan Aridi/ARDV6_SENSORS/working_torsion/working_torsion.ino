float rot_posT1 = 0;
float last_posT1 = 0;
int current_timeT1 = 0;
int last_timeT1 = 0;
float rot_velT1 = 0;
float del_rotT1 = 0;
int del_tT1 =  0;
float rot_posT2 = 0;
float last_posT2 = 0;
int current_timeT2 = 0;
int last_timeT2 = 0;
float rot_velT2 = 0;
float del_rotT2 = 0;
int del_tT2 =  0;

//interrupt vector when DIGITAL PIN2 is written HIGH 
//from the torsion sensor
//Function: Increments the rotational position (360 deg / 128(pulses per deg) = 2.8125 deg)
// and calculates the rotational speed 

void checkT1() {
  if( digitalRead(4) && digitalRead(8)){
    //increment rotational position and get current time
    rot_posT1 += 2.8125;  
    del_rotT1 = (rot_posT1 - last_posT1);
    current_timeT1 = millis();
    del_tT1 = current_timeT1 - last_timeT1;
    rot_velT1 = (del_rotT1/del_tT1)*1000;
    last_posT1 = rot_posT1;
    last_timeT1 = current_timeT1;
    last_posT1 = rot_posT1;
      Serial.println("TORSION SENSOR 1");
      Serial.print(rot_posT1);
    Serial.print('\t');
  } else {
    //get current position
    rot_posT1 -= 2.8125;
    
    Serial.print(rot_posT1);
    Serial.print('\t');
    
    del_rotT1 = (rot_posT1 - last_posT1);
    current_timeT1 = millis();
    del_tT1 = current_timeT1 - last_timeT1;
    rot_velT1 = (del_rotT1/del_tT1)*1000;
    last_posT1 = rot_posT1;
    last_timeT1 = current_timeT1;
    last_posT1 = rot_posT1;
  }
  //calculate rotational speed
//  Serial.println("TORSION SENSOR 1");
  Serial.print(rot_velT1);
  Serial.print('\t');
  Serial.print(del_tT1);
  Serial.print('\n');
}
void checkT2() {
  if( digitalRead(5) && digitalRead(6)){
    //increment rotational position and get current time
    rot_posT2 += 2.8125;  
    del_rotT2 = (rot_posT2 - last_posT2);
    current_timeT2 = millis();
    del_tT2 = current_timeT2 - last_timeT2;
    rot_velT2 = (del_rotT2/del_tT2)*1000;
    last_posT2 = rot_posT2;
    last_timeT2 = current_timeT2;
    last_posT2 = rot_posT2;
  } else {
    //get current position
    rot_posT2 -= 2.8125;
    del_rotT2 = (rot_posT2 - last_posT2);
    current_timeT2 = millis();
    del_tT2 = current_timeT2 - last_timeT2;
    rot_velT2 = (del_rotT2/del_tT2)*1000;
    last_posT2 = rot_posT2;
    last_timeT2 = current_timeT2;
    last_posT2 = rot_posT2;
  }
  //calculate rotational speed
//  Serial.println("TORSION SENSOR 2");
//  Serial.print(rot_velT2);
//  Serial.print('\t');
//  Serial.print(del_tT2);
//  Serial.print('\n');
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(4, INPUT);
  pinMode(8, INPUT);
  pinMode(6, INPUT);
  pinMode(5, INPUT);
}

void loop() {
  checkT1();
  if (rot_posT1 > 360.0){
    rot_posT1 = 0;
  } else if (rot_posT1 < 0) {
    rot_posT1 = 360;
  }
  //delay(1000);
  checkT2();
  if (rot_posT2 > 360.0){
    rot_posT2 = 0;
  } else if (rot_posT2 < 0) {
    rot_posT2 = 360;
  }
    
}
