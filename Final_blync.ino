#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>
#include "MQ7.h"
#include "SDS011.h"
#include <SoftwareSerial.h>   //Header for Location



#define BLYNK_TEMPLATE_ID "TMPLTtUw3aPb"
#define BLYNK_TEMPLATE_NAME "Living Sane"
#define BLYNK_AUTH_TOKEN "Le1pNdDBrs0jBm2qL3VKWulK3QBCF7ix"


#define DHTPIN 15      // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22  // DHT22 
#define A_PIN 12
#define VOLTAGE 5

SoftwareSerial sim800l(2, 3);   //Check the pin connections

DHT dht(DHTPIN, DHTTYPE);
MQ7 mq7(A_PIN, VOLTAGE);
SDS011 my_sds;

#ifdef ESP32
HardwareSerial port(2);
#endif

char auth[] = "Le1pNdDBrs0jBm2qL3VKWulK3QBCF7ix";  // Your Blynk project authentication token
char ssid[] = "Mt.";  // Your WiFi SSID
char pass[] = "vava@2026";  // Your WiFi password

float p10, p25; 
int err;

SoftwareSerial gsmSerial(10, 11);
void setup() {
  Blynk.begin(auth, ssid, pass);
  my_sds.begin(&port);
  Serial.begin(115200);
  dht.begin();
  mq7.calibrate();	
  //GSM begin
  gsmSerial.begin(115200);
  gsmSerial.print("AT+CGNSPWR=1\r\n"); // Power on the GPS mod
  gsmSerial.print("AT+CGNSTST=1\r\n"); // Start receiving the GPS data
  delay(100);
  //WiFi.begin(ssid, password);
 
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print("%  Temperature: ");
  Serial.print(t);
  Serial.println("°C");
  
//PM sensor, SDS011
  err = my_sds.read(&p25, &p10);
  Serial.println("P2.5: " + String(p25));
  Serial.println("P10:  " + String(p10));

//CO sensor
  Serial.print("CO PPM = "); Serial.println(mq7.readPpm());
	Serial.println(""); 	// blank new line
//Location
  if (gsmSerial.available()) {
    String gpsData = gsmSerial.readStringUntil('\n'); // Read the GPS data
    if (gpsData.startsWith("$GNGGA")) {
      String location = parseGNGGA(gpsData); // Parse the location data from the GPS sentence
      Serial.println(location); // Print the location data
    }
  }
  
  //calling if values are above limits
  if(t>45 || humidity > 85)
  {
  	sim800l.println("ATD+919881420728;");
  }
  // Wifi Connection to send data to blynk

  Blynk.virtualWrite(0, h);  // Send humidity data to Virtual Pin 5
  Blynk.virtualWrite(1, t);  // Send temperature data to Virtual Pin 6
  Blynk.virtualWrite(2, p25);  // Send PM2.5 data to Virtual Pin 5
  Blynk.virtualWrite(3, p10);  // Send PM10 data to Virtual Pin 6

}
//Function for Longitudes and Latitudes.

String parseGNGGA(String sentence) {
  String location = "";
  int i = 0;
  while (sentence[i] != '\0') {
    if (sentence[i] == ',') {
      if (i == 2) {
        int degrees = (sentence.substring(i - 2, i)).toInt();
        float minutes = (sentence.substring(i, i + 9)).toFloat();
        float latitude = degrees + (minutes / 60.0);
        location += "Lat: " + String(latitude, 6) + ", ";
      }
      else if (i == 4) {
        int degrees = (sentence.substring(i - 3, i - 1)).toInt();
        float minutes = (sentence.substring(i, i + 9)).toFloat();
        float longitude = degrees + (minutes / 60.0);
        location += "Lon: " + String(longitude, 6) + ", ";
      }
      else if (i == 9) {
        int fixQuality = (sentence.substring(i, i + 1)).toInt();
        location += "Fix: " + String(fixQuality) + ", ";
      }
      else if (i == 10) {
        int numSatellites = (sentence.substring(i + 1, i + 3)).toInt();
        location += "Sat: " + String(numSatellites) + ", ";
      }
      else if (i == 11) {
        float hdop = (sentence.substring(i, i + 3)).toFloat();
        location += "HDOP: " + String(hdop) + ", ";
      }
      else if (i == 18) {
        int altitude = (sentence.substring(i, i + 6)).toInt();
        location += "Alt: " + String(altitude) + " m";
      }
    }
    i++;
  }
  return location;
}
