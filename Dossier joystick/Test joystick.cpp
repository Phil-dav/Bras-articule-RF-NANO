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
  value_Y1 = analogRead(VRY_PIN1); // imprimer les données sur Serial Monitor sur Arduino IDE
  Serial.print(" x = ");
  Serial.print(value_X);
  Serial.print(" y = ");
  Serial.print(value_Y);
  Serial.print(" : x1 = ");
  Serial.print(value_X1);
  Serial.print(" y1 = ");
  Serial.println(value_Y1);
  delay(200);
}
