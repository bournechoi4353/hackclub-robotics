#pragma once

#include "api.h"

// intake motor group (2x 5.5W) -- separate mechanism from the claw roller
extern pros::MotorGroup intake;

// intake speed for autons, -127..127 (positive = in)
void set_intake(int speed);
