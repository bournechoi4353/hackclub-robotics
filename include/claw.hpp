#pragma once

#include "api.h"

// 2x 5.5W motors as a group, plus the robot's one pneumatic (the clamp)
extern pros::MotorGroup claw;
extern pros::adi::Pneumatics clawPiston;

// spin the claw rollers for autons, -127..127 (positive = in)
void set_claw(int speed);

// driver control: D-pad up/down spins the rollers in/out, A toggles the clamp
void claw_control();
