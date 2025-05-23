//Aitor Gómez Ogueta UO294066
//Diego García González UO294255
//Ejercicio actuador lineal 2.

#include <Servo.h>

const int joystickXPin = A0;
Servo servo;
const int pinServo = 9;

void setup() {
  Serial.begin(9600);
  servo.attach(pinServo);
}

void loop() {
  int joystickXValue = analogRead(joystickXPin);
  Serial.print("Joystick X: ");
  Serial.println(joystickXValue);

  if (joystickXValue < 50) {
    servo.write(180);
  } else if (joystickXValue >= 50 && joystickXValue < 520) {
    servo.write(110);
  } else if (joystickXValue >= 520 && joystickXValue <= 560) {
    servo.write(90);
  } else if (joystickXValue > 560 && joystickXValue <= 1000) {
    servo.write(80);
  } else {
    servo.write(0);
  }

  delay(100);
}

