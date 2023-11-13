// site web https://flowduino.com/2021/08/24/arduino-nano-r3-nrf24l01-rf-nano/

// Emetteur

#include <Arduino.h>

#include <SPI.h>
//#include "nRF24L01.h"
#include <RF24.h>

#define PIN_LED_RED 2   // D2
#define PIN_LED_GREEN 3 // D3
#define PIN_LED_BLUE 4  // D4
#define PIN_BTN_RED 5   // D5
#define PIN_BTN_GREEN 6 // D6
#define PIN_BTN_BLUE 7  // D7

#define PIN_RF_CE 7  // D7 = Chip Enable (CE) for nRF24L01+
#define PIN_RF_CS 8 // D8 = Chip Select (CS) for nRF24L01+

#define CHANNEL_READ 987654321
#define CHANNEL_WRITE 123456789

/*
  RGBState
  We will Transmit and Receive this State data.
*/
struct RGBState
{
  bool Red;   // True if the Red button is Down
  bool Green; // True if the Green button is Down
  bool Blue;  // True if the Blue button is Down
};

RGBState currentState;
RF24 radio(PIN_RF_CE, PIN_RF_CS);
bool radioReady = false;

void setup()
{
  // Initialise Serial first
  Serial.begin(9600);
  Serial.println("Emetteur RF-NANO");
  // Pin modes
  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_LED_BLUE, OUTPUT);
  pinMode(PIN_BTN_RED, INPUT);
  pinMode(PIN_BTN_GREEN, INPUT);
  pinMode(PIN_BTN_BLUE, INPUT);

  // Configure the Radio
  int failCount = 0;

  while (!radioReady && failCount < 10)
  {
    radioReady = radio.begin();
    if (!radioReady)
    {
      failCount++;
      Serial.print("Radio Initialisation Failed ");
      Serial.print(failCount);
      Serial.println(" times.");
    }
  }

  if (!radioReady)
  {
    Serial.println("Radio could not be initialised!");
    return;
  }

  radio.setDataRate(RF24_2MBPS); // Maximum Bandwidth
  radio.setPALevel(RF24_PA_MAX); // Maximum Range

  radio.setPayloadSize(sizeof(RGBState)); // Size of the Data we will Transmit
  radio.setAutoAck(true);                 // Allows us to check if the Transmission Succeeded

  // We technically don't need to open a Reading Pipe for a Transmit-Only Device!
  radio.openReadingPipe(1, CHANNEL_READ); // For Incoming Data
  // We need to open the Writing Pipe in order to Transmit data
  radio.openWritingPipe(CHANNEL_WRITE); // For Outgoing Data
}

inline void sendState()
{
  if (!radio.write(&currentState, sizeof(RGBState)))
  {
    Serial.println("Transmission failed!"); // We output errors to Serial.
  }
}

void loop()
{
  if (!radioReady)
  {
    digitalWrite(PIN_LED_RED, HIGH); // Turn the Red LED on to show failure
    return;                          // We cannot continue if the Radio isn't working!
  }

  // We need a LOCAL State so we can Compare later!
  RGBState newState;

  // Let's populate the LOCAL State
  newState.Red = digitalRead(PIN_BTN_RED);
  newState.Green = digitalRead(PIN_BTN_GREEN);
  newState.Blue = digitalRead(PIN_BTN_BLUE);

  // Now we see if anything changed
  if (
      newState.Red != currentState.Red ||
      newState.Green != currentState.Green ||
      newState.Blue != currentState.Blue)
  {
    // Update the Current State
    currentState = newState;
    // Show the State on the Controller's LEDs
    digitalWrite(PIN_LED_RED, currentState.Red);
    digitalWrite(PIN_LED_GREEN, currentState.Green);
    digitalWrite(PIN_LED_BLUE, currentState.Blue);

    sendState(); // Send the State to all Receivers
  }
}