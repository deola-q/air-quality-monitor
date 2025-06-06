#include <DHT.h>

#define DHTPIN 25           // Пин для DHT11
#define DHTTYPE DHT11   
#define MQ135_PIN 32        // Пин для MQ135
#define SERIAL_BAUDRATE 115200
#define DELAY_MS 2000


const int THRESHOLD_CO2 = 1500;    // Порог CO2 (ADC)
const float THRESHOLD_TEMP = 30.0; // Макс температура (°C)
const float THRESHOLD_HUM = 70.0;  // Макс влажность (%)

// Инициализация DHT
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(SERIAL_BAUDRATE);
  dht.begin();
  pinMode(MQ135_PIN, INPUT);
  
  Serial.println("=== Система мониторинга воздуха ===");
  Serial.println("Пороговые значения:");
  Serial.print("CO2: "); Serial.println(THRESHOLD_CO2);
  Serial.print("Температура: "); Serial.print(THRESHOLD_TEMP); Serial.println("°C");
  Serial.print("Влажность: "); Serial.print(THRESHOLD_HUM); Serial.println("%");
  Serial.println("===============================");
}

void loop() {
  // Чтение данных с датчиков
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int air_quality = analogRead(MQ135_PIN);

  if (isnan(temperature) {
    Serial.println("Ошибка: Не удалось прочитать температуру!");
  } else if (isnan(humidity)) {
    Serial.println("Ошибка: Не удалось прочитать влажность!");
  } else {
    // Вывод текущих значений
    Serial.print("\nТемпература: ");
    Serial.print(temperature);
    Serial.print("°C\tВлажность: ");
    Serial.print(humidity);
    Serial.print("%\tКачество воздуха (ADC): ");
    Serial.println(air_quality);

    // Проверка превышения порогов и вывод рекомендаций
    checkThresholds(temperature, humidity, air_quality);
  }

  delay(DELAY_MS);
}

// Проверка пороговых значений и вывод предупреждений
void checkThresholds(float temp, float hum, int co2) {
  bool isWarning = false;

  if (co2 > THRESHOLD_CO2) {
    Serial.println("⚠ ВНИМАНИЕ: Высокий уровень CO2!");
    Serial.println("→ Рекомендация: Проветрите помещение");
    isWarning = true;
  }
  
  if (temp > THRESHOLD_TEMP) {
    Serial.println("⚠ ВНИМАНИЕ: Высокая температура!");
    Serial.println("→ Рекомендация: Включите кондиционер или проветрите");
    isWarning = true;
  }
  
  if (hum > THRESHOLD_HUM) {
    Serial.println("⚠ ВНИМАНИЕ: Высокая влажность!");
    Serial.println("→ Рекомендация: Включите осушитель или проветрите");
    isWarning = true;
  }
