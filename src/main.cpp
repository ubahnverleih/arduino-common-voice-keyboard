#include <Arduino.h>
#include <Keyboard.h>

bool keyState[8];
String chars[8] = { "1", "2", "3", "4", "5", "\n", "ü", "a" };
byte keyPins[8] = { PIN2, PIN3, PIN4, PIN5, PIN6, PINB7, 8, 9 };


int lastMillis = millis();

void setup() {
  Serial.begin(9600);
  delay(1000);
  Serial.println("START");
  delay(2*1000);
  Serial.println("start keyboard");
  delay(1000);
  Keyboard.begin();
  
  

  for (int i = 0; i < 8; i++){
    pinMode(keyPins[i], INPUT_PULLUP);
  }
}

void loop() {
  for (int i = 0; i < 8; i++){
    bool value = digitalRead(keyPins[i]);
    if (value < keyState[i]){
      Serial.print(chars[i]);
      Serial.println();
      
      // zeitabstand checken 
      if ((millis() - lastMillis) > 800){
        lastMillis = millis();
        //fix for ü
        if (chars[i].compareTo("ü") == 0){
          Keyboard.write(91);
        } else {
          Keyboard.write(chars[i].charAt(0));
        }
      }
    }
    keyState[i] = value;
    delay(10);
  }
}