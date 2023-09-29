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

#define VRX_PIN A6  // Broche Arduino Nano connectée à la broche VRX
#define VRY_PIN A7  // Arduino Nano broche connectée à la broche  VRY
#define VRX_PIN1 A5 // Broche Arduino Nano connectée à la broche VRX1
#define VRY_PIN1 A4 // Arduino Nano broche connectée à la broche  VRY1
int value_X = 0;    // La variable pour stocker la valeur de l’axe X
int value_Y = 0;    // La variable pour stocker la valeur de l’axe Y
int value_X1 = 0;   // La variable pour stocker la valeur de l’axe X1
int value_Y1 = 0;   // La variable pour stocker la valeur de l’axe Y1
// #include <ezButton.h> // gestion des boutons du joystick

// twelve servo objects can be created on most boards
Servo myservoX; // create servo object to control a servo
Servo myservoY;
Servo myservoX1;
Servo myservoY1;
void setup()
{
  myservoX.attach(8); // attache le servo sur la broche 9 à l'objet servo
  myservoY.attach(9);
  myservoX1.attach(10);
  myservoY1.attach(11);
}

void loop()
{
  value_X = analogRead(VRX_PIN); // lire les valeurs analogiques X et Y analogiques
  value_Y = analogRead(VRY_PIN);
  value_X1 = analogRead(VRX_PIN1);
  value_Y1 = analogRead(VRY_PIN1);

  value_X = map(value_X, 0, 1023, 0, 180); // met à l'echelle les valeurs de 0 à 1023 --> 0 à 180

  value_Y = map(value_Y, 0, 1023, 0, 180);

  value_X1 = map(value_X1, 0, 1023, 0, 180);

  value_Y1 = map(value_Y1, 0, 1023, 0, 180);

  myservoX.write(value_X); // dire au servo d'aller en position dans la variable 'pos'
  delay(15);               // attend 15 ms pour que le servo atteigne la position

  myservoY.write(value_Y);
  delay(15);

  myservoX1.write(value_X1);
  delay(15);

  myservoY1.write(value_Y1);
  delay(15);
}