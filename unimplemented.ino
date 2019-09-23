/**

case 'c':
{
    // call a phone!
    char number[30];
    flushSerial();
    Serial.print(F("Call #"));
    readline(number, 30);
    Serial.println();
    Serial.print(F("Calling "));
    Serial.println(number);
    if (!fona.callPhone(number))
    {
        Serial.println(F("Failed"));
    }
    else
    {
        Serial.println(F("Sent!"));
    }

    break;
}
case 'A':
{
    // get call status
    int8_t callstat = fona.getCallStatus();
    switch (callstat)
    {
    case 0:
        Serial.println(F("Ready"));
        break;
    case 1:
        Serial.println(F("Could not get status"));
        break;
    case 3:
        Serial.println(F("Ringing (incoming)"));
        break;
    case 4:
        Serial.println(F("Ringing/in progress (outgoing)"));
        break;
    default:
        Serial.println(F("Unknown"));
        break;
    }
    break;
}

case 'h':
{
    // hang up!
    if (!fona.hangUp())
    {
        Serial.println(F("Failed"));
    }
    else
    {
        Serial.println(F("OK!"));
    }
    break;
}

case 'p':
{
    // pick up!
    if (!fona.pickUp())
    {
        Serial.println(F("Failed"));
    }
    else
    {
        Serial.println(F("OK!"));
    }
    break;
}
case 'u':
  {
    // send a USSD!
    char message[141];
    flushSerial();
    Serial.print(F("Type out one-line message (140 char): "));
    readline(message, 140);
    Serial.println(message);

    uint16_t ussdlen;
    if (!fona.sendUSSD(message, replybuffer, 250, &ussdlen))
    { // pass in buffer and max len!
      Serial.println(F("Failed"));
    }
    else
    {
      Serial.println(F("Sent!"));
      Serial.print(F("***** USSD Reply"));
      Serial.print(" (");
      Serial.print(ussdlen);
      Serial.println(F(") bytes *****"));
      Serial.println(replybuffer);
      Serial.println(F("*****"));
    }
  }
  case 'S':
  {
    Serial.println(F("Creating SERIAL TUBE"));
    while (1)
    {
      while (Serial.available())
      {
        delay(1);
        fona.write(Serial.read());
      }
      if (fona.available())
      {
        Serial.write(fona.read());
      }
    }
    break;
  }
**/