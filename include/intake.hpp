#pragma once

#include "api.h"

// intake motor group (spins in/out)
extern pros::MotorGroup intake;

// intake speed for autons, -127..127 (positive = in)
void set_intake(int speed);

// driver control: hold L1 to intake, L2 to spit out, let go to stop
void intake_control();
