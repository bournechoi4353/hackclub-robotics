#include "main.h"

// ============================================================
//  ALL driver-control button bindings live here. change a button? change it
//  once, right here, and it's the only place you need to look.
//
//    Lift:  R2 up / L2 down
//    Roller: DOWN in  (hold, no toggle -- no separate out button)
//    Claw:  R1 opens clawPiston / L1 closes it (press, not hold)
// ============================================================
void controls() {
  // ---- lift ----
  if (master.get_digital(DIGITAL_R2)) {
    set_arm(127);   // full up
  } else if (master.get_digital(DIGITAL_L2)) {
    set_arm(-127);  // full down
  } else {
    set_arm(0);     // stop (brake HOLD holds it in place)
  }

  // ---- roller (hold, in only) ----
  if (master.get_digital(DIGITAL_DOWN)) {
    set_roller(127);   // in
  } else {
    set_roller(0);
  }

  // ---- claw clamp piston: R1 opens, L1 closes (press, holds last state) ----
  if (master.get_digital_new_press(DIGITAL_R1)) {
    clawPiston.extend();   // open
  } else if (master.get_digital_new_press(DIGITAL_L1)) {
    clawPiston.retract();  // close
  }
}
