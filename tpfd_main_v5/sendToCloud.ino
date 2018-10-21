int8_t answer;
char aux_str[200];
void gprsInit() {
  Serial.println("Starting GSM...");
  delay(3000);
  delay(3000);
  delay(5000);
  while (sendATcommand("AT+CREG?", "+CREG: 0,1", 2000) == 0);
  sendATcommand("AT+SAPBR=3,1,\"Contype\",\"GPRS\"", "OK", 2000);
  sendATcommand("AT+SAPBR=3,1,\"APN\",\"internet\"", "OK", 2000);
  sendATcommand("AT+SAPBR=3,1,\"USER\",\"\"", "OK", 2000);
  sendATcommand("AT+SAPBR=3,1,\"PWD\",\"\"", "OK", 2000);

  while (sendATcommand("AT+SAPBR=1,1", "OK", 20000) == 0)
  {
    delay(3000);
   
  }

}
void sendDataToCloud() {
  Serial.println("Trying to Send Data to Cloud");
  answer = sendATcommand("AT+HTTPINIT", "OK", 20000);
  if (answer == 1)
  {
    answer = sendATcommand("AT+HTTPPARA=\"CID\",1", "OK", 5000);
    if (answer == 1)
    {
      sprintf(aux_str, "AT+HTTPPARA=\"URL\",\"http://shaifur.com/techcom/get.php?d=%d&v=%d&b=%d", dev, ac_voltage, batt);
      Serial.print(aux_str);
      answer = sendATcommand("\"", "OK", 6000);
      if (answer == 1)
      {
        // Starts GET action
        answer = sendATcommand("AT+HTTPACTION=1", "+HTTPACTION:0,200", 10000);
        if (answer == 0)
        {

          Serial.println(F("Done!"));

        }
        else
        {
          Serial.println(F("Error getting url"));

        }

      }
      else
      {
        Serial.println(F("Error setting the url"));

      }
    }
    else
    {
      Serial.println(F("Error setting the CID"));
    }
  }
  else
  {
    Serial.println(F("Error initializating"));
  }
  sendATcommand("AT+HTTPTERM", "OK", 5000);

  delay(2000);
}

int8_t sendATcommand(char* ATcommand, char* expected_answer1, unsigned int timeout)
{

  uint8_t x = 0,  answer = 0;
  char response[100];
  unsigned long previous;

  memset(response, '\0', 100);    // Initialize the string

  delay(100);

  while ( Serial.available() > 0) Serial.read();   // Clean the input buffer

  Serial.println(ATcommand);    // Send the AT command


  x = 0;
  previous = millis();

  // this loop waits for the answer
  do {

    if (Serial.available() != 0) {
      response[x] = Serial.read();
      x++;
      // check if the desired answer is in the response of the module
      if (strstr(response, expected_answer1) != NULL)
      {
        answer = 1;
      }
    }
    // Waits for the answer with time out
  }
  while ((answer == 0) && ((millis() - previous) < timeout));

  return answer;
}

