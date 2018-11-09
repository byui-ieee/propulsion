#include <Servo.h>


//#include Servo ESC1;
Servo ESC1;

int pos = 0; //Sets position variable

void arm(){
  setSpeed(0); //Sets speed variable delay(1000);
}

void setSpeed(int value){
  int angle = map(value, 0, 100, 0, 180); //Sets servo positions to different speeds ESC1.write(angle);
}

void setup() {
  ESC1.attach(5); //Adds ESC to certain pin. arm();
  Serial.begin(9600);
  ESC1.writeMicroseconds(0);
  delay (500);
}

void loop() {
  int value = map( analogRead(0), 0, 1024, 0, 2000);
  Serial.println(value);
//  value = 1800;
  ESC1.writeMicroseconds(value);
  delay(100);
}
