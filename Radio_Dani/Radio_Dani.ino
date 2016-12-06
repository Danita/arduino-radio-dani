/**
 * Multi radio
 * Daniela Rodríguez Careri <dcareri@gmail.com>
 *  
 * @todo Initialize with sim values at startup 
 * @todo Show message while X-Plane is connecting because the device is unresponsive until then
 */
#include <ArdSim_Interface.h>
#include <LiquidCrystal.h>
#include <Encoder.h>
#include <RBD_Timer.h>
#include <RBD_Button.h>

const int PIN_ENC_A = 2;
const int PIN_ENC_B = 3;
const int PIN_ENC_MODE_BTN = 4;
const int PIN_CO_BTN = 29;
const int PIN_MODE_1 = 28;
const int PIN_MODE_2 = 27;
const int PIN_MODE_3 = 26;
const int PIN_MODE_4 = 25;
const int PIN_MODE_5 = 24;
const int PIN_MODE_6 = 23;
const int PIN_MODE_7 = 22;

LiquidCrystal lcd(19, 18, 17, 16, 15, 14);
Encoder enc(PIN_ENC_A, PIN_ENC_B);
RBD::Button changeOverBtn(PIN_CO_BTN);
RBD::Button encModeToggleBtn(PIN_ENC_MODE_BTN);

float Com1 = 0;
float Com1st = 0;
float Com2 = 0;
float Com2st = 0;
float Nav1 = 0;
float Nav1st = 0;
float Nav2 = 0;
float Nav2st = 0;
int Adf1 = 0;
int Adf1st = 0;
int Adf2 = 0;
int Adf2st = 0;
int Xpdr = 0;
int XpdrMode = 0;

int mode = 0;
int encMode = 0;
int encDir = 0;
int lastEncVal = 0;

#include "Util.h"
#include "Handlers.h"

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
  
  changeOverBtn.setDebounceTimeout(30);
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
    encMode = 0; // Reset encoder mode when changing radio modes
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

  switch(mode) {

    // COM 2
    case 1:
      handleNavComMode(Com2, 3, Com2st, 4, 11, 12, 13, 14, 15);
      break; 

    // COM 1
    case 2:
      handleNavComMode(Com1, 1, Com1st, 2, 1, 2, 3, 4, 5);
      break;
      
    // NAV 2
    case 3:
      handleNavComMode(Nav2, 7, Nav2st, 8, 16, 17, 18, 19, 20);
      break;

    // NAV 1
    case 4:
      handleNavComMode(Nav1, 5, Nav1st, 6, 6, 7, 8, 9, 10);
      break;

    // Transponder
    case 5:
      handleXpdrMode(Xpdr, 9, XpdrMode, 10, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46);
      break;

    // ADF 1
    case 6:
      handleAdfMode(Adf1, 11, Adf1st, 12, 21, 22, 23, 24, 25, 26, 27);
      break;

    // ADF 2
    case 7:
      handleAdfMode(Adf2, 13, Adf2st, 14, 28, 29, 30, 31, 32, 33, 34);
      break;
      
  }
  
  lastEncVal = encVal;
}      


