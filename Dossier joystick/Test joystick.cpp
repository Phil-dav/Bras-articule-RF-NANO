// site web https://newbiely.com/tutorials/arduino-nano/arduino-nano-joystick

#include <Arduino.h>
/**Ce code Arduino Nano  a été développé par newbiely.com * * Ce code Arduino  Nano est mis à la disposition du public sans //aucunerestriction * *  Pour des instructions complètes et des schémas de câblage, veuillez visiter: *  https://newbiely.com/tutorialsarduino-nano/arduino-nano-joystick **/

#define VRX_PIN A6  // Broche Arduino Nano connectée à la broche VRX
#define VRY_PIN A7  // Arduino Nano broche connectée à la broche  VRY
#define VRX_PIN1 A5 // Broche Arduino Nano connectée à la broche VRX1
#define VRY_PIN1 A4 // Arduino Nano broche connectée à la broche  VRY1
int value_X = 0;    // La variable pour stocker la valeur de l’axe X
int value_Y = 0;    // La variable pour stocker la valeur de l’axe Y
int value_X1 = 0;   // La variable pour stocker la valeur de l’axe X1
int value_Y1 = 0;   // La variable pour stocker la valeur de l’axe Y1
void setup()
{
  Serial.begin(9600);
}

void loop()
{
  value_X = analogRead(VRX_PIN); // read analog X et Y analog values
  value_Y = analogRead(VRY_PIN);
  value_X1 = analogRead(VRX_PIN1);
  value_Y1 = analogRead(VRY_PIN1);         // imprimer les données sur Serial Monitor sur Arduino IDE
  value_X = map(value_X, 0, 1023, 0, 180); // met à l'echelle les valeurs de 0 à 1023 --> 0 à 180
  Serial.print(" x = ");
  Serial.print(value_X);
  value_Y = map(value_Y, 0, 1023, 0, 180);
  Serial.print(" y = ");
  Serial.print(value_Y);
  value_X1 = map(value_X1, 0, 1023, 0, 180);
  Serial.print(" : x1 = ");
  Serial.print(value_X1);
  value_Y1 = map(value_Y1, 0, 1023, 0, 180);
  Serial.print(" y1 = ");
  Serial.println(value_Y1);
  delay(200);
}
