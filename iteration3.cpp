int fadeValue;

void setup() {
  pinMode(A1, INPUT);
  pinMode(3, OUTPUT);  // White LED
  pinMode(4, OUTPUT);  // Red LED
  pinMode(6, OUTPUT);  // Buzzer indicator
  pinMode(5, INPUT);   // Button
  pinMode(12, OUTPUT); // Buzzer
  digitalWrite(3, LOW); 
  digitalWrite(4, LOW);
  Serial.begin(9600); // Start Serial communication
}

void loop() {
  int sensorValue = analogRead(A1);
  Serial.println(sensorValue);
  
  long totalFadeTime = map(sensorValue, 0, 1023, 60000, 300000); // Map to 1-5 minutes
  Serial.print("Total Fade Time (ms): ");
  Serial.println(totalFadeTime);
  
  int fadeDelay = totalFadeTime / 255; 
  long lastMinuteStart = totalFadeTime - 60000; 
  bool indOn = true;
  if (digitalRead(5) == HIGH) { // Check if the button is pressed
    unsigned long startTime = millis(); // Record the start time

    while (millis() - startTime < totalFadeTime) {
      // Calculate remaining time
      unsigned long elapsedTime = millis() - startTime;

      // Handle white LED for the last minute
      if (elapsedTime >= lastMinuteStart) {
        if (indOn){
        	tone(12, 261);
            indOn = false;
          	noTone(12);
        }
        digitalWrite(3, HIGH); // Turn on the white LED
      }

      // Fade the red LED
      fadeValue = 255 - (elapsedTime * 255 / totalFadeTime); // Linear fade
      analogWrite(4, fadeValue);

      // Debugging output
      Serial.print("Elapsed Time: ");
      Serial.println(elapsedTime);
      Serial.print("Fade Value: ");
      Serial.println(fadeValue);

      delay(fadeDelay);
    }

    // Reset LEDs and start buzzer notification
    digitalWrite(3, LOW); 
    tone(12, 261); // Buzzer tone
    for (int i = 0; i <= 20; i++) {
      digitalWrite(6, HIGH);
      delay(100);
      digitalWrite(6, LOW);
      delay(100);
    }
    noTone(12);
  } else {
    // Reset LEDs and buzzer if the button is not pressed
    digitalWrite(4, LOW);
    digitalWrite(3, LOW);
    digitalWrite(6, LOW);
  }
}
