#include <TinyGPS++.h>    // Include the TinyGPS++ library
#include <SoftwareSerial.h>    // Include the SoftwareSerial library

#define RX_PIN 10    // GPS module RX pin connected to Arduino digital pin 10
#define TX_PIN 11    // GPS module TX pin connected to Arduino digital pin 11

SoftwareSerial gpsSerial(RX_PIN, TX_PIN);    // Create a SoftwareSerial object for GPS module communication
TinyGPSPlus gps;    // Create a TinyGPS++ object for parsing GPS data

void setup() {
  Serial.begin(9600);    // Start serial communication with PC
  gpsSerial.begin(9600);    // Start serial communication with GPS module
}

void loop() {
  while (gpsSerial.available() > 0) {    // Check if there is GPS data available
    if (gps.encode(gpsSerial.read())) {    // Parse GPS data
      Serial.print("Latitude: ");
      Serial.println(gps.location.lat(), 6);    // Display latitude with 6 decimal places
      Serial.print("Longitude: ");
      Serial.println(gps.location.lng(), 6);    // Display longitude with 6 decimal places
      Serial.print("Altitude: ");
      Serial.print(gps.altitude.meters(), 1);    // Display altitude in meters with 1 decimal place
      Serial.println(" m");
      Serial.print("Speed: ");
      Serial.print(gps.speed.kmph(), 1);    // Display speed in km/h with 1 decimal place
      Serial.println(" km/h");
      Serial.print("Date: ");
      Serial.print(gps.date.day());
      Serial.print("/");
      Serial.print(gps.date.month());
      Serial.print("/");
      Serial.println(gps.date.year());    // Display date in format "DD/MM/YYYY"
      Serial.print("Time: ");
      Serial.print(gps.time.hour());
      Serial.print(":");
      Serial.print(gps.time.minute());
      Serial.print(":");
      Serial.print(gps.time.second());
      Serial.print(".");
      Serial.println(gps.time.centisecond());    // Display time in format "HH:MM:SS.ss"
      Serial.println();
    }
  }
}
