#include <Arduino.h>

// Definições dos pinos dos sensores
#define TRIG_PIN 33    // JSN-SR04M trigger
#define ECHO_PIN 32    // JSN-SR04M echo
#define WATER_LEVEL_PIN 34 // Water‐level sensor analog output (AO)
#define RAIN_SENSOR_DO_PIN 35    // Water/rain sensor digital output (DO)

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Setup dos sensores
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(WATER_LEVEL_PIN, INPUT);
  pinMode(RAIN_SENSOR_DO_PIN, INPUT);
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
  int raw = analogRead(WATER_LEVEL_PIN);        // 0–4095 on ESP32
  return map(raw, 0, 4095, 0, 100);             // 0–100%
}

void loop() {
  float distance  = readUltrasonicDistance();
  int   levelPct  = readWaterLevel();
  bool  rainDetect= digitalRead(RAIN_SENSOR_DO_PIN); // adjust logic if module pulls LOW when wet

  // serial output
  Serial.printf("Dist(cm): %.1f  Level(%%): %d  Rain: %s\n",
                distance, levelPct, rainDetect ? "YES" : "NO");

  delay(10000); // Espera 10 segundos antes de nova leitura
}

