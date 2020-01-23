/////////////////////////////////////////////////////////////////////////////////////////////////
//SENIOR RESEARCH PROJECT - JASON PAK AND DAVID CHA
/////////////////////////////////////////////////////////////////////////////////////////////////

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

//Instantiate Notes - (servo num, dynamic, min)
//Note test = Note(0, 2, 122);
//Note g = Note(0, 2, 106);
//Note a = Note(1, 2, 133);
//Note b = Note(2, 2, 105);
//Note c = Note(3, 2, 135);
//Note d = Note(4, 2, 141);
//Note e = Note(5, 2, 105);
//Note f = Note(6, 2, 132);
//Note g2 = Note(7, 2, 122);


Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
//Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x40);
//Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(0x41);

int temp=0;

void setup() { 
  Serial.begin(9600);
  pwm.begin();
  pwm.setOscillatorFrequency(27000000); 
  pwm.setPWMFreq(SERVO_FREQ);
  //pwm1.begin();
  //pwm1.setPWMFreq(1600);
  //pwm2.begin();
  //pwm2.setPWMFreq(1600);
  delay(10);
}

void loop() {
 /* check if data has been sent from the computer: */
 
  //reset dynamic back to forte (2) after reaching piano (6)
  //if(test.getDynamic() > 7) 
  //{
  //  test.setDynamic(2);
  //}

  if (Serial.available()) {
  String byteRead = Serial.readString();
  int space=byteRead.indexOf(" ");
  int note=byteRead.substring(0, space).toInt();
  int velocity=byteRead.substring(space+1).toInt();
  //if(velocity<32)
    //setDynamic(2);
  
  //test.playNote(500);

  delay(1000); 

  //test.setDynamic(test.getDynamic() + 2); 
} 
}
/////////////////////////////////////////////////////////////////////////////////////////////////
//NOTE CLASS - special class written for simpler coding 
//Each "Note" represents on key on the xylophone
/////////////////////////////////////////////////////////////////////////////////////////////////

class Note {
private:
 int servonum; // 0 - 16 on PCA9685
 int dynamic; // 2 - forte, 4 - mf/mp, 6 - piano
 int minval;  //servo value at which mallet touches key
 int maxval; //servo value to which mallet comes up to after touching key

public:
 Note(int a, int b, int c) {   
 this -> servonum = a;
 this->dynamic = b;
 this->minval = c;
 this->maxval = c + (60 / dynamic); //adjusts maxvalue depending on dynamic level
}
 
void Note::playNote(int dur) //plays the note for given duration (millisec)
{
  for (uint16_t pulselen = this->maxval; pulselen > this->minval; pulselen--) {
    pwm.setPWM(this->servonum, 0, pulselen);
    delay(this->dynamic);
  }

  for (uint16_t pulselen = this->minval; pulselen < this->maxval; pulselen++) {
    pwm.setPWM(this->servonum, 0, pulselen);
    delay(this->dynamic);
  }

  delay(dur);
 return;
}

int Note::getMin()
{
 return minval;
}

int Note::getMax()
{
 return maxval;
}

int Note::getServo()
{
 return servonum;
}

int Note::getDynamic()
{
 return dynamic;
}

void Note::setDynamic(int x) //when updating the dynamic, the maxval adjusts accordingly as well
{
  dynamic = x;
  maxval = minval + (60 / x);
}
};
