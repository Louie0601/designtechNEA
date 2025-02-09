// C++ code
//

int fadeValue;

void setup()
{
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(5,INPUT);
  pinMode(12,OUTPUT);
  digitalWrite(4, LOW);
}


void loop()
{
  if (digitalRead(5)==HIGH){
    for (fadeValue = 255; fadeValue >= 0; --fadeValue){
      if (fadeValue > 125){
    	analogWrite(4, fadeValue);
        delay(250);
      } else {
      	analogWrite(4, fadeValue);
        delay(50);
        digitalWrite(3,HIGH);
      }
    }
    digitalWrite(3,LOW);
    tone(12,261);
    for (int i = 0; i <= 20; i++){
      	
    	digitalWrite(6,HIGH);
    	delay(100);
    	digitalWrite(6,LOW);
      	delay(100);
    }
    noTone(12);
  } else {
  	digitalWrite(4,LOW);
    digitalWrite(6,LOW);
  }
}
