#include "main.h"

// ============================================================
//  ALL driver-control button bindings live here. change a button? change it
//  once, right here, and it's the only place you need to look.
//
//    Lift:   R2 up / L2 down
//    Intake: R1 in / B out  (hold, no toggle)
//    Roller: L1 in  (hold, no toggle -- no separate out button)
//    (claw clamp is commented out below -- not wired)
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

  // ---- intake (hold) ----
  if (master.get_digital(DIGITAL_R1)) {
    set_intake(127);   // in
  } else if (master.get_digital(DIGITAL_B)) {
    set_intake(-127);  // out
  } else {
    set_intake(0);
  }

  // ---- roller (hold, in only) ----
  if (master.get_digital(DIGITAL_L1)) {
    set_roller(127);   // in
  } else {
    set_roller(0);
  }

  // ---- claw clamp piston -- NOT WIRED ----
  // if (master.get_digital_new_press(DIGITAL_DOWN)) {
  //   clawPiston.toggle();  // "claw straight"
  // }
}
