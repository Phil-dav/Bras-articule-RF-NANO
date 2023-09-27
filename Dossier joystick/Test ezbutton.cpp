/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-button-library
 *
 * This example:
 *   + uses debounce for a button.
 *   + reads state of a button
 *   + detects the pressed and released events of a button
 */

#include <ezButton.h>
ezButton button1(0);  // create ezButton object that attach to pin 0;
ezButton button2(2);  // create ezButton object that attach to pin 2;

void setup() {
  Serial.begin(9600);
  button1.setDebounceTime(50); // set debounce time to 50 milliseconds
}

void loop() {
  button1.loop(); // MUST call the loop() function first
  delay(10);
  button2.loop();
  //int btnState = button1.getState();
  //Serial.println(btnState);

  if(button1.isPressed())
    Serial.println("Bouton 1 on");

  if(button1.isReleased())
    Serial.println("Bouton 1 off");

  if (button2.isPressed())
    Serial.println("Bouton 2 on");

  if (button2.isReleased())
    Serial.println("Bouton 2 off");
}
