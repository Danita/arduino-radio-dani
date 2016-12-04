#include <ArdSim_Interface.h>
#include <LiquidCrystal.h>
#include <Encoder.h>
#include <RBD_Timer.h>
#include <RBD_Button.h>

const int PIN_ENC_A = 2;
const int PIN_ENC_B = 3;
const int PIN_ENC_MODE_BTN = 4;
const int PIN_CO_BTN = 45;
const int PIN_MODE_1 = 44;
const int PIN_MODE_2 = 43;
const int PIN_MODE_3 = 42;
const int PIN_MODE_4 = 41;
const int PIN_MODE_5 = 40;
const int PIN_MODE_6 = 39;
const int PIN_MODE_7 = 38;

LiquidCrystal lcd(19, 18, 17, 16, 15, 14);
Encoder enc(PIN_ENC_A, PIN_ENC_B);
RBD::Button changeOverBtn(PIN_CO_BTN);
RBD::Button encModeToggleBtn(PIN_ENC_MODE_BTN);

float Com1 = 000.00;
float Com1st = 000.00;
float Nav1 = 000.00;
float Nav1st = 000.00;
float DME = 000.00;
float ADF = 000;
int XPDR = 0000;

int mode = 0;
int encMode = 0;
int encDir = 0;
int lastEncVal = 0;

//------------------------------------------
void setup()  { 
 
  BoardNumber 1;    
  InputPin(NOINPUT);  

  pinMode(PIN_MODE_1, INPUT_PULLUP);
  pinMode(PIN_MODE_2, INPUT_PULLUP);
  pinMode(PIN_MODE_3, INPUT_PULLUP);
  pinMode(PIN_MODE_4, INPUT_PULLUP);
  pinMode(PIN_MODE_5, INPUT_PULLUP);
  pinMode(PIN_MODE_6, INPUT_PULLUP);
  pinMode(PIN_MODE_7, INPUT_PULLUP);
  
  changeOverBtn.setDebounceTimeout(10);
  encModeToggleBtn.setDebounceTimeout(10);
  
  lcd.begin(16, 2);
  lcd.print("Dani Multiradio");
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("                ");
} 

//------------------------------------------
void loop()   { 

  ArdSimScan;  

  // Show radio mode (COM1, NAV1, etc.)
  int newMode = readMode();
  if (newMode != mode) {
    mode = newMode;
    displayMode(mode);
  }

  // Get encoder direction (-1, 0, +1)
  int encVal = enc.read() / 4;
  if (encVal > lastEncVal) {
    encDir = 1;
  } else if (encVal < lastEncVal) {
    encDir = -1;
  } else {
    encDir = 0;
  }

  // Change encoder mode when button is pressed
  if (encModeToggleBtn.onPressed()) {
    toggleEncMode();
  }
  
  switch(mode) {

    // COM 1
    case 2:

      // Update stored data from simulator
      if (NewData(1)) {
        Com1 = GetData(1)/100;
      }
      if (NewData(2)) {
        Com1st = GetData(2)/100;
      }

      // Display current values
      lcd.setCursor(0,1);
      lcd.print(Com1);
      lcd.setCursor(10,1);
      lcd.print(Com1st);

      // According to radio mode and encoder mode, send commands to simulator
      if (encDir == 1) {
        if (encMode == 0) {
          SimInput(2);
        } else {
          SimInput(4);
        }
      } else if (encDir == -1) {
        if (encMode == 0) {
          SimInput(1);
        } else {
          SimInput(3);
        }
      }

      // If changeover pressed, send command to simulator
      if (changeOverBtn.onPressed()) {
        SimInput(5);
      }
      
    break;
  }
  
  lastEncVal = encVal;
}      


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


