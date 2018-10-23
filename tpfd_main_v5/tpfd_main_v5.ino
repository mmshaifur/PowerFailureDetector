int dev = 1, ac_voltage = -100, batt = -100;
byte interruptPin = 2;
byte powerStatus = 1;
long int runTime;
// variables for using interrupt
//const byte interruptPin = 2;
volatile byte state = LOW;
void setup()
{
  Serial.begin(115200);
  Serial.println("Starting up device . . .");
  pinMode(A3, OUTPUT); //gsm reset pin
  digitalWrite(A3, HIGH);
  pinMode(interruptPin, INPUT_PULLUP);
  //  attachInterrupt(digitalPinToInterrupt(interruptPin), powerLost, FALLING);
  runTime = 0;
  devInfo(); // get device name
  delay(8000);
  gprsInit(); // initialize sim808 module communication
}

void loop()
{
  runTime = millis();
  senseing();
  gprsInit();
  sendDataToCloud();


  Serial.println(runTime);
  if (runTime > 60000)
  {
    Serial.println("Restarting up device . . .");
    resetSystem();
  }
}

void resetSystem()
{
  runTime = 0;

  digitalWrite(A3, LOW);
  delay(500);
  digitalWrite(A3, HIGH);
  software_Reset();
}


void software_Reset() // Restarts program from beginning but does not reset the peripherals and registers
{
  asm volatile ("  jmp 0");
}


void powerLost()
{
  sendDataToCloud();
}
