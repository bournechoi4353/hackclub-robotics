#include "main.h"

// two 5.5W motors, spins in and out. green gearset (5.5W motors report as green);
// change the gearset or the CLAW_PORTS list in ports.hpp to match your bot.
pros::MotorGroup claw(CLAW_PORTS, pros::MotorGears::green);

// the robot's only pneumatic, the claw clamp. starts retracted (open).
pros::adi::Pneumatics clawPiston(CLAW_PISTON_PORT, false);

// positive = in
void set_claw(int speed) {
  claw.move(speed);
}

// X toggles the claw rollers in, B toggles them out (not holds). Pressing one
// while the other is running switches straight to the new direction. LEFT
// closes the clamp, RIGHT opens it.
int claw_motor_dir = 0;  // 0 = off, 1 = in, -1 = out

void claw_control() {
  if (master.get_digital_new_press(DIGITAL_X)) {
    claw_motor_dir = (claw_motor_dir == 1) ? 0 : 1;
  } else if (master.get_digital_new_press(DIGITAL_B)) {
    claw_motor_dir = (claw_motor_dir == -1) ? 0 : -1;
  }
  claw.move(claw_motor_dir * 127);

  if (master.get_digital_new_press(DIGITAL_LEFT)) {
    clawPiston.extend();   // close
  } else if (master.get_digital_new_press(DIGITAL_RIGHT)) {
    clawPiston.retract();  // open
  }
}
