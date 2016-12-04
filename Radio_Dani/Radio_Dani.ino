#include <ArdSim_Interface.h>
#include <LiquidCrystal.h>
#include <Encoder.h>
#include <RBD_Timer.h>
#include <RBD_Button.h>

LiquidCrystal lcd(19, 18, 17, 16, 15, 14);
Encoder enc(2,3);
RBD::Button changeOverBtn(45);
RBD::Button encModeToggleBtn(4);

float Com1 = 130.00;
float Com1st = 125.00;
float Nav1 = 109.25;
float Nav1st = 110.05;
float DME = 109.25;
float ADF = 630;
int XPDR = 1200;

int mode = 0;
int encMode = 0;
int encDir = 0;
int lastEncVal = 0;

//------------------------------------------
void setup()  { 
 
  BoardNumber 1;    
  InputPin(NOINPUT);  

  pinMode(38, INPUT_PULLUP);
  pinMode(39, INPUT_PULLUP);
  pinMode(40, INPUT_PULLUP);
  pinMode(41, INPUT_PULLUP);
  pinMode(42, INPUT_PULLUP);
  pinMode(43, INPUT_PULLUP);
  pinMode(44, INPUT_PULLUP);
  
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

  // Mostrar modo de la radio (COM1, NAV1, etc.)
  int newMode = getMode();
  if (newMode != mode) {
    mode = newMode;
    displayMode(mode);
  }

  // Obtener la dirección en que se está girando el encoder
  int encVal = enc.read();
  if (encVal > lastEncVal) {
    encDir = 1;
  } else if (encVal < lastEncVal) {
    encDir = -1;
  } else {
    encDir = 0;
  }

  // Cambiar modo encoder al presionar el pulsador
  if (encModeToggleBtn.onPressed()) {
    toggleEncMode();
  }
  
  switch(mode) {

    // COM 1
    case 2:
    
      if (NewData(1)) {
        Com1 = GetData(1)/100;
      }
      
      if (NewData(2)) {
        Com1st = GetData(2)/100;
      }

      lcd.setCursor(0,1);
      lcd.print(Com1);
      lcd.setCursor(10,1);
      lcd.print(Com1st);
      
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

      // Changeover
      if (changeOverBtn.onPressed()) {
        SimInput(5);
      }
      
    break;
  }


  /*
//  lcd.setCursor (4, 0);
//  lcd.print("M" + String(encMode));
  lcd.setCursor (4, 0);
  lcd.print("D" + String(encDir));
  lcd.setCursor (7, 0);
  lcd.print("P" + String(lastEncVal));
  lcd.setCursor (11, 0);
  lcd.print("E" + String(encVal));
  
    
  if (millis() % 10 == 0) {
    lcd.clear();
  }
  */
  
  lastEncVal = encVal;
}      

/**
 * Alterna el modo del encoder entre 0 y 1
 */
void toggleEncMode() {
  if (encMode == 0) {
    encMode = 1;
  } else {
    encMode = 0;
  }
}

/**
 * Obtener el modo actual según el rotary switch
 */
int getMode() {
  int mode = 999;
  if (digitalRead(38) == 0) { mode = 7; } 
  if (digitalRead(39) == 0) { mode = 6; } 
  if (digitalRead(40) == 0) { mode = 5; } 
  if (digitalRead(41) == 0) { mode = 4; } 
  if (digitalRead(42) == 0) { mode = 3; } 
  if (digitalRead(43) == 0) { mode = 2; }
  if (digitalRead(44) == 0) { mode = 1; }
  return mode;
}

/**
 * Mostrar el modo especificado
 */
void displayMode(int mode) {
  lcd.clear();
  lcd.setCursor(0, 0);  
    switch(getMode()) {
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

