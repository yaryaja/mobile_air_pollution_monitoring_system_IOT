void loop() {
  // put your main code here, to run repeatedly:


  // If Blynk is not connected, attempt to reconnect every 5 seconds
  if (!Blynk.connected()) {
    Serial.println("Blynk disconnected, attempting to reconnect...");
    if (Blynk.connect()) {
      Serial.println("Reconnected to Blynk!");
    } else {
      Serial.println("Reconnection to Blynk failed!");
    }
    delay(5000);
  }

  // Your existing code for reading sensor data and sending it to Blynk here...
}
