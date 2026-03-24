// ************************   COMPASS FUNCTIONS   ************************//

// This file contains various functions for the compass



// ************************   GET_COMPASS_DATA   ************************//

void get_compass_data(float target_lat, float target_lon) {

  if (hmc_flag) {
    sensors_event_t event;
    compass_HMC.getEvent(&event);
    compass_heading = atan2(event.magnetic.y, event.magnetic.x) * 180.0 / M_PI;  // - compass_offset;
  } else {
    compass_QMC.read();
    compass_heading = compass_QMC.getAzimuth();
  }
  compass_heading = compass_heading - compass_offset;
  gps_heading = atan2(target_lon - gps.location.lng(), target_lat - gps.location.lat()) * 180.0 / M_PI;

  // Once you have your compass_heading, you must then add your 'Declination Angle', which
  // is the 'Error' of the magnetic field in your location in radians.
  // Find yours here: http://www.magnetic-declination.com/
  // Salt Lake is 11°0', or 11.0°

  float declinationAngle = 11.0;
  compass_heading = compass_heading + declinationAngle;

  // Check for wrap due to addition of declination or subtraction of offset.
  if (abs(compass_heading) > 180) {
    if (compass_heading > 180) {
      compass_heading -= 360;
    }
    if (compass_heading < -180) {
      compass_heading += 360;
    }
  }

  heading_error = compass_heading - gps_heading;
  // wrap heading_error so it is between -180 and 180
  if (heading_error < -180) {
    heading_error += 360;
  }
  if (heading_error > 180) {
    heading_error += -360;
  }
}  //End of get_compass_data



// ************************   STOP_NO_COMPASS   ************************//

// This code is meant to be called if the compass is not connected
// It gives the "Compass NOT detected" error on LCD
void stop_no_compass() {
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print(F("Compass NOT detected"));
  lcd.setCursor(0, 2);
  lcd.print(F("Program will not"));
  lcd.setCursor(0, 3);
  lcd.print(F("continue ..."));
  while (1) {
    Serial.println(F("Ooops, no Compass detected ... Check your wiring!"));
  }
}  //End of stop_no_compass
