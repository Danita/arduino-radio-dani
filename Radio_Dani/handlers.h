
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



