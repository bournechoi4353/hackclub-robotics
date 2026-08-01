#pragma once

#include "api.h"

extern pros::MotorGroup arm;

// arm speed for autons, -127..127 (positive = up)
void set_arm(int speed);

// driver control, hold R1 to raise, R2 to lower, let go and it holds
void arm_control();
