// site web https://github.com/emakefun/rf-nano/blob/master/example/Peer2peer/Send/Send.ino

// Emetteur
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <RF24.h>
#include <printf.h>
RF24 SendRadio(7, 8);

int value;

void WriteData()
{
  value = random(255);                     // value
  SendRadio.openWritingPipe(0xF0F0F0F066LL); // Sends data on this 40-bit address
  SendRadio.write(&value, sizeof(value));  // 
  Serial.print("WriteData");
  Serial.print(".........");
  Serial.println(value);
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  printf_begin();
  Serial.println(F("RF-NANO v3.0 emision Test"));

  //
  // Setup and configure rf radio
  //
  // Get into standby mode

  SendRadio.begin();
  SendRadio.setAddressWidth(5);
  SendRadio.openWritingPipe(0xF0F0F0F066LL);
  SendRadio.setChannel(115);         // 115 band above WIFI signals
  SendRadio.setPALevel(RF24_PA_MAX); // MIN power low rage
  SendRadio.setDataRate(RF24_1MBPS); // Minimum speed
  SendRadio.stopListening();         // Stop Receiving and start transminitng
  Serial.print("Send Setup Initialized");
  SendRadio.printDetails();
  delay(500);
}

void loop()
{
  WriteData();
  delay(1000);
}