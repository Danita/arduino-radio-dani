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

//  ArdSimScan;  

  int newMode = getMode();
  if (newMode != mode) {
    mode = newMode;
    displayMode(mode);
  }

  switch(mode) {
    case 2:
      if (NewData(1)) {
        lcd.setCursor(0,1);
        lcd.print(GetData(1)/100);
      }
      if (NewData(2)) {
        lcd.setCursor(10,1);
        lcd.print(GetData(2)/100);
      }
      /*
      if (getEncDir() == -1) {
        if (encMode == 0) {
          SimInput(1);
        } else {
          SimInput(3);
        }
      } else if (getEncDir() == 1) {
        if (encMode == 0) {
          SimInput(2);
        } else {
          SimInput(4);
        }
      }
*/
      // Changeover TODO: debouncear
      if (changeOverBtn.onPressed()) {
        SimInput(5);
      }
      
    break;
  }

  // Cambiar modo encoder
  if (encModeToggleBtn.onPressed()) {
    toggleEncMode();
  }
  
  lcd.setCursor(10, 0);
  lcd.print(
    String(encMode) +  ' ' +
    String(enc.read())
    );
}      

void toggleEncMode() {
  if (encMode == 0) {
    encMode = 1;
  } else {
    encMode = 0;
  }
}

int getEncDir() {
  return 0;
}

/**
 * Obtener el modo actual según el rotary switch
 */
int getMode() {
  int mode = 999;
  if (digitalRead(38) == 0) {
    mode = 7;
  } 
  if (digitalRead(39) == 0) {
    mode = 6;
  } 
  if (digitalRead(40) == 0) {
    mode = 5;
  } 
  if (digitalRead(41) == 0) {
    mode = 4;
  } 
  if (digitalRead(42) == 0) {
    mode = 3;
  } 
  if (digitalRead(43) == 0) {
    mode = 2;
  }
  if (digitalRead(44) == 0) {
    mode = 1;
  }
  return mode;  
}

/**
 * Mostrar el modo especificado
 */
void displayMode(int mode) {
  lcd.clear();
  lcd.setCursor(0, 0);  
    switch(getMode()) {
      case 1:
        lcd.print("COM 2");    
        break;
      case 2:
        lcd.print("COM 1");    
        break;
      case 3:
        lcd.print("NAV 2");    
        break;
      case 4:
        lcd.print("NAV 1");    
        break;
      case 5:
        lcd.print("Transponder");    
        break;
      case 6:
        lcd.print("ADF");    
        break;
      case 7:
        lcd.print("DME");    
        break;
      default:
        lcd.print("---INOP---");
    }  
}

