#include "main.h"

// single motor. green cartridge = 200rpm (change if geared differently)
pros::MotorGroup arm({LIFT_PORT, LIFT2_PORT}, pros::MotorGear::green);

// positive = up
void set_arm(int speed) {
  arm.move(speed);
}
//add second motor for lift, r1/r2 flip