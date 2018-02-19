#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile


//RH_ASK driver(BAUD, RX, TX);

RH_ASK driver;

void setup()
{
    Serial.begin(115200); // Debugging only
    if (!driver.init())
         Serial.println("init failed");
}

void loop()
{
    uint8_t buf[12];
    uint8_t buflen = sizeof(buf);
    if (driver.recv(buf, &buflen)) // Non-blocking
    {
      // Message with a good checksum received, dump it.
      Serial.println((char*)buf);         
    }
}
