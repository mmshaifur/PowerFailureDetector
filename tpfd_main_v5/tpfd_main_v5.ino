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
{ Serial.begin(9600);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), powerLost, LOW);
  startSystem(); // this will make two pin HIGH to keep the device running.
  devInfo(); // get device name
  gprsInit(); // initialize sim808 module communication
  runTime = millis();
}

void loop()
{

  senseing();
  sendDataToCloud();

  if (runTime > 300000) // 5min
  {
    resetSystem(); //this will reset the gsm & arduino
  }
}

void resetSystem()
{
  digitalWrite(gsmResetPin, 0);
  digitalWrite(mcuResetPin, 0);
}
void startSystem()
{
  Serial.println("Starting up device . . .");
  digitalWrite(gsmResetPin, 1);
  digitalWrite(mcuResetPin, 1);
}

void powerLost()
{
  sendDataToCloud();
}





