#include "main.h"

pros::Motor tilterMotor(6, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_DEGREES);

pros::ADIPotentiometer tilterPot('A');

void tilter(int speed){
  tilterMotor.move(speed);
}

void tilterBrake(){
  tilterMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

}

void tilterCoast(){
  tilterMotor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}

void moveTilter(int time, int speed){
  tilterMotor.move(speed);
  wait(time);
  tilterMotor.move(0);
}
