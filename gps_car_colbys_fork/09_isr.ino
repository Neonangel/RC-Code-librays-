// ************************   ISR   ************************//

// This file contains the various ISR's that the arduino uses
// isr == Interrupt Service Routine



// ************************   ISR_ENCODER   ************************//

// isr of encoder to change the lcd screens
void isr_encoder() {
  if (LCD_screen_old == LCD_screen)  //this inherently slows it down a bit so it doesn't jump too many screens at once
  {
    if (digitalRead(Dt) == LOW) {
      LCD_screen--;
    } else {
      LCD_screen++;
    }
  }
  // constrain lcd_screen in disp function
}


// // ************************   ISR_ENCODER_NEW   ************************//

// // different isr of encoder to change the lcd screens
// void isr_encoder_new()  //
// {
//   if (LCD_screen_old == LCD_screen) {
//     LCD_screen++;
//     if (digitalRead(Dt) == LOW) {
//       LCD_screen -= 2;
//     }
//   }
//   // wrap lcd screen around...
//   // if (LCD_screen > num_LCD_screens) {
//   //   LCD_screen = 0;
//   // }
//   // if (LCD_screen < 0) {
//   //   LCD_screen = num_LCD_screens;
//   // }
//   LCD_screen = constrain(LCD_screen, 0, num_LCD_screens);  // Cap screens at limits
// }



// ************************   ISR_HALL   ************************//

// isr for the Hall Effect Sensor
void isr_hall() {
  hall_count++;  // Counts the number of times a magnet passes the hall sensor
}