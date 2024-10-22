#include <DHT.h>  
#define DHTPIN 4         // Pin digital donde está conectado el DHT11
#define DHTTYPE DHT11    // Tipo de sensor DHT11

#define LDR_PIN 34       // Pin analógico donde está conectado el LDR
#define TRIG_PIN 26      // Pin para el Trigger del HC-SR04
#define ECHO_PIN 27      // Pin para el Echo del HC-SR04

DHT dht(DHTPIN, DHTTYPE);  // Inicializa el sensor DHT11

void setup() {
  Serial.begin(115200);    // Inicializa la comunicación serie
  dht.begin();             // Inicializa el sensor DHT11
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  // Lectura del DHT11
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  
  // Verifica si las lecturas son válidas
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Error al leer del DHT11");
  } else {
    Serial.print("Temperatura: ");
    Serial.print(temperature);
    Serial.println(" *C");
    
    Serial.print("Humedad: ");
    Serial.print(humidity);
    Serial.println(" %");
  }

  // Lectura del LDR
  int ldrValue = analogRead(LDR_PIN);   // Leer el valor del LDR (entre 0 y 4095)
  Serial.print("Nivel de luz (LDR): ");
  Serial.println(ldrValue);

  // Lectura del sensor ultrasónico HC-SR04
  long duration, distance;

  // Enviar un pulso de Trigger
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Leer el tiempo que tarda el pulso en regresar
  duration = pulseIn(ECHO_PIN, HIGH);

  // Calcular la distancia en cm (velocidad del sonido: 34300 cm/s)
  distance = duration * 0.034 / 2;

  Serial.print("Distancia medida por HC-SR04: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Espera de 2 segundos antes de la siguiente lectura
  delay(2000);
}



