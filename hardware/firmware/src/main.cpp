#include <Arduino.h>
#include <LoRa.h>

// Definições dos pinos dos sensores
#define TRIG_PIN 5
#define ECHO_PIN 18
#define WATER_LEVEL_PIN 34 // Pino analógico

// Definições do LoRa
#define LORA_SCK 5
#define LORA_MISO 19
#define LORA_MOSI 27
#define LORA_SS 18
#define LORA_RST 14
#define LORA_DIO0 26
#define BAND 915E6  // Frequência do LoRa no Brasil

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Setup dos sensores
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(WATER_LEVEL_PIN, INPUT);

  // Setup do LoRa
  Serial.println("Inicializando LoRa...");
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);

  if (!LoRa.begin(BAND)) {
    Serial.println("Falha ao iniciar LoRa!");
    while (1);
  }
  Serial.println("LoRa inicializado com sucesso.");
}

float readUltrasonicDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  float distanceCm = (duration * 0.0343) / 2;

  return distanceCm;
}

int readWaterLevel() {
  int analogValue = analogRead(WATER_LEVEL_PIN);
  return map(analogValue, 0, 4095, 0, 100); // Mapeia de 0-4095 para 0-100%
}

void loop() {
  float distance = readUltrasonicDistance();
  int waterLevel = readWaterLevel();

  Serial.print("Distância Ultrassônica (cm): ");
  Serial.println(distance);
  Serial.print("Nível da água (%): ");
  Serial.println(waterLevel);

  // Enviar dados via LoRa
  LoRa.beginPacket();
  LoRa.print("Distancia:");
  LoRa.print(distance);
  LoRa.print(";NivelAgua:");
  LoRa.print(waterLevel);
  LoRa.endPacket();

  delay(10000); // Espera 10 segundos antes de nova leitura
}

