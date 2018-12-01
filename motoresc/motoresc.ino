#include <Servo.h>

//#include Servo ESC1;
Servo ESC1;            // Right top motor for up/down
Servo ESC2;            // Right bottom motor for up/down
Servo ESC3;            // Left top motor for down
Servo ESC4;            // Left bottom motor for up/down
Servo ESC5;            // Left motor for forward/backward
Servo ESC6;            // Right motor for forward/backward

// define control pins for motors. They have to be on the PWM pins.
#define RFRONT 3        // Right front motor on pin 3
#define RBACK 5         // Right back motor on pin 5
#define LFRONT 6        // Left front motor on pin 6
#define LBACK 9         // Left back motor on pin 9
#define RIGHT 10        // Left motor on pin 10
#define LEFT 11         // Right motor on pin 11

// directional instructions. Values can be changed when we know what we will be receiving from the pi.
const char ROLL_RIGHT = 'd';
const char ROLL_LEFT = 'a';
const char PITCH_FORWARD = 'w';
const char PITCH_BACKWARD = 's';
const char GO_UP = 'q';
const char GO_DOWN = 'e';
const char GO_RIGHT = 'l';
const char GO_LEFT = 'j';
const char GO_FORWARD = 'i';
const char GO_BACKWARD = 'k';
char command = 0;

const int forward = 1600;
const int backward = 1000;
const int stay = 1450;

int pos = 0; //Sets position variable

void arm(){
  setSpeed(0); //Sets speed variable delay(1000);
}

void setSpeed(int value){
  int angle = map(value, 0, 100, 0, 180); //Sets servo positions to different speeds ESC1.write(angle);
}

/*****************************************************************
 * SET MOTOR SPEED
 * Sets the speed of each individual motor.
 ****************************************************************/
void setMotorSpeed(int rFront, int rBack, int lFront, int lBack, int right, int left)
{
  ESC1.writeMicroseconds(rFront);
  ESC2.writeMicroseconds(rBack);
  ESC3.writeMicroseconds(lFront);
  ESC4.writeMicroseconds(lBack);
  ESC5.writeMicroseconds(right);
  ESC6.writeMicroseconds(left);
}

void setup() {
  ESC1.attach(RFRONT); //Adds ESC to certain pin. arm();
  ESC2.attach(RBACK);
  ESC3.attach(LFRONT);
  ESC4.attach(LBACK);
  ESC5.attach(RIGHT);
  ESC6.attach(LEFT);
  Serial.begin(9600);
  ESC1.writeMicroseconds(1450);
  ESC2.writeMicroseconds(1450);
  ESC3.writeMicroseconds(1450);
  ESC4.writeMicroseconds(1450);
  ESC5.writeMicroseconds(1450);
  ESC6.writeMicroseconds(1450);
  delay (500);
}

void loop() {
  if(Serial.available() > 0)
  {
    command = Serial.read();  
  }
//  int Rvalue = map(analogRead(0), 0, 1024, 0, 2000);
//  Serial.println(Rvalue);

// right now we're using fixed values for the motors so no variable speeds for now.
  switch(command)
  {
    case GO_FORWARD:
      setMotorSpeed(stay, stay, stay, stay, stay, stay);
      setMotorSpeed(stay, stay, stay, stay, forward, forward);           // set both thrusters forward to move sub forward
      break;
    case GO_BACKWARD:
      setMotorSpeed(stay, stay, stay, stay, stay, stay);
      setMotorSpeed(stay, stay, stay, stay, backward, backward);           // set both thrusters backward to move sub backward
      break;
    case GO_LEFT:
      setMotorSpeed(stay, stay, stay, stay, stay, stay);
      setMotorSpeed(stay, stay, stay, stay, forward, backward);           // set left thruster backward and right thruster forward to turn left
      break;
    case GO_RIGHT:
      setMotorSpeed(stay, stay, stay, stay, stay, stay);
      setMotorSpeed(stay, stay, stay, stay, backward, forward);           // set left thruster forward and right thruster backward to turn right
      break;
    case ROLL_RIGHT:
      setMotorSpeed(stay, stay, stay, stay, stay, stay);
      setMotorSpeed(backward, backward, forward, forward, stay, stay);   // set right top motors backward and left top motors forward to roll right
      break;
    case ROLL_LEFT:
      setMotorSpeed(stay, stay, stay, stay, stay, stay);
      setMotorSpeed(backward, backward, forward, forward, stay, stay);   // set right top motors forward and left top motors backward to roll left
      break;
    case PITCH_FORWARD:
      setMotorSpeed(stay, stay, stay, stay, stay, stay);
      setMotorSpeed(backward, stay, backward, stay, stay, stay);         // set front top motors backward to pitch forward 
      break;
    case PITCH_BACKWARD:
      setMotorSpeed(stay, stay, stay, stay, stay, stay);
      setMotorSpeed(forward, stay, forward, stay, stay, stay);           // set front top motors forward to pitch backward
      break;
    case GO_UP:
      setMotorSpeed(stay, stay, stay, stay, stay, stay);
      setMotorSpeed(forward, forward, forward, forward, stay, stay);     // set all top motors forward to move upward
      break;
    case GO_DOWN:
      setMotorSpeed(stay, stay, stay, stay, stay, stay);
      setMotorSpeed(backward, backward, backward, backward, stay, stay); // set all top motorw backward to move downward
      break;
    case 'v':
      setMotorSpeed(stay, stay, stay, stay, stay, stay); // set all top motorw backward to move downward
      break;
    default:
      //setMotorSpeed(stay, stay, stay, stay, stay, stay);                 // turn all motors off
      break;
  }
  delay(100);
}
