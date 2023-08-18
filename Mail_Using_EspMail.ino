#include <WiFi.h>
#include <esp_mail.h>

#define WIFI_SSID "your_wifi_ssid"
#define WIFI_PASS "your_wifi_password"
#define SMTP_SERVER "smtp.gmail.com"
#define SMTP_PORT 465
#define EMAIL_FROM "your_email_address"
#define EMAIL_PASSWORD "your_email_password"
#define EMAIL_TO "recipient_email_address"
#define SUBJECT "Temperature Alert"

float temperature;

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Start email library
  esp_mail_init(SMTP_SERVER, SMTP_PORT, EMAIL_FROM, EMAIL_PASSWORD);

  // Set up temperature sensor
  // code to read temperature from sensor
}

void loop() {
  // Read temperature from sensor
  // code to read temperature from sensor

  if (temperature > 50) {
    // Compose email message
    String message = "Temperature has exceeded 50 degrees Celsius! Current temperature is: ";
    message += String(temperature);
    message += " degrees Celsius.";

    // Send email
    bool success = esp_mail_send(EMAIL_TO, SUBJECT, message.c_str());

    if (success) {
      Serial.println("Email sent successfully");
    } else {
      Serial.println("Error sending email");
    }
  }

  // Wait for some time before checking temperature again
  delay(5000);
}
