#include "main.h"

// intake: 2x 5.5W motors as ONE group. green gearset (5.5W motors report as
// green). sign is a default, flip the ports in ports.hpp if it spins wrong.
pros::MotorGroup intake({INTAKE_RIGHT_PORT, INTAKE_LEFT_PORT}, pros::MotorGears::green);

// positive = in
void set_intake(int speed) {
  intake.move(speed);
}
