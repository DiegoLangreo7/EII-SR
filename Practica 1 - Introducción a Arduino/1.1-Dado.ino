//Aitor Gómez Ogueta UO294066
//Diego García González UO294255
//Ejercicio del dado aleatorio


  #define led1 3
  #define led2 2
  #define led3 5
  #define numberOfLeds 3

  byte leds[numberOfLeds] = {led1, led2, led3};
  int numberOfLedsToActivate = 0;

  int button = 4;
  int pushed = 0;

void setup() {
  
  Serial.begin(9600);
  Serial.println("Setup");

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(button, INPUT);

  randomSeed(analogRead(A0));
  
}

void loop() {

  int read = digitalRead(button);

  if (read == HIGH && pushed == 0){
    pushed = 1;
    numberOfLedsToActivate = random(1, 4);
    light(numberOfLedsToActivate, pushed);
  }
  else if (read == LOW && pushed == 1){
    pushed = 0;
    for (int i = 0; i < numberOfLeds; i++){
        digitalWrite(leds[i], LOW);
      }
  }

}

void light(int number, bool pushed){
  
  Serial.println(number);
  for (int i = 0; i < number; i++){
    digitalWrite(leds[i], HIGH);
  }

}
