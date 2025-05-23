//Aitor Gómez Ogueta UO294066
//Diego García González UO294255
//Ejercicio actuador lineal 3.

#include <Servo.h>

const int joystickXPin = A0;
const int alarmaIzquierda = 6;
const int alarmaDerecha = 5;
Servo servo;
const int pinServo = 9;

void setup() {
  Serial.begin(9600);
  servo.attach(pinServo);
  pinMode(alarmaIzquierda, INPUT_PULLUP); 
  pinMode(alarmaDerecha, INPUT_PULLUP);
}

void loop() {
  int joystickXValue = analogRead(joystickXPin);
  bool piIzquierdo = digitalRead(alarmaIzquierda) == LOW; 
  bool piDerecho = digitalRead(alarmaDerecha) == LOW; 

  Serial.print("Joystick Value: ");
  Serial.println(joystickXValue);
  if(piIzquierdo)
    Serial.print("Izquierdo ");
  if(piDerecho)
    Serial.print("Derecho ");

  if (joystickXValue < 50 && !piIzquierdo) {
    servo.write(180);
  } else if (joystickXValue >= 50 && joystickXValue < 520 && !piIzquierdo) {
    servo.write(110);
  } else if (joystickXValue >= 1000 &&  !piDerecho) {
    servo.write(0);
  } else if (joystickXValue > 560 && joystickXValue < 1000 && !piDerecho) {
    servo.write(80);
  } else {
    servo.write(90);
  }

  delay(100); 
}




