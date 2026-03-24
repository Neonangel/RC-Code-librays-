// ************************   NEO_PIXEL   ************************//

// This code runs the neo-pixel subroutine to do fun stuff...



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

    case 1:  // Initialize
      for (int j = 0; j < 8; j++) {
        neo_pixel.setPixelColor(j, neo_pixel.Color(255, 0, 0));
        neo_pixel.show();
        delay(75);
      }

      for (int j = 7; j > 0; j--) {
        neo_pixel.setPixelColor(j, neo_pixel.Color(0, 255, 0));
        neo_pixel.show();
        delay(75);
      }

      for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 8; j++) {
          neo_pixel.setPixelColor(j, neo_pixel.Color(0, 0, 255));
        }
        neo_pixel.show();
        delay(75);

        for (int j = 0; j < 8; j++) {
          neo_pixel.setPixelColor(j, neo_pixel.Color(0, 0, 0));
        }
        neo_pixel.show();
        delay(75);
      }
      break;

    case 2:  // cycles green once

      for (int j = 0; j <= 7; j++) {
        neo_pixel.setPixelColor(j + 0, neo_pixel.Color(250 * red / 255, 250 * green / 255, 250 * blue / 255));
        neo_pixel.setPixelColor(j - 1, neo_pixel.Color(100 * red / 255, 100 * green / 255, 100 * blue / 255));
        neo_pixel.setPixelColor(j - 2, neo_pixel.Color(10 * red / 255, 10 * green / 255, 10 * blue / 255));
        neo_pixel.setPixelColor(j - 3, neo_pixel.Color(1 * red / 255, 1 * green / 255, 1 * blue / 255));
        neo_pixel.setPixelColor(j - 4, neo_pixel.Color(0, 0, 0));
        neo_pixel.show();
        delay(speed);
      }

      for (int j = 7; j >= 0; j--) {
        neo_pixel.setPixelColor(j + 0, neo_pixel.Color(250 * red / 255, 250 * green / 255, 250 * blue / 255));
        neo_pixel.setPixelColor(j + 1, neo_pixel.Color(100 * red / 255, 100 * green / 255, 100 * blue / 255));
        neo_pixel.setPixelColor(j + 2, neo_pixel.Color(10 * red / 255, 10 * green / 255, 10 * blue / 255));
        neo_pixel.setPixelColor(j + 3, neo_pixel.Color(1 * red / 255, 1 * green / 255, 1 * blue / 255));
        neo_pixel.setPixelColor(j + 4, neo_pixel.Color(0, 0, 0));
        neo_pixel.show();
        delay(speed);
      }
      break;

    case 4:  // fail of gps 
      if gps_state = false
      neo_pixel.show();{
        neo_pixel.setPixelColor( 255,0,0)

      }
      break;

    case 5:  //
      neo_pixel.show();
      break;

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

    case 911:  //
      neo_police();
      break;

    case 2000:  //
      neo_knight_rider();
      break;

    default:  // runs if option doesn't match case
      break;

  }
}


void neo_knight_rider() {
  byte brightness = 1;
  static bool fb = 1;
  static int j = 0;
  static unsigned long last_time = 0;
  if (millis() > last_time + 75) {
    last_time = millis();
    if (fb == 1) {
      // if (j >= 7) {
      neo_pixel.setPixelColor(j - 0, neo_pixel.Color(250 * neo_red / 255, 250 * neo_green / 255, 250 * neo_blue / 255));
      neo_pixel.setPixelColor(j - 1, neo_pixel.Color(100 * neo_red / 255, 100 * neo_green / 255, 100 * neo_blue / 255));
      neo_pixel.setPixelColor(j - 2, neo_pixel.Color(10 * neo_red / 255, 10 * neo_green / 255, 10 * neo_blue / 255));
      neo_pixel.setPixelColor(j - 3, neo_pixel.Color(1 * neo_red / 255, 1 * neo_green / 255, 1 * neo_blue / 255));
      neo_pixel.setPixelColor(j - 4, neo_pixel.Color(0, 0, 0));
      j++;
      if (j > 12) {
        j = 7;
        fb = 0;
      }
    } else {
      neo_pixel.setPixelColor(j, neo_pixel.Color(250 * neo_red / 255, 250 * neo_green / 255, 250 * neo_blue / 255));
      neo_pixel.setPixelColor(j + 1, neo_pixel.Color(100 * neo_red / 255, 100 * neo_green / 255, 100 * neo_blue / 255));
      neo_pixel.setPixelColor(j + 2, neo_pixel.Color(10 * neo_red / 255, 10 * neo_green / 255, 10 * neo_blue / 255));
      neo_pixel.setPixelColor(j + 3, neo_pixel.Color(1 * neo_red / 255, 1 * neo_green / 255, 1 * neo_blue / 255));
      neo_pixel.setPixelColor(j + 4, neo_pixel.Color(0, 0, 0));
      j--;
      if (j < -4) {
        j = 0;
        fb = 1;
      }
    }
    neo_pixel.show();
  }
}



// WIP
void neo_police() {
  byte red_lights[4] = { 0, 2, 4, 6 };
  byte blue_lights[4] = { 1, 3, 5, 7 };
  static bool fb = 1;
  static byte red_on = 0;
  static unsigned long last_time = 0;
  // static unsigned long red_time = 0;
  // static unsigned long blue_time = 0;
  if (millis() > last_time + 50) {
    last_time = millis();


    if (red_on < 2) {
      if (fb == 1) {                   // on\off
        for (int j = 0; j < 2; j++) {  // red lights on
          neo_pixel.setPixelColor(red_lights[j], neo_pixel.Color(255, 0, 0));
        }
        neo_pixel.show();
        fb = 0;
      } else {
        for (int j = 0; j < 2; j++) {  // red lights off
          neo_pixel.setPixelColor(red_lights[j], neo_pixel.Color(0, 0, 0));
        }
        neo_pixel.show();
        fb = 1;
        red_on++;
      }
    } else {
      if (fb == 1) {                   // on\off
        for (int j = 3; j > 1; j--) {  // blue lights off
          neo_pixel.setPixelColor(blue_lights[j], neo_pixel.Color(0, 0, 255));
        }
        neo_pixel.show();
        fb = 0;
      } else {
        for (int j = 3; j > 1; j--) {  // blue lights on
          neo_pixel.setPixelColor(blue_lights[j], neo_pixel.Color(0, 0, 0));
        }
        neo_pixel.show();
        fb = 1;
        red_on++;
        if (red_on >= 4) {
          red_on = 0;
        }
      }
    }

    // if (fb == 1) {  // on\off

    //   for (int j = 0; j < 4; j++) {  // red lights on
    //     neo_pixel.setPixelColor(red_lights[j], neo_pixel.Color(255, 0, 0));
    //   }
    //   neo_pixel.show();

    //   for (int j = 0; j < 4; j++) {  // blue lights on
    //     neo_pixel.setPixelColor(blue_lights[j], neo_pixel.Color(0, 0, 255));
    //   }
    //   neo_pixel.show();
    //   fb = 0;
    // } else {
    //   for (int j = 0; j < 4; j++) {  // red lights off
    //     neo_pixel.setPixelColor(red_lights[j], neo_pixel.Color(0, 0, 0));
    //   }
    //   neo_pixel.show();

    //   for (int j = 0; j < 4; j++) {  // blue lights off
    //     neo_pixel.setPixelColor(blue_lights[j], neo_pixel.Color(0, 0, 0));
    //   }
    //   neo_pixel.show();
    //   fb = 1;
    // }


    neo_pixel.show();
  }
}

// WIP
void neo_disco() {}
