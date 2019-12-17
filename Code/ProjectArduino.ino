#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define servoPin 2
#define SERVOMIN2  105 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX2  120 // This is the 'maximum' pulse length count (out of 4096)
#define SERVOMIN4  110 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX4  120
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates
// our servo # counter
uint8_t servonum = 1;
int servospeed = 2;
int temp=0;

//https://maker.pro/arduino/tutorial/how-to-make-arduino-and-processing-ide-communicate

void setup() { 
  Serial.begin(9600);
  Serial.println("8 channel Servo test!");

  pwm.begin();
  pwm.setOscillatorFrequency(27000000);  // The int.osc. is closer to 27MHz  
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  delay(10);
}

void loop() {
 for (int pos = 0; pos <= 180; pos += 1) {
    Servo1.write(pos);  
    delay(10);                 
  }
  Servo1.write(0); 
  delay(1000);
 /* check if data has been sent from the computer: */
 if (Serial.available()) {
 
 /* read the most recent byte */
 String byteRead = Serial.readString();
 int space=byteRead.indexOf(" ");
 int note=byteRead.substring(0, space).toInt();
 int velocity=byteRead.substring(space+1).toInt();
 
 if(velocity!=0)
 {
  temp=note;
  digitalWrite(note, HIGH); 
 } 
 else
  digitalWrite(temp, LOW); 
 }
 }
/*

void loop() {
  // Drive each servo one at a time using setPWM()
  servonum = 1;
  
  //if(servospeed > 6)
  //servospeed = 2;
  
  Serial.println(servonum);
  for (uint16_t pulselen = SERVOMAX2; pulselen > SERVOMIN2; pulselen--) {
    pwm.setPWM(servonum, 0, pulselen);
    delay(servospeed);
  }

  for (uint16_t pulselen = SERVOMIN2; pulselen < SERVOMAX2; pulselen++) {
    pwm.setPWM(servonum, 0, pulselen);
    delay(servospeed);
  }

  servonum = 3;

  Serial.println(servonum);

  delay(500);
  for (uint16_t pulselen = SERVOMAX4; pulselen > SERVOMIN4; pulselen--) {
    pwm.setPWM(servonum, 0, pulselen);
    delay(servospeed);
  }

  Serial.println(servonum);
  for (uint16_t pulselen = SERVOMIN4; pulselen < SERVOMAX4; pulselen++) {
    pwm.setPWM(servonum, 0, pulselen);
    delay(servospeed);
  }

  delay(500);

  //servospeed += 1;
}*/
