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

// D-pad up = spin in, D-pad down = spin out, A toggles the clamp
void claw_control() {
  if (master.get_digital(DIGITAL_UP)) {
    claw.move(127);   // in
  } else if (master.get_digital(DIGITAL_DOWN)) {
    claw.move(-127);  // out
  } else {
    claw.move(0);     // stop
  }

  if (master.get_digital_new_press(DIGITAL_A)) {
    clawPiston.toggle();  // clamp / release
  }
}
