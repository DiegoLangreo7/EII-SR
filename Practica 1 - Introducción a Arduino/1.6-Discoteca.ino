#define led1R 3
#define led1G 5
#define led1B 6
#define led2R A2
#define led2G A3
#define led2B A4
int pot1 = A5;
int pot2 = A6;
int zum = A7;

void setup() {

  Serial.begin(9600);
  Serial.println("Setup");

  pinMode(led1R, OUTPUT);
  pinMode(led1G, OUTPUT);
  pinMode(led1B, OUTPUT);

  pinMode(led2R, OUTPUT);
  pinMode(led2G, OUTPUT);
  pinMode(led2B, OUTPUT);

  pinMode(zum, OUTPUT);

}

void loop() {

  // Leer los valores de los potenciómetros
    int valorPot1 = analogRead(pot1); // Leer potenciómetro 1
    int valorPot2 = analogRead(pot2); // Leer potenciómetro 2

    // Mapear el valor del potenciómetro 1 para la escala de colores (0 a 255)
    int valorColor = map(valorPot1, 0, 1023, 0, 255);
    
    // Calcular el valor para el segundo LED, que se invertirá
    int valorColorInverso = 255 - valorColor;

    // Controlar los LEDs RGB
    // Si el potenciómetro está en su valor mínimo (0)
    if (valorPot1 < 341) { // 0 a 341 corresponde al 0 a 255 en el mapa
        digitalWrite(led1R, LOW);
        digitalWrite(led1G, LOW);
        digitalWrite(led1B, LOW);

        // El segundo LED estará a todo color
        analogWrite(led2R, valorColorInverso);
        analogWrite(led2G, valorColorInverso);
        analogWrite(led2B, valorColorInverso);
    }
    // Si el potenciómetro está en su valor máximo (1023)
    else if (valorPot1 > 682) { // 682 a 1023 corresponde a 255 a 0 en el mapa
        analogWrite(led1R, valorColor);
        analogWrite(led1G, valorColor);
        analogWrite(led1B, valorColor);

        // El segundo LED estará apagado
        digitalWrite(led2R, LOW);
        digitalWrite(led2G, LOW);
        digitalWrite(led2B, LOW);
    }
    // Si el potenciómetro está en su valor medio (entre 341 y 682)
    else {
        int medio = (valorPot1 - 341) * 255 / 341; // Mapea el rango medio a 0-255
        analogWrite(led1R, medio);
        analogWrite(led1G, medio);
        analogWrite(led1B, medio);

        // Ambos LEDs tendrán la misma tonalidad
        analogWrite(led2R, 255 - medio);
        analogWrite(led2G, 255 - medio);
        analogWrite(led2B, 255 - medio);
    }

    // Controlar el volumen del zumbador
    // Mapear el segundo potenciómetro a un rango de notas
    int volumen = map(valorPot2, 0, 1023, 0, 255);
    analogWrite(zum, volumen);

}
