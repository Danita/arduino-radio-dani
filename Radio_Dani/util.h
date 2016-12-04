/**
 * Togle encoder mode between 0 (coarse) and 1 (fine)
 */
void toggleEncMode() {
  if (encMode == 0) {
    encMode = 1;
  } else {
    encMode = 0;
  }
}

/**
 * Get the current radio mode according to the rotary switch
 */
int readMode() {
  int mode = 999;
  if (digitalRead(PIN_MODE_7) == 0) { mode = 7; } 
  if (digitalRead(PIN_MODE_6) == 0) { mode = 6; } 
  if (digitalRead(PIN_MODE_5) == 0) { mode = 5; } 
  if (digitalRead(PIN_MODE_4) == 0) { mode = 4; } 
  if (digitalRead(PIN_MODE_3) == 0) { mode = 3; } 
  if (digitalRead(PIN_MODE_2) == 0) { mode = 2; }
  if (digitalRead(PIN_MODE_1) == 0) { mode = 1; }
  return mode;
}

/**
 * Show selected mode on screen
 */
void displayMode(int mode) {
  lcd.clear();
  lcd.setCursor(0, 0);  
    switch(readMode()) {
      case 1: lcd.print("COM 2"); break;
      case 2: lcd.print("COM 1"); break;
      case 3: lcd.print("NAV 2"); break;
      case 4: lcd.print("NAV 1"); break;
      case 5: lcd.print("Transponder"); break;
      case 6: lcd.print("ADF"); break;
      case 7: lcd.print("DME"); break;
      default: lcd.print("---INOP---");
    }
}

