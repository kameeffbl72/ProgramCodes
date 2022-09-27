//
//    FILE: dht11_test.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.01
// PURPOSE: DHT library test sketch for DHT11 && Arduino
//     URL:
//
// Released to the public domain
//

#include <dht.h>

#include "U8glib.h"            // U8glib library for the OLED you download below
#include <Wire.h>              // Set Wire library for I2C communication

#include "max6675.h" // max6675.h file is part of the library that you should download from Robojax.com
int soPin = 8;// SO=Serial Out
int csPin = 9;// CS = chip select CS pin
int sckPin = 10;// SCK = Serial Clock pin

int soPin1 = 1;// SO=Serial Out
int csPin1 = 2;// CS = chip select CS pin
int sckPin1 = 3;// SCK = Serial Clock pin

int soPin2 = 11;// SO=Serial Out
int csPin2 = 12;// CS = chip select CS pin
int sckPin2 = 13;// SCK = Serial Clock pin


MAX6675 robojax1(sckPin, csPin, soPin);// create instance object of MAX6675
MAX6675 robojax2(sckPin1, csPin1, soPin1);
MAX6675 robojax3(sckPin2, csPin2, soPin2);

U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE); //set i2C Interface


dht DHT;

#define DHT11_PIN 7


void setup()
{
  Serial.begin(9600);
  Serial.println("DHT TEST PROGRAM ");
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHT_LIB_VERSION);
  Serial.println();
  Serial.println("Type,\tstatus,\tHumidity (%),\tTemperature (C)");
}

void loop()
{
  // READ DATA
  Serial.print("DHT11, \t");
  int chk = DHT.read11(DHT11_PIN);
  switch (chk)
  {
    case DHTLIB_OK:  
                Serial.print("OK,\t"); 
                break;
    case DHTLIB_ERROR_CHECKSUM: 
                Serial.print("Checksum error,\t"); 
                break;
    case DHTLIB_ERROR_TIMEOUT: 
                Serial.print("Time out error,\t"); 
                break;
    case DHTLIB_ERROR_CONNECT:
        Serial.print("Connect error,\t");
        break;
    case DHTLIB_ERROR_ACK_L:
        Serial.print("Ack Low error,\t");
        break;
    case DHTLIB_ERROR_ACK_H:
        Serial.print("Ack High error,\t");
        break;
    default: 
                Serial.print("Unknown error,\t"); 
                break;
  }
  // DISPLAY DATA
  int h = DHT.humidity;
  int t = DHT.temperature;
  
  int thermo = robojax1.readCelsius();
  int thermo1 = robojax2.readCelsius();
  int thermo2 = robojax3.readCelsius();
  
  Serial.print(DHT.humidity, 1);
  Serial.print(",\t");
  Serial.println(DHT.temperature, 1);

  delay(1000);

u8g.firstPage();  
do 
    {
     u8g.setFont(u8g_font_profont15);        // Set display font 1
     u8g.setPrintPos(5, 20);                 // set print position 1, 45
  u8g.println(thermo2);
  u8g.setFont(u8g_font_profont29);        // Set display font 2
  u8g.setPrintPos(1, 45);                 // set print position 1, 45
  u8g.println(t);
u8g.println(thermo2);
u8g.println(thermo);
u8g.println(thermo1);
  u8g.setFont(u8g_font_profont15);        // Set display font 1
  u8g.drawStr(1, 58, "Hamdard University");      
    }
  while( u8g.nextPage() ); 
//delay(1000);  
}
//
// END OF FILE
//
