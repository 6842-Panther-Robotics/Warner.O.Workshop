#include "main.h"

//18:1 green
//36:1 red
//6:1 blue (06)
//define inertail

pros::Imu inertail(5);
//Define Motors
pros::Motor rightFront (1, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor rightBack (2, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor leftFront (3, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor leftBack (4, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);

void wait(int time) {
  //milliseconds
  pros::delay(time);
}
//varible defo
int TICS_PER_REVOLUTION = 360;
double WHEEL_DIAMETER = 4;
double pi = 3.14159;

double CORRECTION_FACTOR = 0.8;
int THRESHHOLD = -5;

PIDController movePID(0.1, 30);
PIDController turnPID(2.5, 30);

void timedDrive(int time, int speed) {
  right(speed);
  left(speed);
  wait(time);
  right(0);
  left(0);
}

void left(int speed) {
  leftFront.move(speed);
  leftBack.move(speed);
}

void right(int speed) {
  rightFront.move(speed);
  rightBack.move(speed);
}

void hold() {
  rightFront.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  rightBack.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  leftFront.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  leftBack.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void coast() {
  rightFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  rightBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  leftFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  leftBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}

void moveForward (int inches){
  rightFront.tare_position();
  leftFront.tare_position();

  int time = 0;

  double target = TICS_PER_REVOLUTION * (inches / (WHEEL_DIAMETER * pi));

  while(time < 50) {

    int rightFrontPosition = rightFront.get_position();
    int leftFrontPosition = leftFront.get_position();

    int PIDSpeed = movePID.getSpeedToMotor(target, rightFront.get_position());

    if(rightFrontPosition - leftFrontPosition < THRESHHOLD){
      right(PIDSpeed);
      left(PIDSpeed * CORRECTION_FACTOR);
    }
    else if (leftFrontPosition - rightFrontPosition <= THRESHHOLD){
      right(PIDSpeed * CORRECTION_FACTOR);
      left(PIDSpeed);
    }
    else {
    left(PIDSpeed);
    right(PIDSpeed);
    }

    if(fabs(movePID.getError()) < 1) {
      time++;
      wait(2);
    }
    }
    right(0);
    left(0);
 }

 void moveBackWards (int inches){
   rightFront.tare_position();
   leftFront.tare_position();

   double target = TICS_PER_REVOLUTION * (inches / (WHEEL_DIAMETER * pi));

   int time = 0;

   while(time < 50) {

     int rightFrontPosition = rightFront.get_position();
     int leftFrontPosition = leftFront.get_position();

     int PIDSpeed = movePID.getSpeedToMotor(target, rightFront.get_position());

     if(rightFrontPosition - leftFrontPosition < -THRESHHOLD){
       right(-PIDSpeed);
       left(-PIDSpeed * CORRECTION_FACTOR);
     }
     else if (leftFrontPosition - rightFrontPosition <= -THRESHHOLD){
       right(-PIDSpeed * CORRECTION_FACTOR);
       left(-PIDSpeed);
     }
     else {
       right(-PIDSpeed);
       left(-PIDSpeed);
     }

     if(fabs(movePID.getError()) < 1) {
       time++;
       wait(2);
     }
     }
     right(0);
     left(0);
  }

//turn right for degrees

void turn(int degrees){

  int time = 0;

  while(time < 50) {

  left(turnPID.getSpeedToMotor(degrees, inertail.get_rotation()));
  right(-turnPID.getSpeedToMotor(degrees, inertail.get_rotation()));

  if(fabs(turnPID.getError()) < 1) {
  time++;
  wait(2);
    }
 }
 right(0);
 left(0);
}

void driveOP(){

  leftBack.move(master.get_analog(ANALOG_LEFT_Y));
  leftFront.move(master.get_analog(ANALOG_LEFT_Y));
  rightBack.move(-master.get_analog(ANALOG_RIGHT_Y));
  rightFront.move(-master.get_analog(ANALOG_RIGHT_Y));
}

/*
void left(int speed); = left motors
void right(int speed); = right motors
void brake(); = constant brake mode
boid coast(); = constant brake mode
void timedDrive(int time, int speed); = moves for speed at time
*/
