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
      case 5: lcd.print("Transponder"); break;
      case 6: lcd.print("ADF1"); break;
      case 7: lcd.print("ADF2"); break;
      default: lcd.print("---INOP---");
    }
}


void printFixedWidth(Print &out, float in, byte width, byte decimals){
  float temp = in;
 
  //compensate for rounding if we don't want decimals
  if(decimals == 0){
    temp += 0.5;
  }
 
  //do we need room for a minus?
  if(in < 0){
    width--;
  }
 
  //compensate for after the decimal and the decimal
  width -= decimals + 1;
 
  //no room left?
  if(width < 0){
    width = 0;
  }
 
  //let's check width of variable efore decimal
  while(temp > 10 && width){
    temp /= 10;
    width--;
  }
 
  //now let's print it
  //is it negative?
  if(in < 0){
    out.print('-');
  }
 
  //fill it up
  while(width){
    out.print('0');
    width--;
  }
 
  //now print the number
  out.print(abs(in), decimals);
}

