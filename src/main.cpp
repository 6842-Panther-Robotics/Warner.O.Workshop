#include "main.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

pros::ADIDigitalIn selector ('A');
int autonIndex = 0;

void autonSelector(void* paramater){
	const int autoCount = 2;

	const char *autoNames[autoCount] = {
		"Red Front Auton", "Blue Front Auton"
	};

	while(true) {
		if(selector.get_value() == 1)
		autonIndex++;
		if(autonIndex == autoCount){
			autonIndex = 0;
		}
		//%s = print string
		//%d = pring integer
		//%f = print double or float
		pros::lcd::print(4, "%s", autoNames[autonIndex]);
		wait(300);
	}
}

void initialize() {
	pros::lcd::initialize();

	pros::lcd::set_text(1, "Hello PROS User!");

	pros::Task auton_selector(autonSelector);

	pros::lcd::register_btn1_cb(on_center_button);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */


 	pros::Controller master(pros::E_CONTROLLER_MASTER);

void opcontrol() {

moveForward(48);
	while (true) {
		driveOP();
		wait(10);
	}
}
