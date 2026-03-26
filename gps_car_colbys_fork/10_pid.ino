// ************************   PID FUNCTIONS   ************************//

// perhaps rename variables so they are all the same or rename them
// to specify which PID they are a part off



// ************************   ESC_PID   ************************//

int esc_pid(int speed) {

  long Err, D;
  static long I, prev_Err;
  unsigned long esc_Time;
  float deltaT, mag_rpm, set_rpm;
  int throttle_command, pid_throttle;  // make variables "static" if you uncomment Integral Check

  

  const float mph_to_rpm = 175.36766;  // 5280 ft\mile * 12 in\ft * 2.6 rev_enc\rev_wheel / 15.65625 in\rev_wheel / 60 minutes\hr

  const long max_I = (esc_full_forward - esc_default) / Ki;  // Determine the max I value for desired max influence

  esc_Time = micros();
  mag_rpm = calc_mag_rpm();
  set_rpm = speed * mph_to_rpm;
  Err = set_rpm - mag_rpm;  // current error of mag_rpm

  D = (Err - prev_Err);  // difference between current and previous error scaled by deltaT

  //-----------------------------------------------------------------------------------------------
  // D == rpm/s so r/ms maybe make  deltaT/6E7
  // I == rpm*s so rs/m or make rpm to rps
  //-----------------------------------------------------------------------------------------------

  //-----------------------------------------------------------------------------------------------
  // // Leave commented
  // // Integral Check
  // if ((pid_throttle != (throttle_command - esc_default)) && (sign(pid_throttle) == sign(Err))) {
  //   sec_I = sec_I;
  // } else {
  //   sec_I = constrain(sec_I + (Err * deltaT), -max_I, max_I);  // summation of the error of mag_rpm
  // }
  //-----------------------------------------------------------------------------------------------

  I = constrain(I + Err, -max_I, max_I);  // summation of the error of mag_rpm
  pid_throttle = Err * Kp + I * Ki + D * Kd;
  throttle_command = constrain(esc_default + pid_throttle, esc_full_reverse, esc_full_forward);  // Keep it in range of the ESC

  prev_Err = Err;  // grab error for next time through
  prev_esc_Time = esc_Time;


  return throttle_command;
}
