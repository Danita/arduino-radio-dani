
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
    lcd.print(currentVal);
    lcd.setCursor(10,1);
    lcd.print(sbyVal);

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
 * Handle ADF mode, by displaying the current value
 * and allowing to tune each digit separately
 * (changeover button does nothing)
 */
void handleAdfMode(
   int &currentVal, int currentOutput, 
   int input100dn, int input100up,
   int input10dn, int input10up,
   int input1dn, int input1up   
   ) {

    // Update stored data from simulator
    if (NewData(currentOutput)) {
      currentVal = GetData(currentOutput);
    } 

    // Display current value
    lcd.setCursor(0,1);
    printFixedWidth(lcd, currentVal, 3, 0);

    // According to encoder direction and mode, send commands to simulator
    switch(encMode) {
      case 0:        
         if (encDir == 1) {            
            SimInput(input100up);
         } else if (encDir == -1) {
            SimInput(input100dn);
         }
      break;
      case 1:
         if (encDir == 1) {
            SimInput(input10up);
         } else if (encDir == -1) {
            SimInput(input10dn);
         }
      break;
      case 2:
         if (encDir == 1) {
            SimInput(input1up);
         } else if (encDir == -1) {
            SimInput(input1dn);
         }
      break;
    }    

    // Change encoder mode when button is pressed
    if (encModeToggleBtn.onPressed()) {
      toggleEncMode(2);
    }
}



