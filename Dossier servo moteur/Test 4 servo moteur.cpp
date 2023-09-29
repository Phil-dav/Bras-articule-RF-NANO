/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 https://www.arduino.cc/en/Tutorial/LibraryExamples/Sweep
*/
// modi le 25/09/23 par Philippe DAVID
#include "arduino.h"
#include <Servo.h>

// #include <ezButton.h> // gestion des boutons du joystick
Servo myservo; // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0; // variable to store the servo position
int Num_Moteur = 8;
void setup()
{
}

void loop()

{
  myservo.attach(Num_Moteur); // attaches the servo on pin 9 to the servo object
  for (pos = 0; pos <= 180; pos += 1)
  { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos); // tell servo to go to position in variable 'pos'
    delay(15);          // waits 15 ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1)
  {                     // goes from 180 degrees to 0 degrees
    myservo.write(pos); // tell servo to go to position in variable 'pos'
    delay(15);          // waits 15 ms for the servo to reach the position
  }
  Num_Moteur = Num_Moteur + 1;
  if (Num_Moteur == 12)
  {
    Num_Moteur = 8;
  }
}