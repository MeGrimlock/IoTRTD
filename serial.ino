void flushSerial()
{
    while (Serial.available())
        Serial.read();
}

char readBlocking()
{
    while (!Serial.available())
        ;
    return Serial.read();
}
uint16_t readnumber()
{
    uint16_t x = 0;
    char c;
    while (!isdigit(c = readBlocking()))
    {
        //Serial.print(c);
    }
    Serial.print(c);
    x = c - '0';
    while (isdigit(c = readBlocking()))
    {
        Serial.print(c);
        x *= 10;
        x += c - '0';
    }
    return x;
}

uint8_t readline(char *buff, uint8_t maxbuff, uint16_t timeout)
{
    uint16_t buffidx = 0;
    boolean timeoutvalid = true;
    if (timeout == 0)
        timeoutvalid = false;

    while (true)
    {
        if (buffidx > maxbuff)
        {
            //Serial.println(F("SPACE"));
            break;
        }

        while (Serial.available())
        {
            char c = Serial.read();

            //Serial.print(c, HEX); Serial.print("#"); Serial.println(c);

            if (c == '\r')
                continue;
            if (c == 0xA)
            {
                if (buffidx == 0) // the first 0x0A is ignored
                    continue;

                timeout = 0; // the second 0x0A is the end of the line
                timeoutvalid = true;
                break;
            }
            buff[buffidx] = c;
            buffidx++;
        }

        if (timeoutvalid && timeout == 0)
        {
            //Serial.println(F("TIMEOUT"));
            break;
        }
        delay(1);
    }
    buff[buffidx] = 0; // null term
    return buffidx;
}
