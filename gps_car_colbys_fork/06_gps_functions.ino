// ************************   GPS FUNCTIONS   ************************//

// This file contains various functions for the gps



// ************************   GET_GPS_DATA   ************************//

// This code is meant to be called to get GPS data
void get_gps_data(float target_lat, float target_lon) {

  static float old_lat = 0;
  static float old_lon = 0;
  float lat = gps.location.lat();
  float lon = gps.location.lng();

  if (old_lat == 0 || old_lon == 0) {  // take care of first time
    old_lat = lat;
    old_lon = lon;
  }

  // estimate how far traveled total...
  if (gps.location.isValid()) {
    dist_to_target = gps.distanceBetween(lat, lon, target_lat, target_lon);
    dist_traveled = dist_traveled + gps.distanceBetween(lat, lon, old_lat, old_lon);
    old_lat = lat;
    old_lon = lon;
  }

  // Figure out GPS Date / Time
  byte gps_month = gps.date.month();
  byte gps_day = gps.date.day();
  byte gps_year = gps.date.year() - 2000;  // put it in a shorter format
  int gps_hour = gps.time.hour();          // this needs to be int so late at night it doesn't get all jacked up
  byte gps_minute = gps.time.minute();
  byte gps_second = gps.time.second();

  // Knowing that Salt Lake is 6-7 hours behind the standard GPS time (depending on DST) ...
  // Also, assuming that DST is between between Feb 28 and Nov 1 (not accurate, but close enough)
  byte UT_hour_offset = 7;
  if (gps_month > 2 && gps_month < 11) {
    UT_hour_offset = 6;  // when on daylight savings time...
  }
  if (gps_hour < UT_hour_offset) {
    gps_day = gps_day - 1;  // the whole late-night thing (hasn't crossed 12am yet)
  }
  gps_hour = gps_hour - UT_hour_offset;
  if (gps_hour < 0) {
    gps_hour = gps_hour + 24;
  }
  if (gps_hour > 12) {
    gps_hour = gps_hour - 12;
    ampm = 1;
  }

  sprintf(gps_time, "%2d:%02d:%02d", gps_hour, gps_minute, gps_second);
  sprintf(gps_date, "%0d/%0d/%0d", gps_month, gps_day, gps_year);
  sprintf(gps_speed, "%2d", round(gps.speed.mph()));
}  //End of get_gps_data

// ************************   use_gps_heading   ************************//

// This code is used to get the gps_heading and then use it as our main heading.
// We want to switch from compass to gps when we're going faster than 2 miles per hour
void use_gps_heading(float target_lat, float target_lon) {
  compass_heading = gps.course.deg();
  gps_heading = atan2(target_lon - gps.location.lng(), target_lat - gps.location.lat()) * 180.0 / M_PI;
  
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
}


// ************************   STOP_NO_GPS   ************************//
//Gobal var add, i dont know why this wasnt't added sooner. -BMW

bool stop_no_gps_signal = false;

// This code is meant to be called if the GPS signal isn't found
// It gives the "Check Wriring" error on LCD
void stop_no_gps() {
  static bool write_flag = 1;
  lcd.clear();
  while (1) {
    if (write_flag) {
      stop_no_gps_signal = true;
      lcd.setCursor(0, 0);
      lcd.print(F("No GPS"));
      lcd.setCursor(0, 1);
      lcd.print(F("Check Wiring"));
      write_flag = 0;
      delay(500);
    } else {
      lcd.clear();
      write_flag = 1;
      delay(250);
    }
  }
}  //End of stop_no_gps