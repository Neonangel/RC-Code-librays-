// ************************   SENSOR FUNCTIONS   ************************//

// This file contains the various functions that the arduino uses to
// monitor the state of the car and its surroundings using the various
// sensors on the car, not including the gps and compass



// ************************   CALC_BATT_VOLTAGE   ************************//

// This function should calculate the total battery voltage using a voltage divider on pin A1,
// and cell 1 voltage using a voltage divider on pin A0.
// It assume the voltage dividers has values of R1, R2, R3, and R4
void calc_batt_voltage() {
  const byte R1 = 100;
  const byte R2 = 39;
  const byte R3 = 100;
  const byte R4 = 100;
  float tot_batt_scale = 1.0401;   // Emperically measured value
  float cell_batt_scale = 1.0358;  // Emperically measured value
  float tmp1 = analogRead(batt_volt_pin) * 3.3 / 1024.0;
  volts_total = tmp1 * (R1 + R2) / R2 * tot_batt_scale;
  float tmp2 = analogRead(batt_cell_1_pin) * 3.3 / 1024.0;
  volts_cell_1 = tmp2 * (R3 + R4) / R4 * cell_batt_scale;
  volts_cell_2 = volts_total - volts_cell_1;

}  //End of calc_batt_voltage



// ************************   CALC_MAG_RPM   ************************//

// Calculates rpm of magnet wheel
float calc_mag_rpm() {
  static unsigned long last_micros_rpm = 0;
  unsigned long micros_now = micros();
  rpm = 6.0E7 * hall_count / (micros_now - last_micros_rpm) / 6;
  // 6 reads\revolution, measured in micro-seconds...
  hall_count = 0;
  last_micros_rpm = micros_now;
  return rpm;
}  //End of calc_mag_rpm



// ************************   GET_LIDAR_DATA   ************************//

// Using front Lidar sensor, guestimate the distance to any object in front
void get_lidar_data() {
  int16_t dist_cm;                     // Leave as int16_t
  luna.getData(dist_cm, lidar_adr);    // Gets distance data from lidar sensor in cm
  dist_lidar = float(dist_cm) / 2.54;  // Returns the distance in inches
}  //End of get_lidar_data



// ************************   SET_STEERING   ************************//

// Sets the steering trim of the cars
void set_steering(int range) {
  while (1) {
    lcd.clear();
    lcd.setCursor(2, 1);
    lcd.print(F("Set Steering Pot"));
    Serial.println(F("Set Steering Pot"));
    while (1) {
      steering_trim = map(analogRead(steering_trim_pin), 0, 1023, -range, range);  // potentially change to pwm values 1000 - 2000
      servo_straight = 90 + steering_trim;
      servo_left = 55 + steering_trim;
      servo_right = 125 + steering_trim;
      steering_servo.write(servo_straight);
      delay(100);
    }
  }
}  //End of set_steering