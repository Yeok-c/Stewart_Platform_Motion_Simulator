#include "Wire.h"
#include "Adafruit_PWMServoDriver.h"
Adafruit_PWMServoDriver board1 = Adafruit_PWMServoDriver(0x40);

// Depending on your servo make, the pulse width min and max may vary, you 
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!
// Watch video V1 to understand the two lines below: http://youtu.be/y8X9X10Tn1k
#define SERVOMIN  250 // 687 // 125 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  1148 //3162 //575 // this is the 'maximum' pulse length count (out of 4096)

const byte numChars = 50;
char receivedChars[numChars];
char tempChars[numChars];        // temporary array for use when parsing

float ANGLE[6] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

      // variables to hold the parsed data
char messageFromPC[numChars] = {0};
int integerFromPC = 0;

float ANGLE1 = 0;
float ANGLE2 = 0;
float ANGLE3 = 0;
float ANGLE4 = 0;
float ANGLE5 = 0;
float ANGLE6 = 0;

boolean newData = false;

//============

void setup() {  
    board1.begin();
    board1.setPWMFreq(120);  // Analog servos run at ~60 Hz updates
    Serial.begin(38400);
    
    Serial.println("Yeok's Stewart Platform Program: Send data in form of <Angles, 12.1, 10.1, 23.1, 12.0, 25.4, 150.1>  ");
    Serial.println();
}

//============

void loop() {
  recvWithStartEndMarkers();
  if (newData == true) {
      strcpy(tempChars, receivedChars);
          // this temporary copy is necessary to protect the original data
          //   because strtok() used in parseData() replaces the commas with \0
      parseData();
//      showParsedData();
      newData = false;
  }
  showAngles();
  board1.setPWM(5, 0, angleToPulse(90.0-ANGLE1) ); 
  board1.setPWM(4, 0, angleToPulse(90.0+ANGLE2) );
  board1.setPWM(3, 0, angleToPulse(90.0-ANGLE3) );
  board1.setPWM(2, 0, angleToPulse(90.0+ANGLE4) );
  board1.setPWM(1, 0, angleToPulse(90.0-ANGLE5) );
  board1.setPWM(0, 0, angleToPulse(90.0+ANGLE6) );
}

//============ Servo Functions =============

int angleToPulse(float ang){
//   int pulse = map(ang,0, 180, SERVOMIN,SERVOMAX);// map angle of 0 to 180 to Servo min and Servo max 

   float pulse = ang/180*(SERVOMAX-SERVOMIN) + SERVOMIN;
//   Serial.print("Angle: ");Serial.print(ang);
//   Serial.print(" pulse: ");Serial.println(pulse);
   return int(pulse);
}

int setAll(float angle){
  Serial.print("Set angle to: "); Serial.println(angle);
  for(int i=0; i<=6; i++){      
    board1.setPWM(i, 0, angleToPulse(angle) );
  }
}

//============

void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;

    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}

//============

void parseData() {      // split the data into its parts
    char * strtokIndx; // this is used by strtok() as an index

    strtokIndx = strtok(tempChars,",");      // get the first part - the string
    strcpy(messageFromPC, strtokIndx); // copy it to messageFromPC

    strtokIndx = strtok(NULL, ",");
    ANGLE1 = atof(strtokIndx);     // convert this part to a float
    
    strtokIndx = strtok(NULL, ",");
    ANGLE2 = atof(strtokIndx);     // convert this part to a float
    
    strtokIndx = strtok(NULL, ",");
    ANGLE3 = atof(strtokIndx);     // convert this part to a float
    
    strtokIndx = strtok(NULL, ",");
    ANGLE4 = atof(strtokIndx);     // convert this part to a float
    
    strtokIndx = strtok(NULL, ",");
    ANGLE5 = atof(strtokIndx);     // convert this part to a float
    
    strtokIndx = strtok(NULL, ",");
    ANGLE6 = atof(strtokIndx);     // convert this part to a float

}

//============
void showAngles(){
  Serial.print("Angles: "); 
  Serial.print(ANGLE1); Serial.print(", ");
  Serial.print(ANGLE2); Serial.print(", ");
  Serial.print(ANGLE3); Serial.print(", ");
  Serial.print(ANGLE4); Serial.print(", ");
  Serial.print(ANGLE5); Serial.print(", ");
  Serial.print(ANGLE6); Serial.print(", ");
  Serial.println("");
}
//
//void showParsedData() {
//    Serial.print("Header: ");
//    Serial.println(messageFromPC);
//    
//    Serial.print("Float(1)");
//    Serial.println(ANGLE1);
//
//    Serial.print("Float(2)");
//    Serial.println(ANGLE2);
//
//    Serial.print("Float(3)");
//    Serial.println(ANGLE3);
//
//    Serial.print("Float(4)");
//    Serial.println(ANGLE4);
//
//    Serial.print("Float(5)");
//    Serial.println(ANGLE5);
//
//    Serial.print("Float(6)");
//    Serial.println(ANGLE6);
//}
