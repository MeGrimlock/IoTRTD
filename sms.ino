int8_t readNumberofSMS(){  
  // read the number of SMS's!
  int8_t smsnum = fona.getNumSMS();
  if (smsnum < 0)
  {
    Serial.println(F("Could not read # SMS"));
  }
  else
  {
    Serial.print(smsnum);
    Serial.println(F(" SMS's on SIM card!"));
  }
  return smsnum;     
}

void readSMSselector(){
  // read an SMS
  flushSerial();
  Serial.print(F("Read #"));
  uint8_t smsn = readnumber();
  Serial.print(F("\n\rReading SMS #"));
  Serial.println(smsn);
  readSMS(smsn);
}

boolean readSMS(uint8_t smsn){
 // Retrieve SMS sender address/phone number. given the position in Memory
 
  if (!fona.getSMSSender(smsn, replybuffer, 250))
  {
    Serial.println("Failed!");
    return false;
  }
  Serial.print(F("FROM: "));
  Serial.println(replybuffer);

  // Retrieve SMS value.
  uint16_t smslen;
  if (!fona.readSMS(smsn, replybuffer, 250, &smslen))
  { // pass in buffer and max len!
    Serial.println("Failed!");
    return false;
  }

  // Store it in the buffer reserved for sending later using the HTML POST
  strncpy(lastSMS, replybuffer, 250);  
  Serial.print(F("***** SMS #"));
  Serial.print(smsn);
  Serial.print(" (");
  Serial.print(smslen);
  Serial.println(F(") bytes *****"));
  Serial.println(replybuffer);
  Serial.println(F("*****"));    
}

void readAllSMS(){
  // read all SMS
  int8_t smsnum = fona.getNumSMS();
  uint16_t smslen;
  int8_t smsn;

  if ((type == FONA3G_A) || (type == FONA3G_E))
  {
    smsn = 0; // zero indexed
    smsnum--;
  }
  else
  {
    smsn = 1; // 1 indexed
  }

  for (; smsn <= smsnum; smsn++)
  {
    Serial.print(F("\n\rReading SMS #"));
    Serial.println(smsn);
    if (!fona.readSMS(smsn, replybuffer, 250, &smslen))
    { // pass in buffer and max len!
      Serial.println(F("Failed!"));
      break;
    }
    // if the length is zero, its a special case where the index number is higher
    // so increase the max we'll look at!
    if (smslen == 0)
    {
      Serial.println(F("[empty slot]"));
      smsnum++;
      continue;
    }

    Serial.print(F("***** SMS #"));
    Serial.print(smsn);
    Serial.print(" (");
    Serial.print(smslen);
    Serial.println(F(") bytes *****"));
    Serial.println(replybuffer);
    Serial.println(F("*****"));
  }
}

boolean deleteSMSselector(){
  // delete an SMS
  flushSerial();
  Serial.print(F("Delete #"));
  uint8_t smsn = readnumber();
  return deleteSMS(smsn);
}

boolean deleteSMS(uint8_t smsn){
  Serial.print(F("\n\rDeleting SMS #"));
  Serial.println(smsn);
  boolean deleted= fona.deleteSMS(smsn);
  if (deleted)
  {
    Serial.println(F("OK!"));
  }
  else
  {
    Serial.println(F("Couldn't delete"));
  }  
  return deleted;  
}
