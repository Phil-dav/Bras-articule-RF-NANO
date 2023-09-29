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

int mov_x = 90;
int mov_y = 90;
int mov_x1 = 90;
int mov_y1 = 90;
int vitesse = 15;
int pas = 5;

// twelve servo objects can be created on most boards
Servo myservoX; // create servo object to control a servo
Servo myservoY;
Servo myservoX1;
Servo myservoY1;
void setup()
{
  Serial.begin(9600);
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
  Serial.println(value_X);
  value_Y = map(value_Y, 0, 1023, 0, 180);

  value_X1 = map(value_X1, 0, 1023, 0, 180);

  value_Y1 = map(value_Y1, 0, 1023, 0, 180);

//--------------------------------- Axe X---------------------------------
  if (value_X > 95) // avance sur l'axe "X"
  {
    mov_x = mov_x + pas;
    delay(vitesse);
    if (mov_x > 179)
    {
      mov_x = 180;
    }
  }

  if (value_X < 85) // recule sur l'axe "X"
  {
    mov_x = mov_x - pas;
    delay(vitesse);
    if (mov_x < 1)
    {
      mov_x = 0;
    }
  }
  //--------------------------------- Axe Y---------------------------------
  if (value_Y > 95) // avance sur l'axe "Y"
  {
    mov_y = mov_y + pas;
    delay(vitesse);
    if (mov_y > 179)
    {
      mov_y = 180;
    }
  }

  if (value_Y < 85) // recule sur l'axe "Y"
  {
    mov_y = mov_y - pas;
    delay(vitesse);
    if (mov_y < 50)
    {
      mov_y = 50;
    }
  }
  //--------------------------------- Axe X1---------------------------------
  if (value_X1 > 95) // avance sur l'axe "X1"
  {
    mov_x1 = mov_x1 + pas;
    delay(vitesse);
    if (mov_x1 > 179)
    {
      mov_x1 = 180;
    }
  }

  if (value_X1 < 85) // recule sur l'axe "X1"
  {
    mov_x1 = mov_x1 - pas;
    delay(vitesse);
    if (mov_x1 < 1)
    {
      mov_x1 = 0;
    }
  }
  //--------------------------------- Axe Y1---------------------------------
  if (value_Y1 > 95) // avance sur l'axe "Y1"
  {
    mov_y1 = mov_y1 + pas;
    delay(vitesse);
    if (mov_y1 > 179)
    {
      mov_y1 = 180;
    }
  }

  if (value_Y1 < 85) // recule sur l'axe "Y1"
  {
    mov_y1 = mov_y1 - pas;
    delay(vitesse);
    if (mov_y1 < 1)
    {
      mov_y1 = 0;
    }
  }
  // rotation
  myservoX.write(mov_x); // dire au servo d'aller en position dans la variable 'pos'
  delay(15);             // attend 15 ms pour que le servo atteigne la position
  // pince
  myservoY.write(mov_y);
  delay(15);
// bras tourelle
  myservoX1.write(mov_x1);
  delay(15);
// bras pince
  myservoY1.write(mov_y1);
  delay(15);
}