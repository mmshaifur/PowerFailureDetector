int dev = "def", ac_voltage = -100, batt = -100;
void setup()
{
  devInfo();
  gprsInit();
}

void loop()
{
  senseing();
  sendDataToCloud();
}





