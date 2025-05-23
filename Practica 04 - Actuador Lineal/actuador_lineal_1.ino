//Aitor Gómez Ogueta UO294066
//Diego García González UO294255
//Ejercicio actuador lineal 1.

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

  if (joystickXValue > 560) {
    servo.write(0);
  } else if (joystickXValue < 520) {
    servo.write(180);
    
  } else {
    servo.write(90);
  }
delay(100);
}
