
//Aitor Gómez Ogueta UO294066
//Diego García González UO294255
//Ejercicio de abrir y cerrar la puerta

#include <Keypad.h>

#define ledverde 3
#define ledrojo 2

const byte ROWS = 4; // cuatro filas
const byte COLS = 4; // cuatro columnas
bool abierta;
unsigned long currentTime;

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {4, 5, 6, 7}; // filas conectadas a los pines 4-7
byte colPins[COLS] = {8, 9, 10, 11}; // columnas conectadas a los pines 8-11

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String patron; 

void setup() {
  Serial.begin(9600); 
  pinMode(ledverde, OUTPUT);
  pinMode(ledrojo, OUTPUT);
  abierta = false;
  digitalWrite(ledverde, LOW);
  digitalWrite(ledrojo, HIGH);
}

void loop() {
  char key = keypad.getKey();

  if (key != NO_KEY) { 
    patron += key; 

    if (patron.indexOf("9876") != -1 && !abierta) { 
      digitalWrite(ledverde, HIGH);
      digitalWrite(ledrojo, LOW);
      abierta = true;
      currentTime = millis();
      patron = ""; 
    } 
    else if (key == 'C' && abierta) {
      digitalWrite(ledverde, LOW);
      digitalWrite(ledrojo, HIGH);
      abierta = false;
      patron = ""; 
    } 
    else if (abierta && millis() - currentTime > 5000) {
      digitalWrite(ledverde, LOW);
      digitalWrite(ledrojo, HIGH);
      abierta = false; 
      patron = ""; 
    }
  }
}

