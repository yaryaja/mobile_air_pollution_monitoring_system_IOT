#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "SDS011.h"
#include "DHT.h"

char auth[] = "38YW7uNne98RK9y42zLXh9Vf8CpmMegp";
char ssid[] = "Mt.";
char pass[] = "vava@2026";

#define DHTTYPE DHT22   // DHT 11
#define DHTPIN 15    // Digital pin connected to the DHT sensor

DHT dht(DHTPIN, DHTTYPE);
SDS011 my_sds;

#ifdef ESP32
HardwareSerial port(2);
#endif

float p10, p25; 
int err;

void setup()
{
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  // Blynk.config(auth);
 Blynk.begin(auth, ssid, pass);

  my_sds.begin(&port);
  dht.begin();
}

void loop()
{
  // Blynk.run();
  
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


  Blynk.virtualWrite(0, h);  // Send humidity data to Virtual Pin 5
  Blynk.virtualWrite(1, t);  // Send temperature data to Virtual Pin 6
  Blynk.virtualWrite(2, p25);  // Send PM2.5 data to Virtual Pin 5
  Blynk.virtualWrite(3, p10);  // Send PM10 data to Virtual Pin 6
  delay(1000);

}
