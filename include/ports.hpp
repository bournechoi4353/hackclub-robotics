#pragma once

//  drivetrain: 2 full (11W) + 1 half (5.5W) per side, {front, middle, back}.
//  LEFT joystick drives the physically-RIGHT motors and vice versa (flipped
//  on purpose). sign is a DEFAULT, not measured -- flip a side if it drives
//  backward.
#define LEFT_DRIVE_PORTS  {-18, 19, -20}    // physically front-right/mid-right/back-right
#define RIGHT_DRIVE_PORTS {12, -11, 5}  // physically front-left/mid-left/back-left
constexpr int    IMU_PORT       = 13;   // gyro
constexpr double WHEEL_DIAMETER = 2.75;
constexpr double DRIVE_RPM      = 450;

//  tracking wheel -- horizontal only, no vertical tracker on this bot.
//  diameter/offset are the wheel's own geometry, unrelated to the port.
constexpr int    HORIZ_TRACKER_PORT     = 21;   // odom rotation sens
constexpr double HORIZ_TRACKER_DIAMETER = 3.25;
constexpr double HORIZ_TRACKER_OFFSET   = -7.61;

//  lift: single motor
constexpr int LIFT_PORT = 7;

//  arm/lift height presets (motor-encoder degrees), captured via "Arm Height
//  Capture". PLACE = height to actually set the pin down, HOVER = a bit
//  higher, for approaching/clearing before placing.
constexpr double ARM_REST_POS = 0;

constexpr double ARM_PIN1_PLACE_POS = 333;
constexpr double ARM_PIN1_HOVER_POS = 500;

constexpr double ARM_PIN2_PLACE_POS = 800;
constexpr double ARM_PIN2_HOVER_POS = 950;

constexpr double ARM_PIN3_PLACE_POS = 1220;
constexpr double ARM_PIN3_HOVER_POS = 1400;

constexpr double ARM_PIN4_PLACE_POS = 1500;
constexpr double ARM_PIN4_HOVER_POS = 1900;

//  claw roller: 2x 5.5W motors as one group (negative port = reversed).
//  PLACEHOLDERS -- swap these for the real ports once it's wired.
constexpr int ROLLER_RIGHT_PORT = 3;
constexpr int ROLLER_LEFT_PORT  = -8;

//  intake: 2x 5.5W motors as one group (negative port = reversed), separate
//  mechanism from the roller above. PLACEHOLDERS -- swap for the real ports.
constexpr int INTAKE_RIGHT_PORT = 4;
constexpr int INTAKE_LEFT_PORT  = 6;
//  claw clamp, the robot's only pneumatic (ADI port 'A'-'H') -- NOT WIRED,
//  kept here in case it gets added later
constexpr char CLAW_PISTON_PORT = 'H';

//  distance sensors -- STALE. only 2 physical sensors exist ("Distance Sens"
//  on ports 15 and 16, unlabeled), but the project wants 3 named roles
//  (front/left/right) for mcl.cpp + wall_align.cpp/wall_reset.cpp. front/left
//  below are the 2 real sensors with GUESSED roles -- confirm which is which.
//  right has no real sensor yet (port 2 is just unused/free).
constexpr int DISTANCE_FRONT_PORT = 15;
constexpr int DISTANCE_LEFT_PORT  = 16;
constexpr int DISTANCE_RIGHT_PORT = 2;

//  distance sensor mount geometry (STALE for the same reason -- these
//  describe guessed positions, not measured against the real sensors above).
//  body frame: off_x = right(+)/left(-) of center, off_y = forward(+)/
//  behind(-) of center, inches. facing_deg CW from the robot's front.
constexpr double DIST_FRONT_OFF_X = -5.0, DIST_FRONT_OFF_Y = 7.0, DIST_FRONT_FACING = 0.0;
constexpr double DIST_RIGHT_OFF_X = 4.5,  DIST_RIGHT_OFF_Y = 1.5, DIST_RIGHT_FACING = 90.0;
constexpr double DIST_LEFT_OFF_X  = -5.0, DIST_LEFT_OFF_Y  = 6.5, DIST_LEFT_FACING  = 270.0;
