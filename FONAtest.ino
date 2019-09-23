
#include "Adafruit_FONA.h"
#include <avr/wdt.h>

#define FONA_RX 2
#define FONA_TX 3
#define FONA_RST 4

// GET
char campaignsLink[] = "http://www.federicodonner.com/messagewatcher_api/public/api/campaigns";

// POST
char reportLink[] = "http://www.federicodonner.com/messagewatcher_api/public/api/report";
char heartbeatLink[] = "http://www.federicodonner.com/messagewatcher_api/public/api/keepalive";

// Data from SIM and Modem
char IMEI[16];
char CCID[21];


// this is a large buffer for replies from the SIMCOM chip
char replybuffer[255];
char lastSMS [255];

int8_t pendingSMS = 0;

// Hardware serial is also possible!
HardwareSerial *fonaSerial = &Serial2;

Adafruit_FONA fona = Adafruit_FONA(FONA_RST);

uint8_t readline(char *buff, uint8_t maxbuff, uint16_t timeout = 0);

uint8_t type;

void setup()
{
  wdt_disable();
  
  Serial.begin(115200);
  Serial.println(F("RTD - IoT sniffer .- Telefonica Uruguay"));
  Serial.println(F("Initializing....(May take 3 seconds)"));
  Serial.println(F("Watchdog timer: 8 seconds"));
  power_ON_Down();
  fonaSerial->begin(19200);
  if (!fona.begin(*fonaSerial))
  {
    Serial.println(F("Couldn't find FONA"));
    power_ON_Down();
  }
  type = fona.type();
  Serial.println(F("FONA is OK"));
  Serial.print(F("Found "));
  showTypeSIMCOM(type);
  
  // Print module IMEI number.
  char imei[16] = {0}; // MUST use a 16 character buffer for IMEI!
  uint8_t imeiLen = fona.getIMEI(imei);
  if (imeiLen > 0)
  {
    Serial.print("Module IMEI: ");
    Serial.println(imei);
    strncpy(IMEI, imei, 16);
  }

  fona.setGPRSNetworkSettings(F("webapn.movistar.com.uy"), F("movistar"), F("movistar"));
  //fona.setHTTPSRedirect(true);
  delay(5000);
  wdt_enable(WDTO_8S);
  setGPRS(false);   
  // Stay here until GPRS is available
  wdt_reset();
  while(!setGPRS(true)){        
    delay(2500);    
  }

  // Show device data
  // Serial.println("IMEI: %s CCID:%s",IMEI,CCID);
  // printMenu();
  wdt_reset();
  getNetworkStatus();
  
}


unsigned long period = 3000;
unsigned long startTime = 0;

// Control  how often we send the heartbeat. Since the loop occurs once every 3 seconds, an hour would be 60 minutes x 60 seconds / 3 seconds per loop = 1.200
// Hour: 1.200 , Half an hour: 600, 15 minutes: 300 

const int heartBeatPeriod = 600;
int beats=0;

void loop()
{
   wdt_reset();
  Serial.println(F("Command>"));
  // Await for serial command
  startTime=millis();
  while (!Serial.available())
  {
    if (fona.available())
    {
      Serial.write(fona.read());
    }else{
      // Code to be processed while no serial commands are received on a periodic basis.
      if((millis()-startTime>period)){
        //----------Here goes all the FUN from the IoT team----------
                
        // getURL(campaignsLink);
        wdt_reset();
        delay(100); 
               
        if(beats>=heartBeatPeriod){
          postURL(heartbeatLink,"Gg");      
          beats=0;
        }else{
          beats++;  
        }
        wdt_reset();  
        
        delay(100);
        pendingSMS=readNumberofSMS();
        if(pendingSMS>0){
          Serial.println("Got 1 or more pending SMS");               
          while(pendingSMS>0){
            readSMS(pendingSMS);
            pendingSMS--;
            Serial.println("SMS:");
            Serial.println(lastSMS);                                    
            postURL(reportLink,lastSMS);
          }
        }
        wdt_reset();
        
        //-----------------------------------------------------------      
        startTime=millis();
      }
    }
    wdt_reset();
  }
  // Process command
  char command = Serial.read();
  Serial.println(command);
  commandLogic(command);
  // flush input
  flushSerial();

  //Await for SIM800 to respond
  while (fona.available())
  {
    Serial.write(fona.read());
  }
}
