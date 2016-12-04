
/**
 * Handle Nav/Com mode, by displaying the current value,
 * allowing to tune up/down coarse/fine the standby frequency
 * and allowing to flip current and standby frequency
 */
void handleNavComMode(
   float &currentVal, int currentOutput, 
   float &sbyVal, int sbyOutput, 
   int sbyInputCoarseDn, int sbyInputCoarseUp,
   int sbyInputFineDn, int sbyInputFineUp,
   int coInput
   ) {

    // Update stored data from simulator
    if (NewData(currentOutput)) {
      currentVal = GetData(currentOutput)/100;
    }
    if (NewData(sbyOutput)) {
      sbyVal = GetData(sbyOutput)/100;
    }

    // Display current values
    lcd.setCursor(0,1);
    printFixedWidth(lcd, currentVal, 3, 2);
    lcd.setCursor(10,1);
    printFixedWidth(lcd, sbyVal, 3, 2);

    // According to encoder direction and mode, send commands to simulator
    if (encDir == 1) {
      if (encMode == 0) {
        SimInput(sbyInputCoarseUp);
      } else {
        SimInput(sbyInputFineUp);
      }
    } else if (encDir == -1) {
      if (encMode == 0) {
        SimInput(sbyInputCoarseDn);
      } else {
        SimInput(sbyInputFineDn);
      }
    }

    // If changeover pressed, send command to simulator
    if (changeOverBtn.onPressed()) {
      SimInput(coInput);
    }

    // Change encoder mode when button is pressed
    if (encModeToggleBtn.onPressed()) {
      toggleEncMode(1);
    }
}

/**
 * Handle ADF mode, by displaying the current value,
 * allowing to tune each digit separately
 * and allowing to flip current and standby frequency
 */
void handleAdfMode(
   int &currentVal, int currentOutput, 
   int &sbyVal, int sbyOutput,
   int sbyInput100dn, int sbyInput100up,
   int sbyInput10dn, int sbyInput10up,
   int sbyInput1dn, int sbyInput1up,
   int coInput
   ) {

    // Update stored data from simulator
    if (NewData(currentOutput)) {
      currentVal = GetData(currentOutput);
    }
    if (NewData(sbyOutput)) {
      sbyVal = GetData(sbyOutput);
    }

    // Display current value
    lcd.setCursor(0,1);
    printFixedWidth(lcd, currentVal, 3, 0);
    lcd.setCursor(10,1);
    printFixedWidth(lcd, sbyVal, 3, 0);

    // According to encoder direction and mode, send commands to simulator
    switch(encMode) {
      case 0:        
         if (encDir == 1) {            
            SimInput(sbyInput100up);
         } else if (encDir == -1) {
            SimInput(sbyInput100dn);
         }
      break;
      case 1:
         if (encDir == 1) {
            SimInput(sbyInput10up);
         } else if (encDir == -1) {
            SimInput(sbyInput10dn);
         }
      break;
      case 2:
         if (encDir == 1) {
            SimInput(sbyInput1up);
         } else if (encDir == -1) {
            SimInput(sbyInput1dn);
         }
      break;
    }    

    // If changeover pressed, send command to simulator
    if (changeOverBtn.onPressed()) {
      SimInput(coInput);
    }

    // Change encoder mode when button is pressed
    if (encModeToggleBtn.onPressed()) {
      toggleEncMode(2);
    }
}



