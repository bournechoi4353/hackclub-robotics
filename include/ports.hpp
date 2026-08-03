#pragma once

//  drivetrain: 2 full (11W) + 1 half (5.5W) per side (negative port = reversed)
//  each side is {full, full, half}. placeholders, set your real ports.


#define LEFT_DRIVE_PORTS  {7, -15, -3}
#define RIGHT_DRIVE_PORTS {-10, 1, 4}
constexpr int    IMU_PORT       = 20;   // V5 inertial sensor
constexpr double WHEEL_DIAMETER = 2.75;
constexpr double DRIVE_RPM      = 450;

//  tracking wheel -- horizontal only, no vertical tracker on this bot.
//  offset comes from the Measure Offsets auton; the sign matters (+7.61 ran x/y
//  away on a spin last time).
constexpr int    HORIZ_TRACKER_PORT     = 6;
constexpr double HORIZ_TRACKER_DIAMETER = 3.25;
constexpr double HORIZ_TRACKER_OFFSET   = -7.61;

//  arm: 2 motors (negative = reversed)
constexpr int ARM_LEFT_PORT  = 12;
constexpr int ARM_RIGHT_PORT = 11;

//  arm height presets (motor-encoder degrees). placeholders, capture the real
//  numbers with the "Arm Height Test" auton.
constexpr double ARM_REST_POS = 0;
constexpr double ARM_LOW_POS  = 900;
constexpr double ARM_MID_POS  = 100;
constexpr double ARM_HIGH_POS = 2300;

//  intake: motor group, spins in/out. add or remove ports to match how many
//  intake motors you actually have.
#define INTAKE_PORTS {19, -20}

//  claw: 2 half motors (5.5W) in a group, spins in/out
#define CLAW_PORTS {14, -13}
//  claw clamp, the robot's only pneumatic (ADI port 'A'-'H')
constexpr char CLAW_PISTON_PORT = 'H';

//  distance sensors (MCL reads these)
constexpr int DISTANCE_FRONT_PORT = 17;
constexpr int DISTANCE_LEFT_PORT  = 18;
constexpr int DISTANCE_RIGHT_PORT = 2;
