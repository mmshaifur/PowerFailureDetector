int dev = 1, ac_voltage = -100, batt = -100;
byte gsmResetPin = A3;
byte mcuResetPin = A2;
byte interruptPin = 2;
byte powerStatus = 1;
int runTime = 0;
// variables for using interrupt
//const byte interruptPin = 2;
volatile byte state = LOW;
void setup()
{
  Serial.begin(115200);
  Serial.println("Starting up device . . .");
  pinMode(gsmResetPin, OUTPUT);
  pinMode(mcuResetPin, OUTPUT);
  digitalWrite(gsmResetPin, 1);
  digitalWrite(mcuResetPin, 1);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), powerLost, FALLING);
  devInfo(); // get device name
  gprsInit(); // initialize sim808 module communication
  runTime = millis();
}

void loop()
{

  senseing();
  sendDataToCloud();
  if (runTime > 120000)
  {
    resetSystem();
  }


}

void resetSystem()
{
  digitalWrite(gsmResetPin, 0);
  digitalWrite(mcuResetPin, 0);
}


void powerLost()
{
  sendDataToCloud();
}





