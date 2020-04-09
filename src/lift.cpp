#include "main.h"

pros::Motor liftMotor(1, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_DEGREES);

pros::ADIPotentiometer pot('B');

pros::ADILineSensor line('G');

PIDController liftPID(2,2);

void test() {
  if(line.get_value() < 200 && line.get_value() > 100){

  }
  else {

  }
}

void lift(int speed) {
  liftMotor.move(speed);
}

void liftBrake(){
  liftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void liftCoast(){
  liftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}

//Auton

void moveLift(int target) {
  int time = 0;

  while(time < 50){
    int PIDSpeed = -liftPID.getSpeedToMotor(target, pot.get_value());

    if(fabs(liftPID.getError()) < 10) {
      time++;
      wait(2);
    }
    lift(PIDSpeed);
  }
  lift(0);
  liftBrake();
}


//Op control
void liftOP(){

liftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
liftMotor.move_velocity(100);
}

else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
liftMotor.move_velocity(100);
}
else {
liftMotor.move_velocity(0);
  }
}
