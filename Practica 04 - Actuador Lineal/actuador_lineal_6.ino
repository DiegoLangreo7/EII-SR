//Aitor Gómez Ogueta UO294066
//Diego García González UO294255
//Ejercicio actuador lineal 6.

#include <Servo.h>

const int pinServo = 8;          
Servo servo;                      

const int bordeIzquierdo = 6;    
const int bordeDerecho = 7;      

unsigned long tiempoRecorridoDerecha;  
unsigned long tiempoRecorridoIzquierda;    
const int posicionesTotales = 24;  
int posicionActual = 0;           

void setup() {
  Serial.begin(9600);
  servo.attach(pinServo);
  pinMode(bordeIzquierdo, INPUT_PULLUP);
  pinMode(bordeDerecho, INPUT_PULLUP);
  iniciarCalibracion();  
}

void loop() {
   Serial.println("Introduce una/s coordenada/s con el formato 'coordenada,tiempo;'");    
    while (Serial.available() == 0) {}
    
    String input = Serial.readStringUntil('\n');
    Serial.print("Valor introducido: ");
    Serial.println(input); 

    int startIndex = 0;
    int separatorIndex;

    while ((separatorIndex = input.indexOf(';', startIndex)) != -1) {
        String pair = input.substring(startIndex, separatorIndex); 
        int commaIndex = pair.indexOf(',');

        if (commaIndex != -1) {
            String firstValue = pair.substring(0, commaIndex);
            String secondValue = pair.substring(commaIndex + 1);
              moverA(firstValue.toDouble());
              delay(secondValue.toDouble());
        }

        startIndex = separatorIndex + 1; 
    }

    delay(1000); 
}

void iniciarCalibracion() {
  Serial.println("Calibracion empezada");
  while (digitalRead(bordeIzquierdo) == HIGH) {
    servo.write(180);  
  }
  servo.write(90);  
  delay(1000);  
  Serial.println("Midiendo izda-dcha...");
  unsigned long tiempoInicio = millis();
  
  while (digitalRead(bordeDerecho) == HIGH) {
    servo.write(0);  
  }
  servo.write(90); 
  tiempoRecorridoDerecha = millis() - tiempoInicio;  
  delay(1000);  
  Serial.println("Midiendo dcha-izda...");
  tiempoInicio = millis();
  while (digitalRead(bordeIzquierdo) == HIGH) {
    servo.write(180);  
  }
  servo.write(90); 
  tiempoRecorridoIzquierda = millis() - tiempoInicio;  

  Serial.print("El tiempo de recorrido hacia la derecha es: ");
  Serial.println(tiempoRecorridoDerecha);
  Serial.print("El tiempo de recorrido hacia la izquierda es: ");
  Serial.println(tiempoRecorridoIzquierda);
}

void moverA(int coordenada) {
  Serial.println(coordenada);
  if (coordenada < 0) {
    coordenada = 0;
  } else if (coordenada > posicionesTotales) {
    coordenada = posicionesTotales;
  }
  unsigned long tiempoMovimiento = 0;
  if (coordenada > posicionActual) {
    tiempoMovimiento = (tiempoRecorridoDerecha / posicionesTotales) * abs(coordenada - posicionActual);
    servo.write(0);  
  } else if (coordenada < posicionActual) {
    tiempoMovimiento = (tiempoRecorridoIzquierda / posicionesTotales) * abs(coordenada - posicionActual);
    servo.write(180);  
  } 

  delay(tiempoMovimiento);  
  posicionActual = coordenada;  
  servo.write(90); 
}