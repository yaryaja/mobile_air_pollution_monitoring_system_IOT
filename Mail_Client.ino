#include <WiFi.h>
#include <WiFiClient.h>
#include <ESP32Mail.h>  // Library for sending emails

// Replace with your network credentials
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

// SMTP server credentials
#define SMTP_SERVER "your_SMTP_server"
#define SMTP_PORT 587
#define EMAIL_USER "your_email_address"
#define EMAIL_PASSWORD "your_email_password"
#define EMAIL_FROM "your_email_address"
#define EMAIL_TO "recipient_email_address"

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("WiFi connected!");
}

void loop() {
  // Measure temperature and check if it's above 50 degrees
  float temp = getTemperature();  // Replace with your temperature measurement code
  if (temp > 50.0) {
    // Send email
    Serial.println("Sending email...");
    WiFiClient client;
    MailClient mail(client, SMTP_SERVER, SMTP_PORT, EMAIL_USER, EMAIL_PASSWORD);
    String subject = "Temperature Alert!";
    String body = "The temperature has exceeded 50 degrees!";
    String from = EMAIL_FROM;
    String to = EMAIL_TO;
    if (mail.send(subject, body, from, to)) {
      Serial.println("Email sent successfully!");
    } else {
      Serial.println("Email sending failed.");
    }
  }
  delay(1000);  // Wait for 1 second before checking temperature again
}

float getTemperature() {
  // Replace with your temperature measurement code
  // This is just an example that returns a random value between 0 and 100
  return random(0, 100);
}
