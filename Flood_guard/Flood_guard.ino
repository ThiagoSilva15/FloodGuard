int flashPin = 4;

void setup() {
    pinMode(flashPin, OUTPUT);
}

void loop() {
    digitalWrite(flashPin, HIGH);
    delay(1000);
    digitalWrite(flashPin, LOW);
    delay(1000);
}

// #include <Arduino.h>
// // Definições dos pinos dos sensores
// #define TRIG_PIN 33              // JSN-SR04M trigger
// #define ECHO_PIN 32              // JSN-SR04M echo
// #define WATER_LEVEL_PIN 34       // Saída analógica do sensor de nível de água
// #define RAIN_SENSOR_DO_PIN 35    // Saída digital do sensor de chuva

// // Modo de operação dos sensores: 0 = Ultrassônico, 1 = Nível/Chuva, 2 = Ambos
// #define SENSOR_MODE 2

// void setup() {
//   Serial.begin(115200);
//   delay(1000);
//   Serial.println("==== INICIANDO SISTEMA ====");

//   // Setup dos sensores
//   Serial.println("Configurando pinos...");
//   pinMode(TRIG_PIN, OUTPUT);
//   pinMode(ECHO_PIN, INPUT);
//   pinMode(WATER_LEVEL_PIN, INPUT);
//   pinMode(RAIN_SENSOR_DO_PIN, INPUT);

//   Serial.printf("Modo de sensor selecionado: %d\n", SENSOR_MODE);
//   Serial.println("Setup concluído. Iniciando leituras...\n");
// }

// float readUltrasonicDistance() {
//   Serial.println("[DEBUG] Disparando sensor ultrassônico...");
//   digitalWrite(TRIG_PIN, LOW);
//   delayMicroseconds(2);
//   digitalWrite(TRIG_PIN, HIGH);
//   delayMicroseconds(10);
//   digitalWrite(TRIG_PIN, LOW);

//   long duration = pulseIn(ECHO_PIN, HIGH, 30000); // Timeout de 30 ms
//   if (duration == 0) {
//     Serial.println("[ERRO] Nenhuma leitura do sensor ultrassônico (timeout).");
//     return -1.0;
//   }

//   float distanceCm = (duration * 0.0343) / 2;
//   Serial.printf("[DEBUG] Duração: %ld µs | Distância: %.2f cm\n", duration, distanceCm);
//   return distanceCm;
// }

// int readWaterLevel() {
//   Serial.println("[DEBUG] Lendo nível de água (analógico)...");
//   int raw = analogRead(WATER_LEVEL_PIN);  // 0–4095 no ESP32
//   int percent = map(raw, 0, 4095, 0, 100);
//   Serial.printf("[DEBUG] Valor bruto: %d | Percentual: %d%%\n", raw, percent);
//   return percent;
// }

// bool readRainSensor() {
//   Serial.println("[DEBUG] Lendo sensor de chuva (digital)...");
//   int rainRaw = digitalRead(RAIN_SENSOR_DO_PIN);
//   bool isRaining = (rainRaw == LOW);  // LOW geralmente indica presença de água
//   Serial.printf("[DEBUG] Valor digital: %d | Chuva detectada: %s\n", rainRaw, isRaining ? "SIM" : "NÃO");
//   return isRaining;
// }

// void loop() {
//   Serial.println("==== NOVA LEITURA ====");

//   if (SENSOR_MODE == 0) {
//     float distance = readUltrasonicDistance();
//     if (distance > 0) {
//       Serial.printf("Resultado: Distância = %.1f cm\n", distance);
//     } else {
//       Serial.println("Resultado: Distância inválida ou fora do alcance.");
//     }

//   } else if (SENSOR_MODE == 1) {
//     int levelPct = readWaterLevel();
//     bool rainDetect = readRainSensor();
//     Serial.printf("Resultado: Nível = %d%% | Chuva: %s\n", levelPct, rainDetect ? "SIM" : "NÃO");

//   } else if (SENSOR_MODE == 2) {
//     float distance2 = readUltrasonicDistance();
//     int levelPct2 = readWaterLevel();
//     bool rainDetect2 = readRainSensor();

//     if (distance2 > 0) {
//       Serial.printf("Resultado: Distância = %.1f cm | Nível = %d%% | Chuva: %s\n",
//                     distance2, levelPct2, rainDetect2 ? "SIM" : "NÃO");
//     } else {
//       Serial.printf("Resultado: Distância inválida | Nível = %d%% | Chuva: %s\n",
//                     levelPct2, rainDetect2 ? "SIM" : "NÃO");
//     }
//   }

//   Serial.println("Aguardando 10 segundos...\n");
//   delay(10000);
// }
