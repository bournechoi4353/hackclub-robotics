#pragma once

#include "api.h"

// roller motor group (2x 5.5W)
extern pros::MotorGroup roller;

// claw clamp -- NOT WIRED. only the standard rollers exist right now.
// extern pros::adi::Pneumatics clawPiston;

// roller speed for autons, -127..127 (positive = in)
void set_claw(int speed);
