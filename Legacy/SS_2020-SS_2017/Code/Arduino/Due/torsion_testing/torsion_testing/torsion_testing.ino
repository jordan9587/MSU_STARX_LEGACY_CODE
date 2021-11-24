int OUTPUTA_PIN = 3;  // this pin needs to support interrupts
int OUTPUTB_PIN = 2;  // no interrupt required
int PPR = 128;    // Pulses per revolution
int CPR = 192;  // Cycles per revolution (crest to trough) (1.5*PPR)
int CLOCKWISE = 1;  // direction constant
int COUNTER_CLOCKWISE = 2;  // direction constant


// volatile data type handles interrupts that modify values
volatile long inital_position = 0;
volatile long interrupt_counter = 0;

// Rotation direction: 0 = counter-clockwise; 1 = clockwise
short current_direction = CLOCKWISE;

// track last position so we know whether it's worth printing new output
long previous_position = 0;

void setup() {
  interrupts();
  Serial.begin(9600);
  // inputs
  pinMode(OUTPUTA_PIN, INPUT);
  pinMode(OUTPUTB_PIN, INPUT);
  // interrupts
  attachInterrupt(digitalPinToInterrupt(OUTPUTA_PIN), interrupt_function, RISING);  // 3
}

void loop() {
  // When display position has changed
  //int a = digitalRead(OUTPUTA_PIN);
  //Serial.println(a);
  //Serial.println(inital_position);
  //Serial.println(previous_position);
  
  if (inital_position != previous_position ) {
    Serial.println(inital_position, DEC); // Degree in which turn has change
    Serial.println("\t");
    Serial.println(current_direction == CLOCKWISE ? "counter-clockwise" : "clockwise");  // Indicating turning clockwise or anticlockwise
    Serial.println("\t");
    Serial.println(interrupt_counter, DEC);  // Amount of interrupts occouring
    previous_position = inital_position;  // Reset previous position
  }
}

void interrupt_function() {
  // read both inputs
  int a = digitalRead(OUTPUTA_PIN);
  int b = digitalRead(OUTPUTB_PIN);
  if (a == b ) {
    // b is leading a (counter-clockwise)
    inital_position--;
    current_direction = COUNTER_CLOCKWISE;
  } else {
    // a is leading b (clockwise)
    inital_position++;
    current_direction = CLOCKWISE;
  }

  // track 0 to Pulses per Revolution (Max it can turn)
  inital_position = inital_position % PPR;

  // track the number of interrupts
  interrupt_counter++;
}
