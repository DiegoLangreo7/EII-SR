//Aitor Gómez Ogueta UO294066
//Diego García González UO294255
//Ejercicio actuador lineal 7.

#include <Servo.h>

const int pinServo = 8;          
Servo servo;                      

const int bordeIzquierdo = 6;    
const int bordeDerecho = 7;      

unsigned long tiempoRecorridoDerecha;  
unsigned long tiempoRecorridoIzquierda;    
int posicionesTotales = 0;  
int posicionActual = 0;           

void setup() {
  Serial.begin(9600);
  servo.attach(pinServo);
  pinMode(bordeIzquierdo, INPUT_PULLUP);
  pinMode(bordeDerecho, INPUT_PULLUP);
  iniciarCalibracion();  
  pedirN();
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
            if(firstValue.toInt()!=0 && secondValue.toInt() !=0){
              moverA(firstValue.toDouble());
              delay(secondValue.toDouble());
            }
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

void pedirN(){
  Serial.println("El rango de movimiento es de [0,N]");
  bool valido = false;
  bool primera = true;
  int N = 0;
  while(!valido){
    if(primera){
      Serial.println("Introduzca la N por consola porfavor: ");
    }else{
      Serial.println("la N debe ser un numero!! Introduzcalo de nuevo... ");
    }
  while (Serial.available() == 0) {}
  N = Serial.parseInt();
    if(N!=0){
      valido = true;
    }
    primera = false;
  }
  Serial.println(N);
  posicionesTotales = N;
  delay(1000);
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