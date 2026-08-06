#pragma once

// all the PID/odom tuning, gets called in initialize()
void default_constants();

// open-loop push into a wall to let the wall square the robot up -- no PID
// target angle on purpose (the wall decides the final heading, not us).
void swing_into_wall(int left_power, int right_power, int duration_ms);

// cycles the arm through the preset heights so you can check/capture them
void arm_height_test();

// live capture tool: jog the arm by hand, screen shows the current encoder
// position so you can write down the number at each pin height (0 = rest)
void arm_height_capture();

// ---- match autons: red ----
void redRightQuals();
void redLeftQuals();
void redRightElim();
void redLeftElim();
void redRightYellows();
void redLeftYellows();

// ---- match autons: blue (same routines, mirrored/recolored) ----
void blueRightQuals();
void blueLeftQuals();
void blueRightElim();
void blueLeftElim();
void blueRightYellows();
void blueLeftYellows();

// programming skills run (60s solo)
void skills();

// motor pivot in place, x/y drift should stay ~0
void odom_spin_test();

// 48in square (straights + IMU turns), tune drive/turn PID by how well it closes
void pid_square();

// straight 48" via the trapezoid motion profile, prints distance traveled
void motion_profile_test();

// MCL test: catches a 4" odom error we plant on purpose
void mcl_test();

// wall reset test: plants a deliberately wrong pose, then corrects it off
// whichever of front/right/left is square to a wall
void wall_reset_test();
