#pragma once

//  drivetrain: 2 full (11W) + 1 half (5.5W) per side, {front, middle, back}.
//  sign is a DEFAULT, not measured -- run Odom Spin / just watch a joystick
//  test and flip a side's signs if it drives backward.
#define LEFT_DRIVE_PORTS  {-12, -11, -5}
#define RIGHT_DRIVE_PORTS {18, 19, 20}
constexpr int    IMU_PORT       = 13;   // gyro
constexpr double WHEEL_DIAMETER = 2.75;
constexpr double DRIVE_RPM      = 450;

//  tracking wheel -- horizontal only, no vertical tracker on this bot. same
//  physical wheel as before, just replugged to port 17 (odom rotation sens).
//  diameter/offset are the wheel's own geometry, unrelated to the port.
constexpr int    HORIZ_TRACKER_PORT     = 17;
constexpr double HORIZ_TRACKER_DIAMETER = 3.25;
constexpr double HORIZ_TRACKER_OFFSET   = -7.61;

//  lift: single motor (was 2 -- only one lift port on the new sheet)
constexpr int LIFT_PORT = 7;

//  arm/lift height presets (motor-encoder degrees). placeholders, capture the
//  real numbers with the "Arm Height Test" auton.
constexpr double ARM_REST_POS = 0;
constexpr double ARM_LOW_POS  = 900;
constexpr double ARM_MID_POS  = 100;
constexpr double ARM_HIGH_POS = 2300;

//  claw rollers: 2 independent 5.5W motors (not grouped -- each side gets
//  its own driver control button). sign is a default, flip if a roller
//  spins the wrong way.
constexpr int ROLLER_RIGHT_PORT = 8;
constexpr int ROLLER_LEFT_PORT  = 3;
//  claw clamp, the robot's only pneumatic (ADI port 'A'-'H') -- unchanged,
//  this sheet only covers smart ports
constexpr char CLAW_PISTON_PORT = 'H';

//  distance sensors -- STALE. the new sheet lists 2 ("Distance Sens" on
//  ports 15 and 16) with no front/right/left labels, and this project needs
//  named roles (mcl.cpp + wall_reset.cpp both key off front/right/left).
//  left at their OLD port numbers for now, which is also wrong (17 now
//  belongs to the tracker, 18 to the front-right drive motor) -- these two
//  sensors are effectively disabled until the real ports+roles are known.
//  see chat for what's needed.
constexpr int DISTANCE_FRONT_PORT = 17;
constexpr int DISTANCE_LEFT_PORT  = 18;
constexpr int DISTANCE_RIGHT_PORT = 2;

//  distance sensor mount geometry (STALE for the same reason -- these
//  describe the OLD sensors/positions, not verified against the new ones).
//  body frame: off_x = right(+)/left(-) of center, off_y = forward(+)/
//  behind(-) of center, inches. facing_deg CW from the robot's front.
constexpr double DIST_FRONT_OFF_X = -5.0, DIST_FRONT_OFF_Y = 7.0, DIST_FRONT_FACING = 0.0;
constexpr double DIST_RIGHT_OFF_X = 4.5,  DIST_RIGHT_OFF_Y = 1.5, DIST_RIGHT_FACING = 90.0;
constexpr double DIST_LEFT_OFF_X  = -5.0, DIST_LEFT_OFF_Y  = 6.5, DIST_LEFT_FACING  = 270.0;
