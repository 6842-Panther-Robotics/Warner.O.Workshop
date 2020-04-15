#include "main.h"

pros::Motor rightRoller (7, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor leftRoller (8, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);

void rollers(int speed){
  rightRoller.move(speed);
  leftRoller.move(speed);
}

void rollerBrake(){
  rightRoller.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  leftRoller.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

}

void rollerCoast(){
  rightRoller.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  leftRoller.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}

void rollerOP(){

rightRoller.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
leftRoller.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
rightRoller.move_velocity(100);
leftRoller.move_velocity(100);
}

else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
rightRoller.move_velocity(-100);
leftRoller.move_velocity(100);
}
else {
rightRoller.move_velocity(0);
leftRoller.move_velocity(0);
  }
}
