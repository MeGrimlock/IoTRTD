void getURL(char* url){
  uint16_t statuscode;
  int16_t length;
  wdt_reset();
  if (!fona.HTTP_GET_start(url, &statuscode, (uint16_t *)&length))
  {
      Serial.println("Failed!");
      exit(1);
  }
  wdt_reset();
  while (length > 0)
  {
      unsigned long timeIn = millis();
      unsigned long timeOut = 3000;
      while (fona.available() && (millis()-timeIn < timeOut) )
      {
        char c = fona.read();
        Serial.write(c);          
        length--;
        wdt_reset();
      }
  }
  Serial.println(F("\n****"));
  fona.HTTP_GET_end();  
}

void postURL(char *url, char *data){
  // Post data to website
  uint16_t statuscode;
  int16_t length;  

  flushSerial();  
  Serial.println(F("****"));
  wdt_reset();
  if (!fona.HTTP_POST_start(url, F("text/plain"), (uint8_t *)data, strlen(data), &statuscode, (uint16_t *)&length))
  {
      Serial.println("Failed!");
      return;
  }
  while (length > 0)
  {
      while (fona.available())
      {
          char c = fona.read();
          Serial.write(c);
          length--;
      }
  }
  Serial.println(F("\n****"));
  fona.HTTP_POST_end();
}


void getWeb()
{
    uint16_t statuscode;
    int16_t length;
    char url[80];

    flushSerial();
    Serial.println(F("NOTE: in beta! Use small webpages to read!"));
    Serial.println(F("URL to read (e.g. wifitest.adafruit.com/testwifi/index.html):"));
    Serial.print(F("http://"));
    wdt_reset();
    readline(url, 79);
    Serial.println(url);

    Serial.println(F("****"));
    if (!fona.HTTP_GET_start(url, &statuscode, (uint16_t *)&length))
    {
        Serial.println("Failed!");
        exit(1);
    }
    while (length > 0)
    {
        unsigned long timeIn = millis();
        unsigned long timeOut = 3000;
        while (fona.available() && (millis()-timeIn < timeOut) )
        {
            char c = fona.read();

            // Serial.write is too slow, we'll write directly to Serial register!
            #if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
              loop_until_bit_is_set(UCSR0A, UDRE0); /* Wait until data register empty. */
              UDR0 = c;
            #else
              Serial.write(c);
            #endif
            length--;
            if (!length)
                exit(1);
        }
    }
    Serial.println(F("\n****"));
    fona.HTTP_GET_end();
}

void post2web()
{
    // Post data to website
    uint16_t statuscode;
    int16_t length;
    char url[80];
    char data[80];

    flushSerial();
    Serial.println(F("NOTE: in beta! Use simple websites to post!"));
    Serial.println(F("URL to post (e.g. httpbin.org/post):"));
    Serial.print(F("http://"));
    readline(url, 79);
    Serial.println(url);
    Serial.println(F("Data to post (e.g. \"foo\" or \"{\"simple\":\"json\"}\"):"));
    readline(data, 79);
    Serial.println(data);

    Serial.println(F("****"));
    if (!fona.HTTP_POST_start(url, F("text/plain"), (uint8_t *)data, strlen(data), &statuscode, (uint16_t *)&length))
    {
        Serial.println("Failed!");
        exit(1);
    }
    while (length > 0)
    {
        while (fona.available())
        {
            char c = fona.read();

#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
            loop_until_bit_is_set(UCSR0A, UDRE0); /* Wait until data register empty. */
            UDR0 = c;
#else
            Serial.write(c);
#endif

            length--;
            if (!length)
                exit(1);
        }
    }
    Serial.println(F("\n****"));
    fona.HTTP_POST_end();
}
