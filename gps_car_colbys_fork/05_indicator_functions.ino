// ************************   INDICATOR FUNCTIONS   ************************//

// This file contains the various functions that the arduino uses to
// communicate the state of the car to the user, using the various
// indicators, not including the LCD Screen and Neo-Pixel



// ************************   BEEP   ************************//

void beep() {
  beeped = 1;
  digitalWrite(buzzer_pin, 1);
  delay(1000);
  digitalWrite(buzzer_pin, 0);
  delay(250);
  for (int i = 1; i < 5; i++) {
    digitalWrite(buzzer_pin, 1);
    delay(250);
    digitalWrite(buzzer_pin, 0);
    delay(250);
  }
}  //End of beep



// ************************   FLASH   ************************//

// Flashes bult-in RGB LED on rp2040
// Leave as NinaPin
void flash(NinaPin pin, unsigned long on_time, unsigned long off_time, int high_level, int low_level, int LED) {
  static bool pin_state[] = { 0, 0, 0, 0 };

  if (pin_state[LED]) {
    if (millis() - timer[LED] > on_time) {
      analogWrite(pin, low_level);
      pin_state[LED] = 0;
      timer[LED] = millis();
    }
  } else {
    if (millis() - timer[LED] > off_time) {
      analogWrite(pin, high_level);
      timer[LED] = millis();
      pin_state[LED] = 1;
    }
  }
}  //End of flash



// ************************   WAG_SERVO   ************************//

// Wag the servo at a given speed
void wag_servo(int servo_delay) {
  for (int i = 0; i < 5; i++) {
    steering_servo.write(servo_left);
    digitalWrite(buzzer_pin, 1);
    delay(servo_delay);
    steering_servo.write(servo_right);
    digitalWrite(buzzer_pin, 0);
    delay(servo_delay);
  }
  steering_servo.write(servo_straight);
}  //End of wag_servo

// Wag the servo at a given speed for a given time
void wag_servo(int servo_delay, int wag_time) {
  unsigned long wait_time = millis() + wag_time * 1000;
  while (millis() < wait_time) {  // for a given time
    wag_servo(servo_delay);       // Wag the servo at a given speed
  }
}  //End of wag_servo



// ************************   COUNTDOWN   ************************//

// Countdown code - blink the light, beep and show the count-down before car takes off ...
void countdown() {

  digitalWrite(LEDR, LOW);
  digitalWrite(LEDB, LOW);

  unsigned long t_stop = millis() + 5500;
  lcd.clear();

  while (millis() < t_stop) {
    long now = millis();
    int light_delay = 250;
    static long light_on = 0;
    static long light_off;
    long t_minus = (t_stop - now);
    int beep_delay = map(t_minus, 0, 10000, 50, 350);  // beep faster as it gets closer to 0 ...
    static long beep_on = 0;
    static long beep_off;

    if (now > light_on) {
      light_on = now + 2 * light_delay;
      digitalWrite(LEDG, HIGH);
      light_off = now + light_delay;
    } else if (now > light_off) {
      digitalWrite(LEDG, LOW);
    }

    if (now > beep_on) {
      beep_on = now + beep_delay;
      digitalWrite(buzzer_pin, HIGH);
      beep_off = now + 50;  // the 50 is how long it beeps every time, the "beep_delay" is how long it waits between beeps
    } else if (now > beep_off) {
      digitalWrite(buzzer_pin, LOW);
    }

    lcd.setCursor(0, 0);
    lcd.print(F("Launching in ..."));
    lcd.setCursor(3, 1);
    lcd.print(F("T - "));
    lcd.print(min(t_minus / 1000, 99));
    lcd.print(F(" Seconds.."));
  }

  digitalWrite(buzzer_pin, 0);
}  //End of countdown
