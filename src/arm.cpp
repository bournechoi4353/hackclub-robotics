#include "main.h"

// single motor. green cartridge = 200rpm (change if geared differently)
pros::Motor arm(LIFT_PORT, pros::MotorGears::green);

// positive = up
void set_arm(int speed) {
  arm.move(speed);
}

// lift: hold R1 = full up, hold R2 = full down, release = stop (brake HOLD holds it in place)
void arm_control() {
  if (master.get_digital(DIGITAL_R1)) {
    set_arm(127);   // full up
  } else if (master.get_digital(DIGITAL_R2)) {
    set_arm(-127);  // full down
  } else {
    set_arm(0);     // stop
  }
}
