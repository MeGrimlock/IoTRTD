boolean unlockSIM()
{
    // Unlock the SIM with a PIN code
    char PIN[5];
    flushSerial();
    Serial.println(F("Enter 4-digit PIN"));
    readline(PIN, 3);
    Serial.println(PIN);
    Serial.print(F("Unlocking SIM card: "));
    boolean unlocked = fona.unlockSIM(PIN);
    if (!unlocked)
    {
        Serial.println(F("Failed"));
    }
    else
    {
        Serial.println(F("OK!"));
    }
    return unlocked;
}

uint16_t getADC()
{
    uint16_t adc = 0;
    if (!fona.getADCVoltage(&adc))
    {
        Serial.println(F("Failed to read ADC"));
    }
    else
    {
        Serial.print(F("ADC = "));
        Serial.print(adc);
        Serial.println(F(" mV"));
    }
    return adc;
}

uint16_t getBat()
{
    uint16_t vbat = 0;
    if (!fona.getBattVoltage(&vbat))
    {
        Serial.println(F("Failed to read Batt"));
    }
    else
    {
        Serial.print(F("VBat = "));
        Serial.print(vbat);
        Serial.println(F(" mV"));
    }

    if (!fona.getBattPercent(&vbat))
    {
        Serial.println(F("Failed to read Batt"));
    }
    else
    {
        Serial.print(F("VPct = "));
        Serial.print(vbat);
        Serial.println(F("%"));
    }
    return vbat;
}

uint16_t getRSSI()
{
    // read the RSSI
    uint8_t n = fona.getRSSI();
    int8_t r;

    Serial.print(F("RSSI = "));
    Serial.print(n);
    Serial.print(": ");
    if (n == 0)
        r = -115;
    if (n == 1)
        r = -111;
    if (n == 31)
        r = -52;
    if ((n >= 2) && (n <= 30))
    {
        r = map(n, 2, 30, -110, -54);
    }
    Serial.print(r);
    Serial.println(F(" dBm"));
    return r;
}

void getCCID(){
  // read the CCID and store it in CCID
  fona.getSIMCCID(replybuffer); // make sure replybuffer is at least 21 bytes!
  Serial.print(F("SIM CCID = "));
  Serial.println(replybuffer);
  strncpy(CCID, replybuffer, 21);
  Serial.println(CCID);
}
