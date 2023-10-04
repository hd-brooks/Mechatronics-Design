
//ARDUINO OBSTACLE AVOIDING CAR//
// Before uploading the code you have to install the necessary library//
//AFMotor Library https://learn.adafruit.com/adafruit-motor-shield/library-install //
//NewPing Library https://github.com/livetronic/Arduino-NewPing// 
//Servo Library https://github.com/arduino-libraries/Servo.git //
// To Install the libraries go to sketch >> Include Library >> Add .ZIP File >> Select the Downloaded ZIP files From the Above links //


#include <AFMotor.h>  
#include <NewPing.h>
#include <Servo.h> 

#define TRIG_PIN A0 
#define ECHO_PIN A1 
#define MAX_DISTANCE 200 
#define MAX_SPEED 175 // sets speed of DC  motors
#define MAX_SPEED_OFFSET 20

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 

AF_DCMotor motor1(1, MOTOR12_1KHZ); 
AF_DCMotor motor3(3, MOTOR34_1KHZ);

Servo myservo;   
Servo myservo2;

boolean goesForward=false;
boolean parkTime=true;
int distance = 100;
int speedSet = 0;
int pos = 0;
int turnCount = 0;

void setup() {

  myservo.attach(9);
  myservo2.attach(10);  
  //myservo2.write(0);
  //myservo.write(0);  
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop() {

  delay(100);
  if(turnCount <3){
  moveForward();
  }
  if (distance<=25){
    moveStop();
    delay(500);
    turnLeft();
    moveBackward();
    turnCount++;
      if(turnCount ==3 ){//
        moveStop();
        delay(500);
        forwardLoop();
        delay(1000);
        backLoop();
      }
  }
 distance = readPing();
 
}

int readPing() { 
  delay(70);
  int cm = sonar.ping_cm();
  if(cm==0)
  {
    cm = 250;
  }
  return cm;
}

void moveStop() {
  motor1.run(RELEASE); 
  motor3.run(RELEASE);
  } 
  
void moveForward() {
  if(!goesForward){
    goesForward=true;
    motor1.run(FORWARD);      
    motor3.run(FORWARD);  
    for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2){ // slowly bring the speed up to avoid loading down the batteries too quickly
      motor1.setSpeed(speedSet);
      motor3.setSpeed(speedSet);
      delay(5);
    }
  }
}

void moveBackward() {
    goesForward=false;
    motor1.run(BACKWARD);      
    motor3.run(BACKWARD);  
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2){ // slowly bring the speed up to avoid loading down the batteries too quickly
    motor1.setSpeed(speedSet);
    motor3.setSpeed(speedSet);
    delay(5);
  }
}  

void forwardLoop(){
  for (pos = 0; pos <= 95; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
    myservo.write(95-pos);
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}

void backLoop(){
  for (pos = 95; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    // in steps of 1 degree
    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
    myservo.write(95-pos);
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}

void turnLeft() {
  motor1.run(BACKWARD);     
  motor3.run(FORWARD);   
  delay(500);
  motor1.run(FORWARD);     
  motor3.run(FORWARD);
}  

void turnRight() {
  motor1.run(FORWARD);
  motor3.run(FORWARD);     
  delay(500);
  motor1.run(FORWARD);      
  motor3.run(FORWARD);     
} 
