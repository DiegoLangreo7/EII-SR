//Aitor Gómez Ogueta UO294066
//Diego García González UO294255
//Ejercicio actuador lineal 5.

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
  int coordenadas[] = {1, -10, 3, 2, 10, 26}; 
  int numCoordenadas = 6;
    moverA(coordenadas[0]);  
    delay(2000);  
    moverA(coordenadas[1]);  
    delay(2000);  
    moverA(coordenadas[2]);  
    delay(2000);  
    moverA(coordenadas[3]);  
    delay(2000);  
    moverA(coordenadas[4]);  
    delay(2000);        
    moverA(coordenadas[5]);  
    delay(2000);     
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
