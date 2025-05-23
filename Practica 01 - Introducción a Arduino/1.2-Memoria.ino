//Aitor Gómez Ogueta UO294066
//Diego García González UO294255
//Ejercicio de Simon dice.


  #define led1 3
  #define led2 2
  #define pulsador1 4
  #define pulsador2 5
  int initialLights = 3;

  int pushed1 = 0;
  int pushed2 = 0;

void setup() {
  
  Serial.begin(9600);
  Serial.println("Setup");

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(pulsador1, INPUT);
  pinMode(pulsador2, INPUT);

  randomSeed(analogRead(A0));
  
}

void loop() {
  //digitalWrite(led1,LOW);digitalWrite(led2,LOW);
  int secuencia[5] = {9, 9, 9, 9, 9};
  generarSecuencia(secuencia,0,initialLights);
  print(secuencia);
  ejecutarSecuencia(secuencia,0,initialLights);
  delay(2000);
  bool result = leerBotones(secuencia,0,initialLights);
  if(!result){derrota();return;} 
  generarSecuencia(secuencia,initialLights,initialLights+1);
  print(secuencia);
  ejecutarSecuencia(secuencia,0,initialLights+1);
  delay(2000);
  result = leerBotones(secuencia,0,initialLights+1);
  if(!result){derrota();return;} 
  generarSecuencia(secuencia,initialLights+1,initialLights+2);
  print(secuencia);
  ejecutarSecuencia(secuencia,0,initialLights+2);
  delay(2000);
  result = leerBotones(secuencia,0,initialLights+2);
  if(!result){derrota();return;} 
  victoria();
}

void generarSecuencia(int* secuencia, int init, int fin) {
  for (int i = init; i < fin; i++) {
    secuencia[i] = random(0, 2);
  }
}

void ejecutarSecuencia(int* secuencia, int init, int fin) {
  for (int i = init; i < fin; i++) {
    if (secuencia[i] == 1) {
      digitalWrite(led1, HIGH);
      delay(1000);
      digitalWrite(led1, LOW);
      delay(500);
    } else {
      digitalWrite(led2, HIGH);
      delay(1000);
      digitalWrite(led2, LOW);
      delay(500);
    }
  }
}

bool leerBotones(int* secuencia, int init, int fin) {
  Serial.println("Leer botones");
  digitalWrite(led2, HIGH);
  digitalWrite(led1, HIGH);
  delay(100);
  digitalWrite(led2, LOW);
  digitalWrite(led1, LOW);
  int i = init;
  while (i < fin) {
    int read1 = digitalRead(pulsador1);
    int read2 = digitalRead(pulsador2);

    if (read1 == HIGH){
      Serial.println("Pulsador1: " + read1);
      pushed1 = 1;
      digitalWrite(led2, HIGH);
      delay(100);
      digitalWrite(led2, LOW);
    }
    if (read2 == HIGH){
      Serial.println("Pulsador2: " + read2);
      pushed2 = 1;
      digitalWrite(led1, HIGH);
      delay(100);
      digitalWrite(led1, LOW);
    }

    if ((pushed1 == 1 && pushed2 == 0) || (pushed1 == 0 && pushed2 == 1)) {
      if ((secuencia[i] == 0 && read2 == HIGH) || (secuencia[i] == 1 && read1 == HIGH)) {
        
        return false;
      } 
      else {
        i++;
      }
    }
    pushed1 = 0; pushed2 = 0;
    delay(500);
    
  }
  return true;
}

void derrota(){
  for (int i = 0; i < 2; i++) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    delay(500);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    delay(500);
  }
}

void victoria(){
  for (int i = 0; i < 10; i++) {
    digitalWrite(led1, HIGH);
    delay(500);
    digitalWrite(led2, LOW);
    delay(500);
    digitalWrite(led2, HIGH);
    delay(500);
    digitalWrite(led1, LOW);
    delay(500);
  }
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
}

void print(int* secuencia){
  for (int i = 0; i < 5; i++) {
    Serial.print(secuencia[i]);
  }
  Serial.println();
}
