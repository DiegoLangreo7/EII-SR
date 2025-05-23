//Aitor Gómez Ogueta UO294066
//Diego García González UO294255
//Ejercicio de sigue lineas

#include <Servo.h>
int NO_LINE = LOW; // También podría ponerse 0
int LINE = HIGH; // También podría ponerse 1
Servo servoLeft;
Servo servoRight;

int pinIrDer = 3;
int pinIrIzq = 2;
int pinServoRight = 9;
int pinServoLeft = 8;

int STOP = 90;
int BACKWARD = 180;
int FORWARD = 0;

int WAIT_SHORT = 50;
int WAIT_LONG = 3000;

void setup(){
  pinMode(pinIrDer, INPUT);
  pinMode(pinIrIzq, INPUT);
  servoLeft.attach(pinServoLeft);
  servoRight.attach(pinServoRight);
}
void loop(){
  int der = digitalRead(pinIrDer);
  int izq = digitalRead(pinIrIzq);

  if(der == LINE && izq == LINE){
    servoLeft.write(FORWARD);
    servoRight.write(BACKWARD);
  }
  else if (der == LINE && izq == NO_LINE){
    servoLeft.write(BACKWARD);
    servoRight.write(BACKWARD);
  }
  else if (der == NO_LINE && izq  == LINE){
    servoLeft.write(FORWARD);
    servoRight.write(FORWARD);
  }
  else {
    servoLeft.write(STOP);
    servoRight.write(STOP);
  }
}
