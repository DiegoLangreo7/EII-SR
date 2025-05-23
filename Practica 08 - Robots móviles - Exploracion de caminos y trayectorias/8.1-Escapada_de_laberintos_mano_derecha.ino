//Aitor Gómez Ogueta UO294066
//Diego García González UO294255
//Ejercicio de laberinto (mano derecha)
//Robot 12

#include <Servo.h>
int NO_LINE = LOW; // También podría ponerse 0
int LINE = HIGH; // También podría ponerse 1
Servo servoLeft;
Servo servoRight;

int pinIrCentDer = 3;
int pinIrCentIzq = 2;
int pinIrDer = 11;
int pinIrIzq = 10;

int pinServoRight = 9;
int pinServoLeft = 8;

int STOP = 90;
int BACKWARD = 180;
int FORWARD = 0;

int WAIT_SHORT = 50;
int WAIT_LONG = 3000;

void setup(){
  pinMode(pinIrCentDer, INPUT);
  pinMode(pinIrCentIzq, INPUT);
  pinMode(pinIrDer, INPUT);
  pinMode(pinIrIzq, INPUT);
  servoLeft.attach(pinServoLeft);
  servoRight.attach(pinServoRight);
}
void loop(){
  int centDer = digitalRead(pinIrCentDer);
  int centIzq = digitalRead(pinIrCentIzq);
  int der = digitalRead(pinIrDer);
  int izq = digitalRead(pinIrIzq);
  bool flag = false;

  if (centDer == NO_LINE && centIzq == NO_LINE && der == NO_LINE && izq == NO_LINE){
    flag = true;
    while (digitalRead(pinIrCentDer) == NO_LINE && digitalRead(pinIrCentIzq) == NO_LINE){
      servoLeft.write(BACKWARD);
      servoRight.write(BACKWARD);
    }
  }
  else if ((centDer == LINE && centIzq == LINE && der == LINE && izq == NO_LINE) || ((centDer == LINE && centIzq == LINE && der == LINE))){
    flag = true;
    servoLeft.write(BACKWARD);
    servoRight.write(BACKWARD);
    delay(500);
    while (digitalRead(pinIrCentDer) == NO_LINE && digitalRead(pinIrCentIzq) == NO_LINE){
      servoLeft.write(BACKWARD);
      servoRight.write(BACKWARD);
    }
  }
  else if(centDer == LINE && centIzq == LINE){
    flag = true;
    servoLeft.write(FORWARD);
    servoRight.write(BACKWARD);
  }
  else if (centDer == LINE && centIzq == NO_LINE){
    flag = true;
    servoLeft.write(BACKWARD);
    servoRight.write(BACKWARD);
  }
  else if (centDer == NO_LINE && centIzq  == LINE){
    flag = true;
    servoLeft.write(FORWARD);
    servoRight.write(FORWARD);
  }

  if (flag == false){
      servoLeft.write(STOP);
      servoRight.write(STOP);
      delay(10000);
  }
}
