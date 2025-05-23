//Aitor Gómez Ogueta UO294066
//Diego García González UO294255
//Ejercicio del cruce de dos semáforos

  #define ledS1V 9
  #define ledS1A 10 //evidentemente estan los numeros al azar
  #define ledS1R 11
  #define ledS2V 6
  #define ledS2A 5
  #define ledS2R 4


void setup() {
  
  Serial.begin(9600);
  Serial.println("Setup");

  pinMode(ledS1V, OUTPUT);
  pinMode(ledS1A, OUTPUT);
  pinMode(ledS1R, OUTPUT);
  pinMode(ledS2V, OUTPUT);
  pinMode(ledS2A, OUTPUT);
  pinMode(ledS2R, OUTPUT);
  
}

void loop() {

  digitalWrite(ledS2A,LOW);
  digitalWrite(ledS2R, HIGH);
  delay(1000);
  digitalWrite(ledS1V, HIGH);
  digitalWrite(ledS1R, LOW);
  delay(5000);
  digitalWrite(ledS1A,HIGH);
  digitalWrite(ledS1V,LOW);
  delay(2000);
  digitalWrite(ledS1A,LOW);
  digitalWrite(ledS1R,HIGH);
  delay(1000);
  digitalWrite(ledS2V,HIGH);
  digitalWrite(ledS2R,LOW);
  delay(5000);
  digitalWrite(ledS2A,HIGH);
  digitalWrite(ledS2V,LOW);
  delay(2000);
}
