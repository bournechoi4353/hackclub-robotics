#include "main.h"

// single motor. green cartridge = 200rpm (change if geared differently)
pros::Motor arm(LIFT_PORT, pros::MotorGears::green);

// positive = up
void set_arm(int speed) {
  arm.move(speed);
}
