// site web https://flowduino.com/2021/08/24/arduino-nano-r3-nrf24l01-rf-nano/

// Recepteur

#include <Arduino.h>

#include <SPI.h>
#include <RF24.h>

#define PIN_LED_RED 2   // D2
#define PIN_LED_GREEN 3 // D3
#define PIN_LED_BLUE 4  // D4

#define PIN_RF_CE 7 // D7 = Chip Enable (CE) for nRF24L01+
#define PIN_RF_CS 8 // D8 = Chip Select (CS) for nRF24L01+

#define CHANNEL_READ 123456789  // Opposite of the Remote code
#define CHANNEL_WRITE 987654321 // Opposite of the Remote code

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
  Serial.println("Recepteur RF-NANO");
  // Pin modes
  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_LED_BLUE, OUTPUT);

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

  // We need to open the Reading Pipe in order to Receive data
  radio.openReadingPipe(1, CHANNEL_READ); // For Incoming Data
  // We don't need to open the Writing Pipe on a Receive-only Device
  radio.openWritingPipe(CHANNEL_WRITE); // For Outgoing Data

  radio.startListening(); // This starts the radio listening for incoming messages
}

void loop()
{
  if (!radioReady)
  {
    digitalWrite(PIN_LED_RED, HIGH); // Turn the Red LED on to show failure
    return;                          // We cannot continue if the Radio isn't working!
  }

  if (!radio.available())
  {
    return;
  } // No need to continue

  RGBState inboundState;
  radio.read(&inboundState, sizeof(RGBState));

  digitalWrite(PIN_LED_RED, inboundState.Red);
  digitalWrite(PIN_LED_GREEN, inboundState.Green);
  digitalWrite(PIN_LED_BLUE, inboundState.Blue);
}