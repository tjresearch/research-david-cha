#include <Servo.h>

#define servoPin 2
int temp=0;

//https://maker.pro/arduino/tutorial/how-to-make-arduino-and-processing-ide-communicate
Servo Servo1;

void setup() { 
Servo1.attach(servoPin);
Servo1.write(0);
Serial.begin(9600);
}

void loop() {
 int byteRead;
 for (int pos = 0; pos <= 180; pos += 1) {
    Servo1.write(pos);  
    delay(10);                 
  }
  Servo1.write(0); 
  delay(1000);
 /* check if data has been sent from the computer: */
 if (Serial.available()) {
 
 /* read the most recent byte */
 byteRead = Serial.read();
 
 if(byteRead!=0)
 {
  temp=byteRead;
  digitalWrite(byteRead, HIGH); 
 }
 
 if(byteRead==0)
  digitalWrite(temp, LOW); 
 }
 }
