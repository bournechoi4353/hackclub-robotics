#include "main.h"

// built on EZ-Template, docs at https://ez-robotics.github.io/EZ-Template/

// all out of 127
const int DRIVE_SPEED = 127;
const int TURN_SPEED = 110;
const int SWING_SPEED = 127;

// milliseconds to wait between auton movements. change this one number; 0 = none
const int PAUSE = 0;

// drive / turn / odom PID tuning, everything EZ needs, set once at startup
void default_constants() {
  // kP, kI, kD (turn also takes a start-I)
  chassis.pid_drive_constants_set(12.0, 0.0, 80.0);          // fwd/rev, lower kP eases into the target instead of braking hard
  chassis.pid_heading_constants_set(11.0, 0.0, 20.0);        // keeps us driving straight without odom
  chassis.pid_turn_constants_set(3.0, 0.05, 20.0, 15.0);     // turning in place
  chassis.pid_swing_constants_set(6.0, 0.0, 65.0);           // swings, one side pivots
  chassis.pid_odom_angular_constants_set(4.0, 0.0, 52.5);    // heading for odom moves, lowered kP to kill the side-to-side sway
  chassis.pid_odom_boomerang_constants_set(5.8, 0.0, 32.5);  // heading for boomerang moves

  // when a move counts as "done"
  chassis.pid_turn_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_swing_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_drive_exit_condition_set(90_ms, 1_in, 250_ms, 3_in, 500_ms, 500_ms);
  chassis.pid_odom_turn_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 750_ms);
  chassis.pid_odom_drive_exit_condition_set(90_ms, 1_in, 250_ms, 3_in, 500_ms, 750_ms);
  chassis.pid_turn_chain_constant_set(3_deg);
  chassis.pid_swing_chain_constant_set(5_deg);
  chassis.pid_drive_chain_constant_set(3_in);

  // slew, ramp up so we don't jerk off the line
  chassis.slew_turn_constants_set(3_deg, 70);
  chassis.slew_drive_constants_set(3_in, 70);
  chassis.slew_swing_constants_set(3_in, 80);

  // how much turning wins over driving in odom moves (1.0 = max).
  // bump it up if you add tracking wheels
  chassis.odom_turn_bias_set(0.9);

  chassis.odom_look_ahead_set(8_in);           // how far ahead it looks, smaller = less overshoot at the end, bigger = smoother
  chassis.odom_boomerang_distance_set(16_in);  // furthest the carrot point can sit from the target
  chassis.odom_boomerang_dlead_set(0.625);     // how aggressive the tail of a boomerang move is

  chassis.pid_angle_behavior_set(ez::shortest);  // default turns take the shortest way around
}

// open-loop push into a wall so the wall (not a PID target) squares the robot
// up. a closed-loop swing fights to reach a commanded angle even after it's
// pinned against the wall -- this just pushes for a fixed time and stops, no
// target to fight over. direction is a guess (matching the RIGHT_SWING this
// replaces) -- flip which side gets power if it swings the wrong way.
void swing_into_wall(int left_power, int right_power, int duration_ms) {
  uint32_t start = pros::millis();
  while (pros::millis() - start < (uint32_t)duration_ms) {
    chassis.drive_set(left_power, right_power);
    pros::delay(ez::util::DELAY_TIME);
  }
  chassis.drive_set(0, 0);
}

// 2red1black match auton -- EZ's IMU-based PID drive + turns (IMU on port 9).
void redRightQuals() {


  chassis.pid_drive_set(-17_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_relative_set(-90_deg, TURN_SPEED);
  chassis.pid_wait();


  chassis.pid_drive_set(-19_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_drive_set(19_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_turn_relative_set(45_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-38_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_relative_set(-135_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-19_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_drive_set(19_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_relative_set(-90_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-26_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_turn_relative_set(45_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-35_in, DRIVE_SPEED, true);
  chassis.pid_wait();  // full settle -- last move, nothing left to chain into
}

void redLeftQuals() {


  chassis.pid_drive_set(-17_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_relative_set(90_deg, TURN_SPEED);
  chassis.pid_wait();


  chassis.pid_drive_set(-19_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_drive_set(19_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_turn_relative_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-38_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_relative_set(135_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-19_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_drive_set(19_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_relative_set(90_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-26_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_turn_relative_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-35_in, DRIVE_SPEED, true);
  chassis.pid_wait();  // full settle -- last move, nothing left to chain into
}

void redRightElim() {
  chassis.pid_drive_set(-19_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_relative_set(-90_deg, TURN_SPEED);
  chassis.pid_wait();


  chassis.pid_drive_set(-19_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_drive_set(19_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_drive_set(-45_in, 80, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-27_in,90, true);
  chassis.pid_wait();
  chassis.pid_drive_set(27_in, 100, true);
  chassis.pid_wait();
  chassis.pid_drive_set(45_in, 80, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-19_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_drive_set(19_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_turn_relative_set(-135_deg, 90);
  chassis.pid_wait();
  chassis.pid_drive_set(-27_in, 80, true);
  chassis.pid_wait();
  chassis.pid_drive_set(27_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-45_in, 80, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-19_in, DRIVE_SPEED, true);
  chassis.pid_wait();


}

void redLeftElim() {
  chassis.pid_drive_set(-19_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_relative_set(90_deg, TURN_SPEED);
  chassis.pid_wait();


  chassis.pid_drive_set(-19_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_drive_set(19_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_drive_set(45_in, 80, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-27_in,90, true);
  chassis.pid_wait();
  chassis.pid_drive_set(27_in, 100, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-45_in, 80, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-19_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_drive_set(19_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_turn_relative_set(135_deg, 90);
  chassis.pid_wait();
  chassis.pid_drive_set(-27_in, 80, true);
  chassis.pid_wait();
  chassis.pid_drive_set(27_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_drive_set(45_in, 80, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-19_in, DRIVE_SPEED, true);
  chassis.pid_wait();


}

void redRightYellows(){
  chassis.pid_drive_set(-18_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_relative_set(-90_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-19_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_drive_set(19_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_turn_relative_set(45_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-34_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_turn_relative_set(-135_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-19_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_drive_set(19_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_turn_relative_set(45_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-34_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_turn_relative_set(-135_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-19_in, DRIVE_SPEED, true);
  chassis.pid_wait();

}

void redLeftYellows(){
  chassis.pid_drive_set(-18_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_relative_set(90_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-19_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_drive_set(19_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_turn_relative_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-34_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_turn_relative_set(135_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-19_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_drive_set(19_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_turn_relative_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-34_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_turn_relative_set(135_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-19_in, DRIVE_SPEED, true);
  chassis.pid_wait();

}
//--------------------------------------------------------------------------------------
void blueRightQuals() {


  chassis.pid_drive_set(-17_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_relative_set(-90_deg, TURN_SPEED);
  chassis.pid_wait();


  chassis.pid_drive_set(-19_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_drive_set(19_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_turn_relative_set(45_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-38_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_relative_set(-135_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-19_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_drive_set(19_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_relative_set(-90_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-26_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_turn_relative_set(45_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-35_in, DRIVE_SPEED, true);
  chassis.pid_wait();  // full settle -- last move, nothing left to chain into
}

void blueLeftQuals() {


  chassis.pid_drive_set(-17_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_relative_set(90_deg, TURN_SPEED);
  chassis.pid_wait();


  chassis.pid_drive_set(-19_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_drive_set(19_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_turn_relative_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-38_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_relative_set(135_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-19_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_drive_set(19_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_relative_set(90_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-26_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_turn_relative_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-35_in, DRIVE_SPEED, true);
  chassis.pid_wait();  // full settle -- last move, nothing left to chain into
}

void blueRightElim() {
  chassis.pid_drive_set(-19_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_relative_set(-90_deg, TURN_SPEED);
  chassis.pid_wait();


  chassis.pid_drive_set(-19_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_drive_set(19_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_drive_set(-45_in, 80, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-27_in,90, true);
  chassis.pid_wait();
  chassis.pid_drive_set(27_in, 100, true);
  chassis.pid_wait();
  chassis.pid_drive_set(45_in, 80, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-19_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_drive_set(19_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_turn_relative_set(-135_deg, 90);
  chassis.pid_wait();
  chassis.pid_drive_set(-27_in, 80, true);
  chassis.pid_wait();
  chassis.pid_drive_set(27_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-45_in, 80, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-19_in, DRIVE_SPEED, true);
  chassis.pid_wait();


}

void blueLeftElim() {
  chassis.pid_drive_set(-19_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_relative_set(90_deg, TURN_SPEED);
  chassis.pid_wait();


  chassis.pid_drive_set(-19_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_drive_set(19_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_drive_set(45_in, 80, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-27_in,90, true);
  chassis.pid_wait();
  chassis.pid_drive_set(27_in, 100, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-45_in, 80, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-19_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_drive_set(19_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_turn_relative_set(135_deg, 90);
  chassis.pid_wait();
  chassis.pid_drive_set(-27_in, 80, true);
  chassis.pid_wait();
  chassis.pid_drive_set(27_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_drive_set(45_in, 80, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-19_in, DRIVE_SPEED, true);
  chassis.pid_wait();


}

void blueRightYellows(){
  chassis.pid_drive_set(-18_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_relative_set(-90_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-19_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_drive_set(19_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_turn_relative_set(45_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-34_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_turn_relative_set(-135_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-19_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_drive_set(19_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_turn_relative_set(45_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-34_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_turn_relative_set(-135_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-19_in, DRIVE_SPEED, true);
  chassis.pid_wait();

}

void blueLeftYellows(){
  chassis.pid_drive_set(-18_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_relative_set(90_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-19_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_drive_set(19_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_turn_relative_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-34_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_turn_relative_set(135_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-19_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_drive_set(19_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_turn_relative_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-34_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_turn_relative_set(135_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-19_in, DRIVE_SPEED, true);
  chassis.pid_wait();

}

void skills() {
  // real starting spot on the field: (0, -67), facing center (+Y) = 0 deg
  chassis.odom_xyt_set(0_in, -67_in, 0_deg);

  // --- shuttle-loop tuning (PLACEHOLDERS -- capture these on the field) ---
  // front-sensor distance (mm) at the end of each goal approach. drive the
  // segment once, read distanceFront.get() where it should stop, and drop the
  // real number in. the field-tested encoder distances these replace are noted
  // in comments on each drive_to_distance call below.
  const int GOAL1_MM   = 60;   // was pid_drive_set(18_in)
  const int GOAL2_MM   = 60;   // was pid_drive_set(13_in)
  const int SQUARE_TOL = 20;   // left/right match tolerance (mm) for square_to_walls

  chassis.pid_drive_set(-5_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_drive_set(8_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(60_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  for (int i = 0; i < 5; i++) {
    // re-square at the START of every rep so heading error can't compound
    // across reps. bounded + gated: self-aborts if the side sensors aren't on
    // walls, so it never fights the IMU mid-field.
    square_to_walls(SQUARE_TOL);

    chassis.pid_wait_until(3000);
    chassis.pid_drive_set(-13_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    chassis.pid_turn_set(-60_deg, TURN_SPEED);
    chassis.pid_wait();

    // distance sensor is DISABLED for now -- back to the fixed distance this
    // replaced. drive_to_distance(distanceFront, GOAL1_MM, DRIVE_SPEED);
    chassis.pid_drive_set(-18_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    chassis.pid_wait_until(3000);

    chassis.pid_drive_set(-18_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    chassis.pid_turn_set(90_deg, TURN_SPEED);
    chassis.pid_wait();

    // drive_to_distance(distanceFront, GOAL2_MM, DRIVE_SPEED);  // was 13"
    chassis.pid_drive_set(-13_in, DRIVE_SPEED, true);
    chassis.pid_wait();
  }
  chassis.pid_drive_set(-60_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_relative_set(180_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(60_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  for (int i = 0; i < 5; i++) {
    square_to_walls(SQUARE_TOL);

    chassis.pid_wait_until(3000);
    chassis.pid_drive_set(-13_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    chassis.pid_turn_set(60_deg, TURN_SPEED);   // 90 - 150
    chassis.pid_wait();

    // drive_to_distance(distanceFront, GOAL1_MM, DRIVE_SPEED);  // was 18"
    chassis.pid_drive_set(-18_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    chassis.pid_wait_until(3000);

    chassis.pid_drive_set(-18_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    chassis.pid_turn_set(-90_deg, TURN_SPEED);    // back to 90
    chassis.pid_wait();

    // drive_to_distance(distanceFront, GOAL2_MM, DRIVE_SPEED);  // was 13"
    chassis.pid_drive_set(-13_in, DRIVE_SPEED, true);
    chassis.pid_wait();
  }
}




// cycles the arm through each preset height, pausing at each so you can line it
// up against the tower and read the encoder. uses move_absolute, the motor's
// built-in smooth move, no PID tuning. edit the ARM_*_POS numbers in ports.hpp
// once you've captured your real heights.
void arm_height_test() {
  arm.tare_position();  // 0 = wherever the arm is resting right now

  const int ARM_VEL = 100;  // move speed in deg/sec (green cartridge tops out ~200)
  double heights[] = {ARM_PIN1_PLACE_POS, ARM_PIN1_HOVER_POS,
                       ARM_PIN2_PLACE_POS, ARM_PIN2_HOVER_POS,
                       ARM_PIN3_PLACE_POS, ARM_PIN3_HOVER_POS,
                       ARM_PIN4_PLACE_POS, ARM_PIN4_HOVER_POS,
                       ARM_REST_POS};

  for (double h : heights) {
    arm.move_absolute(h, ARM_VEL);
    pros::delay(1500);  // let it get there and settle before reading

    printf("Arm -> target %.0f   actual %.1f\n", h, arm.get_position());
    ez::screen_print("Arm height test"
                         "\ntarget: " + util::to_string_with_precision(h) +
                         "\nactual: " + util::to_string_with_precision(arm.get_position()),
                     1);
  }
}

// live capture tool for pin heights. tares at 0 (resting position), sets the
// arm to COAST so it moves freely by hand (it's HOLD brake normally, which
// would fight you), then shows the live encoder position on screen -- push it
// to each pin count's real height and write down the number. R2/L2 still work
// too if you'd rather jog it than push it. no auto-stepping, runs forever;
// pick a different auton (or restart) to exit.
void arm_height_capture() {
  arm.tare_position();  // 0 = resting position (0 pins)
  arm.set_brake_mode(pros::MotorBrake::coast);  // free to push by hand

  while (true) {
    if (master.get_digital(DIGITAL_R2)) {
      set_arm(127);   // full up
    } else if (master.get_digital(DIGITAL_L2)) {
      set_arm(-127);  // full down
    } else {
      set_arm(0);
    }

    printf("Arm height capture -> position: %.1f\n", arm.get_position());
    ez::screen_print("Arm height capture"
                         "\nposition: " + util::to_string_with_precision(arm.get_position()) +
                         "\n(push by hand, or R2 up / L2 down, 0 = rest)"
                         "\nmove to each pin height, write down the number",
                     1);

    pros::delay(ez::util::DELAY_TIME);
  }
}

// pivot in place under motor power and report how far x/y drifted (should
// be ~0). don't spin it by hand, your hands slide the robot and fake a
// drift. small drift = nudge the horiz offset, big runaway = wrong sign.
void odom_spin_test() {
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);
  chassis.drive_brake_set(MOTOR_BRAKE_COAST);

  chassis.drive_set(45, -45);   // left fwd, right rev = pivot
  pros::delay(4000);            // a few rotations
  chassis.drive_set(0, 0);
  pros::delay(400);

  double x = chassis.odom_x_get();
  double y = chassis.odom_y_get();
  double t = chassis.odom_theta_get();
  printf("Spin drift -> x: %.2f  y: %.2f  t: %.2f  (x/y should be ~0)\n", x, y, t);
  while (true) {
    ez::screen_print("After in-place pivot (x/y should be ~0):"
                         "\n x: " + util::to_string_with_precision(x) +
                         "\n y: " + util::to_string_with_precision(y) +
                         "\n t: " + util::to_string_with_precision(t),
                     1);
    pros::delay(ez::util::DELAY_TIME);
  }
}

// add your own autons below


// 48" square for tuning drive + turn PID, four straights with 90 turns, no
// tracking wheels needed (IMU + encoders). watch how cleanly it closes back to
// the start: sides bowing = drive PID, corners off = turn PID.
void pid_square() {
  for (int i = 0; i < 4; i++) {
    chassis.pid_drive_set(48_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    chassis.pid_turn_relative_set(90_deg, TURN_SPEED);  // 90 right; 4 corners = full loop
    chassis.pid_wait();
  }
}

// straight 48" with the trapezoid profile instead of PID, then prints how
// far it actually went. tune kV/kA/kP in motion_profile.cpp
void motion_profile_test() {
  // profiled_drive(inches, max vel in/s, max accel in/s^2)
  profiled_drive(48, 30, 60);

  double traveled = (chassis.drive_sensor_left() + chassis.drive_sensor_right()) / 2.0;
  printf("Motion profile -> target: 48.0 in   traveled: %f in\n", traveled);
}

// square the robot up against a real wall before running this. seeds a
// deliberately wrong pose (so there's something to fix), then wall_reset()
// should snap it back -- prints before/after so you can see it move.
void wall_reset_test() {
  chassis.odom_xyt_set(0.0, 0.0, chassis.odom_theta_get());  // wrong x/y on purpose
  printf("Wall reset -- BEFORE: x:%.2f y:%.2f t:%.2f\n",
         chassis.odom_x_get(), chassis.odom_y_get(), chassis.odom_theta_get());

  bool applied = wall_reset();

  printf("Wall reset -- AFTER:  x:%.2f y:%.2f t:%.2f  (%s)\n",
         chassis.odom_x_get(), chassis.odom_y_get(), chassis.odom_theta_get(),
         applied ? "applied" : "no sensor was square to a wall in range");
}

// MCL end-to-end test. place the robot at field (-48, -48) facing forward,
// bottom-left corner: back wall ~22" behind center, left wall ~22" to the
// left, so both sensors are in range (back fixes Y, left fixes X, right
// sees nothing).
//
// we seed odom 4" off in X on purpose. watch the screen: pending X walks
// toward -4 as the cloud converges, then the flush snaps odom to the truth.
// after that it drives out and back, flushing only between motions.
void mcl_test() {
  constexpr double START_X = -48.0, START_Y = -48.0;  // true placement
  constexpr double ODOM_ERR_X = 4.0;                  // the planted error

  // lie to odom by 4". MCL gets seeded at the same wrong spot (that's all it
  // would know in a real match) and has to find the truth from the walls
  chassis.odom_xyt_set(START_X + ODOM_ERR_X, START_Y, 0.0);
  mcl::start(START_X + ODOM_ERR_X, START_Y, 3.0);
  mcl::auto_flush_set(false);  // manual flushes so each phase is visible

  // sit still, let the cloud converge
  pros::delay(4000);

  // flush, odom X should jump ~-4"
  bool applied = mcl::flush_if_safe();
  printf("[mcl_test] flush #1 %s | odom (%.1f, %.1f) vs true (%.1f, %.1f)\n",
         applied ? "APPLIED" : "skipped",
         chassis.odom_x_get(), chassis.odom_y_get(), START_X, START_Y);
  pros::delay(1000);

  // drive out and back, flushing only between motions
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  mcl::flush_if_safe();

  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  mcl::flush_if_safe();

  // park with live numbers, stop the program after reading
  while (true) {
    ez::screen_print("MCL  odom(" + util::to_string_with_precision(chassis.odom_x_get()) +
                         ", " + util::to_string_with_precision(chassis.odom_y_get()) + ")" +
                         "\nest (" + util::to_string_with_precision(mcl::x()) +
                         ", " + util::to_string_with_precision(mcl::y()) + ")" +
                         "\npend(" + util::to_string_with_precision(mcl::pending_x()) +
                         ", " + util::to_string_with_precision(mcl::pending_y()) + ")" +
                         "\nsprd(" + util::to_string_with_precision(mcl::spread_x()) +
                         ", " + util::to_string_with_precision(mcl::spread_y()) + ")" +
                         " conf " + (mcl::confident_x() ? "X" : "-") + (mcl::confident_y() ? "Y" : "-") +
                         "\nbeams ok " + std::to_string(mcl::sensors_accepted()) +
                         " gated " + std::to_string(mcl::sensors_gated()) +
                         " flushes " + std::to_string(mcl::flush_count()),
                     1);
    pros::delay(ez::util::DELAY_TIME);
  }
}

void toggle_test() {
  chassis.pid_drive_set(3_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}
