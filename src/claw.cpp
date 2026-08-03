#include "main.h"

// two 5.5W motors, independent (not a group) so each side can be toggled on
// its own. green gearset (5.5W motors report as green).
pros::Motor rollerRight(ROLLER_RIGHT_PORT, pros::MotorGears::green);
pros::Motor rollerLeft(ROLLER_LEFT_PORT, pros::MotorGears::green);

// the robot's only pneumatic, the claw clamp. starts retracted (open).
pros::adi::Pneumatics clawPiston(CLAW_PISTON_PORT, false);

// positive = in
void set_claw(int right_speed, int left_speed) {
  rollerRight.move(right_speed);
  rollerLeft.move(left_speed);
}

// UP toggles the right roller in/off, DOWN toggles the left roller in/off,
// independently of each other. LEFT closes the clamp, RIGHT opens it.
bool roller_right_on = false;
bool roller_left_on = false;

void claw_control() {
  if (master.get_digital_new_press(DIGITAL_UP)) roller_right_on = !roller_right_on;
  if (master.get_digital_new_press(DIGITAL_DOWN)) roller_left_on = !roller_left_on;

  rollerRight.move(roller_right_on ? 127 : 0);
  rollerLeft.move(roller_left_on ? 127 : 0);

  if (master.get_digital_new_press(DIGITAL_LEFT)) {
    clawPiston.extend();   // close
  } else if (master.get_digital_new_press(DIGITAL_RIGHT)) {
    clawPiston.retract();  // open
  }
}
