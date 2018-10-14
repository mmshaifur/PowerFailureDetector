//AC Detection
int sensorvalue0, sensorvalue1, AC_Voltage, Batt_Percent;
void senseing()
{
  sensorvalue1 = analogRead(A1);
  AC_Voltage = map (sensorvalue1, 0, 1023, 0, 300);
  sensorvalue0 = analogRead(A0);
  Batt_Percent = map (sensorvalue0, 700, 860, 0, 100);
  if (Batt_Percent > 100)
  {
    Batt_Percent = 100;
  }
   ac_voltage = AC_Voltage;
   batt = Batt_Percent;
//  volt = AC_Voltage;
//  batt = Batt_Percent;
  Serial.print("Line AC_Voltage= ");
  Serial.print(AC_Voltage);
  Serial.print(" Volt");
  Serial.print("Batt_Percent= ");
  Serial.print(Batt_Percent);
  //Serial.print(sensorvalue0);
  Serial.println(" Percent");
  delay(500);
}

