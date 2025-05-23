//Aitor Gómez Ogueta UO294066
//Diego García González UO294255
//Ejercicio de Simon dice con buzzer.

#define ledRed 3
#define ledGreen 5
#define ledBlue 6
#define pulsador1 7
#define pulsador2 8
#define buzzer 9
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0

int initialLights = 3;

int pushed1 = 0;
int pushed2 = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Setup");

  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledBlue, OUTPUT);
  pinMode(pulsador1, INPUT);
  pinMode(pulsador2, INPUT);
  pinMode(buzzer, OUTPUT);

  randomSeed(analogRead(A0));
}

void loop() {
  int secuencia[5] = {9, 9, 9, 9, 9};
  generarSecuencia(secuencia, 0, initialLights);
  print(secuencia);
  ejecutarSecuencia(secuencia, 0, initialLights);
  delay(2000);
  bool result = leerBotones(secuencia, 0, initialLights);
  if (!result) { derrota(); return; }
  
  generarSecuencia(secuencia, initialLights, initialLights + 1);
  print(secuencia);
  ejecutarSecuencia(secuencia, 0, initialLights + 1);
  delay(2000);
  result = leerBotones(secuencia, 0, initialLights + 1);
  if (!result) { derrota(); return; }

  generarSecuencia(secuencia, initialLights + 1, initialLights + 2);
  print(secuencia);
  ejecutarSecuencia(secuencia, 0, initialLights + 2);
  delay(2000);
  result = leerBotones(secuencia, 0, initialLights + 2);
  if (!result) { derrota(); return; }
  
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
      digitalWrite(ledGreen, HIGH);
      tone(buzzer, 523);
      delay(1000);
      digitalWrite(ledGreen, LOW);
    } else {
      digitalWrite(ledRed, HIGH);
      tone(buzzer, 587);
      delay(1000);
      digitalWrite(ledRed, LOW);
    }
    noTone(buzzer);
    delay(500);
  }
}

bool leerBotones(int* secuencia, int init, int fin) {
  Serial.println("Leer botones");
  digitalWrite(ledRed, HIGH);
  digitalWrite(ledGreen, HIGH);
  delay(100);
  digitalWrite(ledRed, LOW);
  digitalWrite(ledGreen, LOW);
  
  int i = init;
  while (i < fin) {
    int read1 = digitalRead(pulsador1);
    int read2 = digitalRead(pulsador2);

    if (read1 == HIGH) {
      Serial.println("Pulsador1: " + String(0));
      pushed1 = 1;
      digitalWrite(ledRed, HIGH);
      tone(buzzer, 523);
      delay(100);
      digitalWrite(ledRed, LOW);
      noTone(buzzer);
    }
    if (read2 == HIGH) {
      Serial.println("Pulsador2: " + String(1));
      pushed2 = 1;
      digitalWrite(ledGreen, HIGH);
      tone(buzzer, 587);
      delay(100);
      digitalWrite(ledGreen, LOW);
      noTone(buzzer);
    }

    if ((pushed1 == 1 && pushed2 == 0) || (pushed1 == 0 && pushed2 == 1)) {
      if ((secuencia[i] == 0 && read2 == HIGH) || (secuencia[i] == 1 && read1 == HIGH)) {
        return false;
      } else {
        i++;
      }
    }
    pushed1 = 0; pushed2 = 0;
    delay(500);
  }
  return true;
}

void derrota() {
    setColor(0, 0, 255);
    gameOver(); // Tono de Game Over
    delay(500);
    noTone(buzzer);
    delay(500);
    setColor(0, 0, 0);
}

int melody[] = {

  REST,2, REST,4, REST,8, NOTE_DS4,8, 
  NOTE_E4,-4, REST,8, NOTE_FS4,8, NOTE_G4,-4, REST,8, NOTE_DS4,8,
  NOTE_E4,-8, NOTE_FS4,8,  NOTE_G4,-8, NOTE_C5,8, NOTE_B4,-8, NOTE_E4,8, NOTE_G4,-8, NOTE_B4,8,   
  NOTE_AS4,2, NOTE_A4,-16, NOTE_G4,-16, NOTE_E4,-16, NOTE_D4,-16, 
  NOTE_E4,2, REST,4, REST,8, NOTE_DS4,4,

  NOTE_E4,-4, REST,8, NOTE_FS4,8, NOTE_G4,-4, REST,8, NOTE_DS4,8,
  NOTE_E4,-8, NOTE_FS4,8,  NOTE_G4,-8, NOTE_C5,8, NOTE_B4,-8, NOTE_G4,8, NOTE_B4,-8, NOTE_E5,8,
  NOTE_DS5,1,   
  NOTE_D5,2, REST,4, REST,8, NOTE_DS4,8, 
  NOTE_E4,-4, REST,8, NOTE_FS4,8, NOTE_G4,-4, REST,8, NOTE_DS4,8,
  NOTE_E4,-8, NOTE_FS4,8,  NOTE_G4,-8, NOTE_C5,8, NOTE_B4,-8, NOTE_E4,8, NOTE_G4,-8, NOTE_B4,8,   
  
  NOTE_AS4,2, NOTE_A4,-16, NOTE_G4,-16, NOTE_E4,-16, NOTE_D4,-16, 
  NOTE_E4,-4, REST,4,
  REST,4, NOTE_E5,-8, NOTE_D5,8, NOTE_B4,-8, NOTE_A4,8, NOTE_G4,-8, NOTE_E4,-8,
  NOTE_AS4,16, NOTE_A4,-8, NOTE_AS4,16, NOTE_A4,-8, NOTE_AS4,16, NOTE_A4,-8, NOTE_AS4,16, NOTE_A4,-8,   
  NOTE_G4,-16, NOTE_E4,-16, NOTE_D4,-16, NOTE_E4,16, NOTE_E4,16, NOTE_E4,2,
 
};

void victoria() {
  for (int i = 0; i < 176; i++) {
    setColor(random(0, 256), random(0, 256), random(0, 256));
    tone(buzzer, melody[i],150);
    delay(200);
  }
  noTone(buzzer);
  setColor(0, 0, 0);
}

void print(int* secuencia) {
  for (int i = 0; i < 5; i++) {
    Serial.print(secuencia[i]);
  }
  Serial.println();
}

void setColor(int red, int green, int blue) {
  analogWrite(ledRed, red);
  analogWrite(ledGreen, green);
  analogWrite(ledBlue, blue);
}

void gameOver(){
  // Nota A4
  tone(buzzer, 440, 300); // 300 ms
  delay(300); 
  noTone(buzzer);

  // Nota A4
  tone(buzzer, 440, 300);
  delay(300);
  noTone(buzzer);

  // Nota A4
  tone(buzzer, 440, 300);
  delay(300);
  noTone(buzzer);

  // Nota A4
  tone(buzzer, 440, 300);
  delay(300);
  noTone(buzzer);

  // Nota E4
  tone(buzzer, 330, 300);
  delay(300);
  noTone(buzzer);

  // Nota D4
  tone(buzzer, 294, 300);
  delay(300);
  noTone(buzzer);

  // Nota C4
  tone(buzzer, 262, 300);
  delay(300);
  noTone(buzzer);

  // Nota D4
  tone(buzzer, 294, 300);
  delay(300);
  noTone(buzzer);

  // Nota E4
  tone(buzzer, 330, 300);
  delay(300);
  noTone(buzzer);

  // Nota C4
  tone(buzzer, 262, 300);
  delay(300);
  noTone(buzzer);

  // Nota E4
  tone(buzzer, 330, 300);
  delay(300);
  noTone(buzzer);
}
