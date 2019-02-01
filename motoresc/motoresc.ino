#include <Servo.h>

//#include Servo ESC1;
Servo ESC1;            // Right top motor for up/down
Servo ESC2;            // Right bottom motor for up/down
Servo ESC3;            // Left top motor for down
Servo ESC4;            // Left bottom motor for up/down

// define control pins for motors. They have to be on the PWM pins.
#define RFRONT 3        // Right front motor on pin 3
#define RBACK 5         // Right back motor on pin 5
#define LFRONT 6        // Left front motor on pin 6
#define LBACK 9         // Left back motor on pin 9

// directional instructions. Values can be changed when we know what we will be receiving from the pi.
#define PITCH_FORWARD 'w'
#define PITCH_BACKWARD 's'
#define GO_UP 'q'
#define GO_DOWN 'e'
#define GO_RIGHT 'l'
#define GO_LEFT 'j'
#define GO_FORWARD 'i'
#define GO_BACKWARD 'k'
int command = 0;

#define forward 1600
#define backward 1000
#define stay 1500

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
}

/************************************************
 * 
 * 
 ************************************************/
void setup() {
  ESC1.attach(RFRONT); //Adds ESC to certain pin. arm();
  ESC2.attach(RBACK);
  ESC3.attach(LFRONT);
  ESC4.attach(LBACK);
  Serial.begin(9600);
  ESC1.writeMicroseconds(stay);
  ESC2.writeMicroseconds(stay);
  ESC3.writeMicroseconds(stay);
  ESC4.writeMicroseconds(stay);
  delay(7000);
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
      delay(7000);
      setMotorSpeed(stay, stay, stay, stay, forward, forward);            // set both thrusters forward to move sub forward
      break;
    case GO_BACKWARD:
      setMotorSpeed(stay, stay, stay, stay, stay, stay);
      delay(7000);
      setMotorSpeed(stay, stay, stay, stay, backward, backward);          // set both thrusters backward to move sub backward
      break;
    case GO_LEFT:
      setMotorSpeed(stay, stay, stay, stay, stay, stay);
      delay(7000);
      setMotorSpeed(stay, stay, stay, stay, forward, backward);           // set left thruster backward and right thruster forward to turn left
      break;
    case GO_RIGHT:
      setMotorSpeed(stay, stay, stay, stay, stay, stay);
      delay(7000);
      setMotorSpeed(stay, stay, stay, stay, backward, forward);           // set left thruster forward and right thruster backward to turn right
      break;
    case PITCH_FORWARD:
      setMotorSpeed(stay, stay, stay, stay, stay, stay);
      delay(7000);
      setMotorSpeed(backward, stay, backward, stay, stay, stay);         // set front top motors backward to pitch forward 
      break;
    case PITCH_BACKWARD:
      setMotorSpeed(stay, stay, stay, stay, stay, stay);
      delay(7000);
      setMotorSpeed(forward, stay, forward, stay, stay, stay);           // set front top motors forward to pitch backward
      break;
    case GO_UP:
      setMotorSpeed(stay, stay, stay, stay, stay, stay);
      delay(7000);
      setMotorSpeed(forward, forward, forward, forward, stay, stay);     // set all top motors forward to move upward
      break;
    case GO_DOWN:
      setMotorSpeed(stay, stay, stay, stay, stay, stay);
      delay(7000);
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
