//Aitor Gómez Ogueta UO294066
//Diego García González UO294255
//Ejercicio control y regulador de luz.

#define led1 3
#define led2 5
#define led3 6
int pot = A2;

#define numberOfLeds 3
int leds[numberOfLeds] = {led1, led2, led3};

void setup() {
  Serial.begin(9600);
  Serial.println("Setup");

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
}

void loop() {
  int valorPot = analogRead(pot);
  int numberOfLedsToSwitchOn = map(valorPot, 0, 1023, 0, 3);

  for (int i = 0; i < numberOfLeds; i++) {
    if (i < numberOfLedsToSwitchOn) {
      int brightness = map(valorPot, 0, 1023, 0, 255);
      analogWrite(leds[i], brightness);
    } else {
      analogWrite(leds[i], 0);
    }
  }
}
