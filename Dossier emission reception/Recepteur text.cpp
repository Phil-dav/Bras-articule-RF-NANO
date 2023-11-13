// site web https://github.com/emakefun/rf-nano/blob/master/example/Peer2peer/Receive/Receive.ino

// Recepteur

#include <Arduino.h>

#include <SPI.h>
#include <Wire.h>
#include <RF24.h>
#include <printf.h>
RF24 ReceiveRadio(7, 8);

byte value[32];

void ReadData()
{
  uint8_t bytes;
  if (ReceiveRadio.available())
  {
    while (ReceiveRadio.available())
    {
      bytes = ReceiveRadio.getPayloadSize();
      ReceiveRadio.read(value, bytes); // 
    }
    Serial.print("ReadData");
    Serial.print(".........");
    Serial.println(value[0]); // 
  }
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  printf_begin();
  Serial.println(F("RF-NANO v3.0 Reception Test"));

  //
  // Setup and configure rf radio
  //
  ReceiveRadio.begin();
  ReceiveRadio.setAddressWidth(5);
  ReceiveRadio.openReadingPipe(1, 0xF0F0F0F066LL);
  ReceiveRadio.setChannel(115);         // 115 band above WIFI signals
  ReceiveRadio.setPALevel(RF24_PA_MAX); // MIN power low rage
  ReceiveRadio.setDataRate(RF24_1MBPS); // Minimum speed
  ReceiveRadio.startListening();
  Serial.println("Receive Setup Initialized");
  ReceiveRadio.printDetails();
  delay(500);
}

void loop()
{
  ReadData();
}