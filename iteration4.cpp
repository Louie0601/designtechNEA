#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

#define POT A1
#define BUT 8
Adafruit_NeoPixel strip = Adafruit_NeoPixel(12, 6, NEO_RGB + NEO_KHZ800);

void setup() {
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code

  strip.begin();
  strip.show();
  pinMode(POT, INPUT);
  pinMode(BUT, INPUT);   // Button
  pinMode(4, OUTPUT); // Buzzer
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(A1);
  Serial.println(sensorValue);
  long totalTime = map(sensorValue, 1023, 0, 60000, 300000); // Map to 1-5 minutes
    Serial.print("Total Time (ms): ");
  Serial.println(totalTime);
  long firstTime = totalTime - 60000; 
  
  if (digitalRead(BUT) == HIGH) { // Check if the button is pressed
    colorWipe(strip.Color(255, 0, 0), firstTime/16);
    colorWipe(strip.Color(0, 0, 255), 60000/16); 
    digitalWrite(4,HIGH);
    rainbowCycle(5);
    digitalWrite(4,LOW);
  } else {
    // Reset LEDs and buzzer if the button is not pressed
    //digitalWrite(4, LOW);
    //digitalWrite(3, LOW);
    //digitalWrite(6, LOW);
  }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, int wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbowCycle(int wait) {
  int i, j;
  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
