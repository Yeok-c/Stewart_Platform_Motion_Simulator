#include "Wire.h"
#include "Adafruit_PWMServoDriver.h"
Adafruit_PWMServoDriver board1 = Adafruit_PWMServoDriver(0x40);

// Servo Test Code: Modified slightly from RoboJax

// Depending on your servo make, the pulse width min and max may vary, you
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!
// Watch video V1 to understand the two lines below: http://youtu.be/y8X9X10Tn1k

#define SERVOMIN  250 //125 // 687 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  1148 // 574 //3162 // this is the 'maximum' pulse length count (out of 4096)


int servoNumber = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("32 channel Servo test!");

  board1.begin();
  board1.setPWMFreq(120);  // Analog servos run at ~60 Hz updates
}

// the code inside loop() has been updated by Robojax
void loop() {
    setAll(0); delay(1000);
    setAll(90); delay(1000);
    setAll(180); delay(1000);
  //
  //  for(int ANGLE = 700; ANGLE <=1200; ANGLE++){
  //    float angle_issue = ANGLE/10.0;
  //    Serial.print("angle_issue: "); Serial.println(angle_issue);
  //    setAll(angle_issue); delay(5);
  //  }
}

/*
   angleToPulse(int ang)
   gets angle in degree and returns the pulse width
   also prints the value on seial monitor
   written by Ahmad Nejrabi for Robojax, Robojax.com
*/
int angleToPulse(float ang) {
  float pulse = ang / 180 * (SERVOMAX - SERVOMIN) + SERVOMIN;
  Serial.print("Angle: "); Serial.print(ang);
  Serial.print(" pulse: "); Serial.println(pulse);
  return int(pulse);
}

void setAll(float angle) {
  Serial.print("Set angle to: "); Serial.println(angle);
  for (int i = 0; i <= 6; i++) {
    board1.setPWM(i, 0, angleToPulse(angle) );
  }
}
