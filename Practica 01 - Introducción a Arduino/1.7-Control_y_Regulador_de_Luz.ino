#define led1 3
#define led2 4
#define led3 5
int pot1 = A2;
int pot2 = A3;

#define numberOfLeds 3
byte leds[numberOfLeds] = {led1, led2, led3};

void setup() {

  Serial.begin(9600);
  Serial.println("Setup");

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

}

void loop() {

  int numberOfLedsToSwitchOn = map(analogRead(pot1), 0, 1023, 0, 3);
  int intensity = map(analogRead(pot2), 0, 1023, 0, 255);

  for (int i = 0; i < numberOfLeds; i++){

    if (i < numberOfLedsToSwitchOn){
      digitalWrite(leds[i], intensity);
    }
    else{
      digitalWrite(leds[i], LOW);
    }

  }

}