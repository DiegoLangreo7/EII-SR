#include <SPI.h> //Importamos librería comunicación SPI
#include <Ethernet.h> //Importamos librería Ethernet
#include <DHT.h>
#include <DHT_U.h>

#define DHTTYPE DHT11 // DHT 11
int pin_sensor = 5;
DHT dht(pin_sensor, DHTTYPE);
float temperature, humidity;

byte mac[] = {0x54, 0x55, 0x58, 0x10, 0x00, 0x03}; // Tiene que ser única en la red local, cuidado, cambiad el último dígito por el de vuestro grupo
EthernetServer servidor(80); // Puerto en el 80
// Estos datos cogedlos del ordenador que uséis o del de al lado
IPAddress dnsServer(8, 8, 8, 8);
IPAddress gateway(192, 168, 61, 50);
IPAddress subnet(255, 255, 255, 0);
// Coged la IP del PC de al lado, y usad su toma de Ethernet
IPAddress ip(192, 168, 61, 145);
int led = 8;

void setup(){
  
    Serial.begin(9600);
    Ethernet.begin(mac, ip, dnsServer, gateway, subnet);
    servidor.begin();
    Serial.println("Setup");
    // Imprimir la IP
    Serial.println(Ethernet.localIP());
    
    // Inicializar el led
    pinMode(led,OUTPUT);
    digitalWrite(led,LOW);

    dht.begin();
    temperature = 0;
    humidity = 0;
    
}
void loop(){
      EthernetClient cliente = servidor.available();
      if (cliente) {
        Serial.println("Nueva peticion");
        String peticion="";
        while (cliente.connected()) {
          if (cliente.available()) {
          
          char c = cliente.read(); //Leer petición carácter a carácter
          peticion.concat(c); // concatenar en un string
          // Ha acabado la peticion http
          // Si contiene index responder con una web
          
          // la petición ha acabado '\n' y contiene la cadena "index" al principio: index, indexabc, indexación, etc. Usar equals para que sea igual
          if (c == '\n' && peticion.indexOf("index") != -1){
            Serial.println("Responder");
            // Serial.println(peticion);
            
            // contiene la cadena "encender"
            if(peticion.indexOf("encender") != -1){
                Serial.println("Encender Led");
                digitalWrite(led,HIGH);
            }else if(peticion.indexOf("apagar") != -1){
                // contiene la cadena "apagar"
                Serial.println("Apagar led");
                digitalWrite(led,LOW);
            }
            
            // Enviamos al cliente una respuesta HTTP
            cliente.println("HTTP/1.1 200 OK");
            cliente.println("Content-Type: text/html");
            cliente.println("Access-Control-Allow-Origin: *");
            cliente.println(); // Tiene que estar este salto de línea, sino, fallan las peticiones


            temperature = dht.readTemperature();
            humidity = dht.readHumidity();
            if (isnan(temperature) || isnan(humidity)) {
            Serial.println("Fallo en la lectura del "+DHTTYPE);
            return;
            }

            if (peticion.indexOf("encender") != -1) {
                cliente.println("<html>");
                cliente.println("<body>");
                cliente.println("<p>Temperature: " + String(temperature) + "ºC Humedad: " + String(humidity) + "%</p>");
                cliente.println("</body>");
                cliente.println("</html>");
            }


            
            break;
            }
          }
        }
        
        // Pequeña pausa para asegurar el envio de datos
        delay(1000);
        cliente.stop();// Cierra la conexión
    }
}
