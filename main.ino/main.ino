#include <DHT.h>

// Константы
#define DHTPIN 25       // Пин для DHT11
#define DHTTYPE DHT11   
#define MQ135_PIN 32    // Пин для MQ135
#define SERIAL_BAUDRATE 115200
#define DELAY_MS 2000   

// Инициализация DHT
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(SERIAL_BAUDRATE);
  dht.begin();
  pinMode(MQ135_PIN, INPUT);  

}

void loop() {
  // Чтение данных с DHT11
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature)) {
    Serial.println("Ошибка чтения температуры");
  } else if (isnan(humidity)) {
    Serial.println("Ошибка чтения влажности");
  } else {
    Serial.print("Температура: ");
    Serial.print(temperature);
    Serial.print("°C\tВлажность: ");
    Serial.print(humidity);
    Serial.println("%");
  }

  // Чтение данных с MQ-135
  int air_quality = analogRead(MQ135_PIN);
  Serial.print("Качество воздуха (RAW ADC): ");
  Serial.println(air_quality);

  delay(DELAY_MS); 
}

