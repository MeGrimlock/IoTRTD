void commandLogic(char command){
  
switch (command)
  {
  case '?':
  {
    printMenu();
    break;
  }

  case 'a':
  {
    // read the ADC
    uint16_t adc = getADC();
    break;
  }

  case 'b':
  {
    // read the battery voltage and percentage
    uint16_t vbat = getBat();
    break;
  }

  case 'U':
  {
    unlockSIM();
    break;
  }

  case 'C':
  {
    getCCID();
    break;
  }

  case 'i':
  {
    getRSSI();
    break;
  }

  case 'n':
  {
    // read the network/cellular status
    getNetworkStatus();
    break;
  }

    /*** SMS ***/

  case 'N':
  {
    readNumberofSMS();
    break;
  }
  case 'r':
  {
    readSMSselector();
    break;
  }
  case 'R':
  {
    readAllSMS();
    break;
  }

  case 'd':
  {
    deleteSMSselector();
    break;
  }

  case 's':
  {
    // send an SMS!
    char sendto[21], message[141];
    flushSerial();
    Serial.print(F("Send to #"));
    readline(sendto, 20);
    Serial.println(sendto);
    Serial.print(F("Type out one-line message (140 char): "));
    readline(message, 140);
    Serial.println(message);
    if (!fona.sendSMS(sendto, message))
    {
      Serial.println(F("Failed"));
    }
    else
    {
      Serial.println(F("Sent!"));
    }

    break;
  }

    /*** Time ***/

  case 't':
  {
    // read the time
    char buffer[23];

    fona.getTime(buffer, 23); // make sure replybuffer is at least 23 bytes!
    Serial.print(F("Time = "));
    Serial.println(buffer);
    break;
  }

    /*********************************** GPRS */

  case 'g':
  {
    // turn GPRS off
    setGPRS(false);
    break;
  }
  case 'G':
  {
    // turn GPRS on
    setGPRS(true);      
    break;
  }
  case 'l':
  {
    // check for GSMLOC (requires GPRS)
    uint16_t returncode;

    if (!fona.getGSMLoc(&returncode, replybuffer, 250))
      Serial.println(F("Failed!"));
    if (returncode == 0)
    {
      Serial.println(replybuffer);
    }
    else
    {
      Serial.print(F("Fail code #"));
      Serial.println(returncode);
    }

    break;
  }
  case 'w':
  {
    // read website URL
    getWeb();
    break;
  }

  case 'W':
  {
    post2web();
    break;
  }
    /*****************************************/

  default:
  {
    Serial.println(F("Unknown command"));
    printMenu();
    break;
  }
}
    
}
