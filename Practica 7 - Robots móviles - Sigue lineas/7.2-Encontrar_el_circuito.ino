//Aitor Gómez Ogueta UO294066
//Diego García González UO294255
//Ejercicio de encuentra camino

#include <Servo.h>

int NO_LINE = LOW;
int LINE = HIGH;
Servo servoLeft;
Servo servoRight;

int pinIrDer = 3;
int pinIrIzq = 2;
int pinServoRight = 9;
int pinServoLeft = 8;

int STOP = 90;
int BACKWARD = 180;
int FORWARD = 0;

void setup() {
  pinMode(pinIrDer, INPUT);
  pinMode(pinIrIzq, INPUT);
  servoLeft.attach(pinServoLeft);
  servoRight.attach(pinServoRight);
}

void loop() {
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
  // Encuentra camino (cuadrado)
  else {
    encontrarCircuito();
  }
}

void encontrarCircuito() {
  static unsigned long previousTime = 0;
  static int step = 0; // Variable para controlar el paso de la búsqueda
  static int waitTime = 200; // Tiempo de espera inicial

  unsigned long currentTime = millis();
  
  // Girar 90 grados a la derecha
  if (step == 0) {
    servoLeft.write(BACKWARD);
    servoRight.write(BACKWARD);
    previousTime = currentTime; // Reiniciar el tiempo
    step++;
  } 
  else if (step == 1) {
    if (currentTime - previousTime >= 1000) { // 1.5 segundos
      // Verificar si encontró la línea
      if (digitalRead(pinIrDer) == LINE || digitalRead(pinIrIzq) == LINE) {
        return; // Salir si encuentra la línea
      }
      // Avanzar
      servoLeft.write(FORWARD);
      servoRight.write(BACKWARD);
      previousTime = currentTime; // Reiniciar el tiempo
      step++;
    }
  }
  else if (step == 2) {
    if (currentTime - previousTime >= waitTime) { // Esperar 200 ms
      // Verificar si encontró la línea
      if (digitalRead(pinIrDer) == LINE || digitalRead(pinIrIzq) == LINE) {
        return; // Salir si encuentra la línea
      }
      // Incrementar el tiempo de espera
      waitTime += 200; // Aumentar el tiempo de espera en 200 ms
      step = 0; // Reiniciar el proceso
    }
  }
}
