import processing.serial.*;

// Arduino Parameters
static final char PAC_DEL = ',';    // Packet delimiter
static final char PAC_TER = '\r';   // Packet terminator
static final int SER_TIM = 100;    // Serial wait time in milliseconds

// Arduino Commands
static final String SendADCValuesString = "ADC";
static final String SetGPIODirectionString = "PIN";
static final String SetGPIODirectionInString = "IN";
static final String SetGPIODirectionOutString = "OUT";
static final String SetPWMDutyCycleString = "PWM";
static final String SetFullStopString = "STP";
static final String StartMessageString = "START";
static final String ErrorMessageString = "ERROR";

String packet = "";
int sendTime = 0, getTime = 0, startTime = 0, elapsedTime = 0, count = 0;

Serial myPort;       

void setup() {
  myPort = new Serial(this, "COM8", 9600);
  startTime = millis() / 1000;
  myPort.write(StartMessageString + PAC_TER);
}

void draw() {
}

void serialEvent(Serial myPort) {
  packet = myPort.readStringUntil(PAC_TER);
  getTime = millis() - sendTime;
  elapsedTime = millis() / 1000 - startTime;
  if (packet != null) {
    println("#" + str(count++) + " " + packet + " " + str(elapsedTime) + "s" + " " + str(getTime) + "ms");
    myPort.write(SendADCValuesString + PAC_TER);                     // ADC Command = "ADC\r"
    //myPort.write(SetGPIODirectionString + ",2,OUT" + PAC_TER);       // PIN Command = "PIN,2,OUT\r"
    //myPort.write(SetPWMDutyCycleString + ",50,50,50,50" + PAC_TER);  // PWM Command = "PWM,50,50,50,50\r"
    sendTime = millis();
    delay(SER_TIM);
  }
}