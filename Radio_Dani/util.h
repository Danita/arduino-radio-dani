/**
 * Togle encoder mode between 0 and max
 */
void toggleEncMode(int max) {
  if (encMode < max) {
    encMode = encMode + 1;
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
      case 5: lcd.print("XPDR"); break;
      case 6: lcd.print("ADF1"); break;
      case 7: lcd.print("ADF2"); break;
      default: lcd.print("-----=INOP=-----");
    }
}

/**
 * Print numbers on fixed width
 * @param out reference to print interface
 * @param in value to format
 * @param width number of total digits
 * @param decimal number of decimal digits
 */
void printFixedWidth(Print &out, float in, byte width, byte decimals){
  float temp = in;
  
  if (decimals == 0){
    temp += 0.5;
  }
 
  if (in < 0){
    width--;
  }
 
  width -= decimals + 1;
 
  if (width < 0){
    width = 0;
  }
 
  while (temp > 10 && width){
    temp /= 10;
    width--;
  }
 
  if (in < 0){
    out.print('-');
  }
 
  while (width){
    out.print('0');
    width--;
  }
 
  out.print(abs(in), decimals);
}

