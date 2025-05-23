
//Aitor Gómez Ogueta UO294066
//Diego García González UO294255
//Ejercicio de Simon dice con buzzer.

  #define ledS1G 5
  #define ledS1R 2
  #define ledS2G 10
  #define ledS2R 9
  #define ledPG 12
  #define ledPR 13
  #define zumbador 3


void setup() {
  
  Serial.begin(9600);
  Serial.println("Setup");

  pinMode(ledS1G, OUTPUT);
  pinMode(ledS1R, OUTPUT);
  pinMode(ledS2G, OUTPUT);
  pinMode(ledS2R, OUTPUT);
  pinMode(ledPG, OUTPUT);
  pinMode(ledPR, OUTPUT);
  pinMode(zumbador, OUTPUT);

  analogWrite(ledS2R, 255);
  analogWrite(ledS1G, 255);
  digitalWrite(ledPR,HIGH);
  
}

void loop() {
 // Semáforo 2 rojo
  analogWrite(ledS2R, 255);
  analogWrite(ledS2G, 0);
  delay(1000);
  
  // Semáforo 1 en verde
  analogWrite(ledS1G, 255);
  analogWrite(ledS1R, 0);
  delay(5000);
  
  // Cambiar semáforo 1 a rojo
  analogWrite(ledS1R, 255);
  delay(2000);
  
  // Espera antes de cambiar a semáforo 2
  analogWrite(ledS1G, 0);
  delay(1000);
  
  // Semáforo 2 en verde, LED verde peatones encendido y zumbador activado
  analogWrite(ledS2G, 255);
  analogWrite(ledS2R, 0);
  digitalWrite(ledPR, LOW); // LED rojo peatones apagado
  digitalWrite(ledPG, HIGH); // LED verde peatones encendido

  // Zumbador activado con pitidos
  for (int i = 0; i < 5; i++) { // Sonido intermitente
    tone(zumbador, 523);; // Activar zumbador
    delay(500);
    tone(zumbador, 0); // Desactivar zumbador
    delay(500);
  }
  
  // Parpadeo del LED verde para peatones
  for (int i = 0; i < 5; i++) { // Parpadeo rápido
    digitalWrite(ledPG, HIGH);
    delay(250);
    digitalWrite(ledPG, LOW);
    delay(250);
  }

  // Cambiar el semáforo 2 a rojo, LED peatones rojo encendido
  analogWrite(ledS2R, 255);
  digitalWrite(ledPG, LOW); // LED verde peatones apagado
  digitalWrite(ledPR, HIGH); // LED rojo peatones encendido
  noTone(zumbador); // Desactivar zumbador
  delay(2000);
}
