#pragma once

#include "api.h"

// two independent 5.5W roller motors, plus the robot's one pneumatic (the clamp)
extern pros::Motor rollerRight;
extern pros::Motor rollerLeft;
extern pros::adi::Pneumatics clawPiston;

// roller speeds for autons, -127..127 each (positive = in)
void set_claw(int right_speed, int left_speed);

// driver control: UP toggles the right roller, DOWN toggles the left roller
// (independently -- either, both, or neither can be spinning). LEFT closes
// the clamp, RIGHT opens it.
void claw_control();
