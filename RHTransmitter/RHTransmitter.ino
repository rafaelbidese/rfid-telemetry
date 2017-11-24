#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

RH_ASK driver;

char msg[12];
char idx[6] = "#S01T";

void setup()
{
    Serial.begin(9600);   // Debugging only
    if (!driver.init())
         Serial.println("init failed");
    Serial.println("init SUCCESS");
}

void loop()
{
    sprintf(msg,"%s.%04d",idx,analogRead(A0));    
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    
    delay(2000);
}
