#include "main.h"

// motor group, spins in and out. blue gearset (600rpm) is a common intake speed;
// change the gearset or the INTAKE_PORTS list in ports.hpp to match your bot.
pros::MotorGroup intake(INTAKE_PORTS, pros::MotorGears::blue);

// positive = in
void set_intake(int speed) {
  intake.move(speed);
}

// hold L1 = in, hold L2 = out, release = stop. call this every loop in opcontrol
void intake_control() {
  if (master.get_digital(DIGITAL_L1)) {
    intake.move(127);   // in
  } else if (master.get_digital(DIGITAL_L2)) {
    intake.move(-127);  // out
  } else {
    intake.move(0);     // stop
  }
}
