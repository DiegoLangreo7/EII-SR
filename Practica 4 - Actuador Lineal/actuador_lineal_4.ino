#include <Servo.h>

const int pinServo = 8;
Servo servo;

const int joystickXPin = 14;
const int bordeIzquierdo = 6;
const int bordeDerecho = 7;
const int botonJoystick = 9;

bool modo = false;
bool primeras = true;

void setup() {
  Serial.begin(9600);
  servo.attach(pinServo);
  pinMode(bordeIzquierdo, INPUT_PULLUP); 
  pinMode(bordeDerecho, INPUT_PULLUP);
  pinMode(botonJoystick, INPUT_PULLUP);
  servo.write(0);
}

void loop() {
  if (digitalRead(botonJoystick) == LOW) {
    modo = !modo;
    if(modo)
      Serial.println("Modo automatico activado");
    else
      Serial.println("Modo manual activado");
    delay(300); 
    primeras = true; 
  }

  if (modo) {
    modoAutomatico();
  } else {
    modoManual();
  }
}

void modoManual() {
  int joystickXValue = analogRead(joystickXPin);
  bool piIzquierdo = digitalRead(bordeIzquierdo) == LOW; 
  bool piDerecho = digitalRead(bordeDerecho) == LOW; 

  if (joystickXValue < 100 && !piIzquierdo) {
    servo.write(180);
  } else if (joystickXValue >= 100 && joystickXValue < 412 && !piIzquierdo) {
    servo.write(135);
  } else if (joystickXValue > 913 && !piDerecho) {
    servo.write(0);
  } else if (joystickXValue > 612 && joystickXValue <= 913 && !piDerecho) {
    servo.write(45);
  } else {
    servo.write(90);
  }

  delay(100); 
}

void modoAutomatico() {
  bool tocadoIzquierdo = digitalRead(bordeIzquierdo) == LOW;
  bool tocadoDerecho = digitalRead(bordeDerecho) == LOW;

  if (primeras) {
    servo.write(180);
  }
   
  if (tocadoDerecho) {
    primeras = false;
    Serial.println("Mahd dtrong kua");
    servo.write(180);
  }
  
  if (tocadoIzquierdo) {
    primeras = false;
    Serial.println("Mahd dtrong sai");
    servo.write(0);
  }

  delay(100);
}


