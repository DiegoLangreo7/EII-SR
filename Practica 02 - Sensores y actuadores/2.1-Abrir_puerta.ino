//Aitor Gómez Ogueta UO294066
//Diego García González UO294255
//Ejercicio de abrir y la puerta

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

byte rowPins[ROWS] = {2, 3, 4, 5}; // filas conectadas a los pines 2-5
byte colPins[COLS] = {6, 7, 8, 9}; // columnas conectadas a los pines 6-9

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

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
  if (key == 'A' && !abierta) { 
    digitalWrite(ledverde, HIGH);
    digitalWrite(ledrojo, LOW);
    abierta = true;
    currentTime = millis();
  }
  else if (abierta && millis() - currentTime > 5000) {
    digitalWrite(ledverde, LOW);
    digitalWrite(ledrojo, HIGH);
    abierta = false; 
  }
}
