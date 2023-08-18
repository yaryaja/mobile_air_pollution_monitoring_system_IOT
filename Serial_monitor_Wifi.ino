#include "SDS011.h"
#include "DHT.h"
#include <WiFi.h>

#define DHTPIN 15    // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22   // DHT 11

const char* ssid = "Mt.";
const char* password = "vava@2026";

DHT dht(DHTPIN, DHTTYPE);
SDS011 my_sds;


#ifdef ESP32
HardwareSerial port(2);
#endif

float p10, p25; 
int err;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");

  my_sds.begin(&port);
  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
  Serial.println("Humidity: " + String(h) + "%");
  Serial.println("Temperature: " + String(t) + "°C");
  err = my_sds.read(&p25, &p10);
  Serial.println("P2.5: " + String(p25));
  Serial.println("P10:  " + String(p10));
  Serial.println("____________________________");

  delay(1000);
}
