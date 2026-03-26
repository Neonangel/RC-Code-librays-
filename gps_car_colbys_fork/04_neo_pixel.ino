// ************************   NEO_PIXEL   ************************//

// This code runs the neo-pixel subroutine to do fun stuff...

// Ratio of green pixels (right side) to total 8 pixels. 0.0 = all red, 1.0 = all green.
// Call neo_set_bar_ratio() from any other module to update this at runtime.
float neo_bar_ratio = 0.5;

// Sets the green/red bar ratio from an outside function.
// Why: allows other modules (e.g. speed or sensor logic) to drive the bar display
// without needing to know the internal pixel layout.
// ratio: 0.0 (all red) to 1.0 (all green), clamped automatically.
void neo_set_bar_ratio(float ratio) {
  if (ratio < 0.0) ratio = 0.0;
  if (ratio > 1.0) ratio = 1.0;
  neo_bar_ratio = ratio;
}



// ************************   NEO_DESIGN   ************************//

// single input function, calls multi input function
void neo_design(int option) {
  neo_design(neo_red, neo_green, neo_blue, option);
}



// ************************   NEO_DESIGN   ************************//

// multi input function
void neo_design(int red, int green, int blue, int option) {
  neo_time = neo_time + neo_delay;
  static int last_option = 0;

  if (last_option != option) {
    neo_pixel.clear();
    last_option = option;
  }

  int speed = 100;
  switch (option) {
    case 0:  // Turn Off
      for (int j = 0; j < 8; j++) {
        neo_pixel.setPixelColor(j, neo_pixel.Color(0, 0, 0));
      }
      neo_pixel.show();  // turn neo_pixel off
      break;

    case 1: {  // Rainbow cycle - spreads all 8 pixels evenly across the hue wheel
               // and rotates the hue over time. Non-blocking: uses millis() instead of delay().
      static uint16_t hue = 0;
      static unsigned long last_time = 0;
      if (millis() > last_time + 20) {
        last_time = millis();
        for (int j = 0; j < 8; j++) {
          // Offset each pixel evenly around the 65536-step hue wheel
          uint16_t pixel_hue = hue + (uint16_t)(j * 65536L / 8);
          neo_pixel.setPixelColor(j, neo_pixel.gamma32(neo_pixel.ColorHSV(pixel_hue)));
        }
        neo_pixel.show();
        hue += 256;  // Advance the hue each frame to animate the cycle
      }
      break;
    }
    case 2: {  // Inward sweep - lights one pixel from each end per step, moving toward center.
               // Why: creates a closing/converging effect in blue.
               // After all 8 pixels are lit, holds for 2 seconds then repeats.
               // Non-blocking: uses millis() for both step timing and the hold delay.
      static int step = 0;
      static unsigned long last_time = 0;
      static bool waiting = false;

      if (waiting) {
        // All pixels on - hold for 2 seconds then clear and restart
        if (millis() > last_time + 2000) {
          neo_pixel.clear();
          neo_pixel.show();
          step = 0;
          waiting = false;
          last_time = millis();
        }
      } else {
        if (millis() > last_time + 150) {
          last_time = millis();
          // Light the symmetrical pair: left side and mirrored right side
          neo_pixel.setPixelColor(step,     neo_pixel.Color(0, 0, 255));
          neo_pixel.setPixelColor(7 - step, neo_pixel.Color(0, 0, 255));
          neo_pixel.show();
          step++;
          if (step >= 4) {
            // All 4 pairs lit (all 8 pixels on) - begin hold
            waiting = true;
            last_time = millis();
          }
        }
      }
      break;
    }
    case 4: {  // Green/red bar - red fills from the left, green fills from the right.
               // Why: provides a visual ratio indicator (e.g. battery, throttle, sensor level).
               // Ratio is controlled via neo_set_bar_ratio() from outside this module.
      int green_count = (int)(neo_bar_ratio * 8 + 0.5);  // number of green pixels (right side)
      int red_count   = 8 - green_count;                  // remaining pixels are red (left side)
      for (int j = 0; j < red_count;   j++) neo_pixel.setPixelColor(j,             neo_pixel.Color(255, 0,   0));
      for (int j = 0; j < green_count; j++) neo_pixel.setPixelColor(red_count + j, neo_pixel.Color(0,   255, 0));
      neo_pixel.show();
      break;
    }
    case 5: {  // No-GPS warning - reads the global stop_no_gps_signal flag set by the GPS module.
               // Why: gives a visual alert on the strip when GPS signal is lost.
      if (stop_no_gps_signal) {
        for (int j = 0; j < 8; j++) neo_pixel.setPixelColor(j, neo_pixel.Color(255, 165, 0));
        neo_pixel.show();
      } else {
        neo_pixel.clear();
        neo_pixel.show();
      }
      break;
    }
    case 6:  //
      neo_pixel.show();
      break;
    case 7:  //
      neo_pixel.show();
      break;
    case 8:  //
      neo_pixel.show();
      break;
    case 70:  //
      neo_disco();
      break;
    case 911: {  // Police lights - alternates red and blue flashes, 2 red then 2 blue.
                 // Why: emergency/alert visual effect using interleaved pixel positions.
                 // Non-blocking: uses millis() to time each flash at 50ms intervals.
      byte red_lights[4]  = { 0, 2, 4, 6 };
      byte blue_lights[4] = { 1, 3, 5, 7 };
      static bool fb     = 1;
      static byte red_on = 0;
      static unsigned long last_time = 0;
      if (millis() > last_time + 50) {
        last_time = millis();
        if (red_on < 2) {
          if (fb == 1) {                   // red lights on
            for (int j = 0; j < 2; j++) {
              neo_pixel.setPixelColor(red_lights[j], neo_pixel.Color(255, 0, 0));
            }
            neo_pixel.show();
            fb = 0;
          } else {                         // red lights off
            for (int j = 0; j < 2; j++) {
              neo_pixel.setPixelColor(red_lights[j], neo_pixel.Color(0, 0, 0));
            }
            neo_pixel.show();
            fb = 1;
            red_on++;
          }
        } else {
          if (fb == 1) {                   // blue lights on
            for (int j = 3; j > 1; j--) {
              neo_pixel.setPixelColor(blue_lights[j], neo_pixel.Color(0, 0, 255));
            }
            neo_pixel.show();
            fb = 0;
          } else {                         // blue lights off
            for (int j = 3; j > 1; j--) {
              neo_pixel.setPixelColor(blue_lights[j], neo_pixel.Color(0, 0, 0));
            }
            neo_pixel.show();
            fb = 1;
            red_on++;
            if (red_on >= 4) red_on = 0;
          }
        }
      }
      break;
    }
    case 2000: {  // Knight Rider - comet trail bounces left and right across the strip.
                  // Why: classic scanning effect using neo_red/green/blue color with fading tail.
                  // Non-blocking: uses millis() to advance one step every 75ms.
      static bool fb = 1;
      static int j   = 0;
      static unsigned long last_time = 0;
      if (millis() > last_time + 75) {
        last_time = millis();
        if (fb == 1) {  // moving forward
          neo_pixel.setPixelColor(j - 0, neo_pixel.Color(250 * neo_red / 255, 250 * neo_green / 255, 250 * neo_blue / 255));
          neo_pixel.setPixelColor(j - 1, neo_pixel.Color(100 * neo_red / 255, 100 * neo_green / 255, 100 * neo_blue / 255));
          neo_pixel.setPixelColor(j - 2, neo_pixel.Color(10  * neo_red / 255, 10  * neo_green / 255, 10  * neo_blue / 255));
          neo_pixel.setPixelColor(j - 3, neo_pixel.Color(1   * neo_red / 255, 1   * neo_green / 255, 1   * neo_blue / 255));
          neo_pixel.setPixelColor(j - 4, neo_pixel.Color(0, 0, 0));
          j++;
          if (j > 12) { j = 7; fb = 0; }
        } else {        // moving backward
          neo_pixel.setPixelColor(j + 0, neo_pixel.Color(250 * neo_red / 255, 250 * neo_green / 255, 250 * neo_blue / 255));
          neo_pixel.setPixelColor(j + 1, neo_pixel.Color(100 * neo_red / 255, 100 * neo_green / 255, 100 * neo_blue / 255));
          neo_pixel.setPixelColor(j + 2, neo_pixel.Color(10  * neo_red / 255, 10  * neo_green / 255, 10  * neo_blue / 255));
          neo_pixel.setPixelColor(j + 3, neo_pixel.Color(1   * neo_red / 255, 1   * neo_green / 255, 1   * neo_blue / 255));
          neo_pixel.setPixelColor(j + 4, neo_pixel.Color(0, 0, 0));
          j--;
          if (j < -4) { j = 0; fb = 1; }
        }
        neo_pixel.show();
      }
      break;
    }
    default:  // runs if option doesn't match case
      break;
  }
}
