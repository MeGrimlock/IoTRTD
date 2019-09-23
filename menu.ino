void printMenu(void)
{
    Serial.println(F("-------------------------------------"));
    Serial.println(F("[?] Print this menu"));
    //Serial.println(F("[a] read the ADC 2.8V max (FONA800 & 808)"));
    Serial.println(F("[b] read the Battery V and % charged"));
    Serial.println(F("[C] read the SIM CCID"));
    Serial.println(F("[U] Unlock SIM with PIN code"));
    Serial.println(F("[i] read RSSI"));
    Serial.println(F("[n] get Network status"));
    // Phone
    Serial.println(F("[c] make phone Call"));
    Serial.println(F("[A] get call status"));
    Serial.println(F("[h] Hang up phone"));
    Serial.println(F("[p] Pick up phone"));
    // SMS
    Serial.println(F("[N] Number of SMSs"));
    Serial.println(F("[r] Read SMS #"));
    Serial.println(F("[R] Read All SMS"));
    Serial.println(F("[d] Delete SMS #"));
    Serial.println(F("[s] Send SMS"));
    Serial.println(F("[u] Send USSD"));

    // Time
    Serial.println(F("[t] Get network time"));

    // GPRS
    Serial.println(F("[G] Enable GPRS"));
    Serial.println(F("[g] Disable GPRS"));
    Serial.println(F("[l] Query GSMLOC (GPRS)"));
    Serial.println(F("[w] Read webpage (GPRS)"));
    Serial.println(F("[W] Post to website (GPRS)"));

    Serial.println(F("[S] create Serial passthru tunnel"));
    Serial.println(F("-------------------------------------"));
    Serial.println(F(""));
}

void showTypeSIMCOM(uint8_t type){
switch (type)
  {
  case FONA800L:
    Serial.println(F("FONA 800L"));
    break;
  case FONA800H:
    Serial.println(F("FONA 800H"));
    break;
  case FONA808_V1:
    Serial.println(F("FONA 808 (v1)"));
    break;
  case FONA808_V2:
    Serial.println(F("FONA 808 (v2)"));
    break;
  case FONA3G_A:
    Serial.println(F("FONA 3G (American)"));
    break;
  case FONA3G_E:
    Serial.println(F("FONA 3G (European)"));
    break;
  default:
    Serial.println(F("???"));
    break;
  }
}
