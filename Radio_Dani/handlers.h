
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
    printFixedWidth(lcd, currentVal, 5, 2);
    lcd.setCursor(10,1);
    printFixedWidth(lcd, sbyVal, 5, 2);

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


/**
 * Handle Transponder by displaying the current value,
 * allowing to tune digits 1, 2 and 3, 4 separately
 * and allowing to cycle the transponder mode
 * (off, standby, ground, test)
 */
void handleXpdrMode(
   int &currentVal, int currentOutput, 
   int &modeVal, int modeOutput,
   int tInput1000dn, int tInput1000up,
   int tInput100dn, int tInput100up,
   int tInput10dn, int tInput10up,
   int tInput1dn, int tInput1up,
   int mOffInput, int mSbyInput, int mOnInput, int mTestInput
   ) {

    // Update stored data from simulator
    if (NewData(currentOutput)) {
      currentVal = GetData(currentOutput);
    }
    if (NewData(modeOutput)) {
      modeVal = GetData(modeOutput);
    }

    // Display current value
    lcd.setCursor(0,1);
    printFixedWidth(lcd, currentVal, 4, 0);
    lcd.setCursor(10,1);
    printFixedWidth(lcd, modeVal, 1, 0);

    // According to encoder direction and mode, send commands to simulator
    switch(encMode) {
      case 0:        
         if (encDir == 1) {            
            SimInput(tInput1000up);
         } else if (encDir == -1) {
            SimInput(tInput1000dn);
         }
      break;
      case 1:
         if (encDir == 1) {
            SimInput(tInput100up);
         } else if (encDir == -1) {
            SimInput(tInput100dn);
         }
      break;
      case 2:
         if (encDir == 1) {
            SimInput(tInput10up);
         } else if (encDir == -1) {
            SimInput(tInput10dn);
         }
      break;
      case 3:
         if (encDir == 1) {
            SimInput(tInput1up);
         } else if (encDir == -1) {
            SimInput(tInput1dn);
         }
      break;
    }    

    // Cycle transponder modes with the changeover button
    if (changeOverBtn.onPressed()) {
      if (modeVal == 0) {
        SimInput(mSbyInput);
      }
      if (modeVal == 1) {
        SimInput(mOnInput);
      }
      if (modeVal == 2) {
        SimInput(mTestInput);
      }
      if (modeVal == 3) {
        SimInput(mOffInput);
      }
      if (modeVal > 3) { // Failsafe for unexpected values
        SimInput(mOffInput);
      }
    }

    // Change encoder mode when button is pressed
    if (encModeToggleBtn.onPressed()) {
      toggleEncMode(3);
    }
}


