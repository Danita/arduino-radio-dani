#include <ArdSim_Interface.h>
#include <LiquidCrystal.h>

// LCD: 19, 18, 17, 16, 15, 14
// Rotary encoder: 2, 3
// Rotary encoder pushbutton: 4
// Rotary switch: 38, 39, 40, 41, 42, 43, 44
// Button: 45

LiquidCrystal lcd(19, 18, 17, 16, 15, 14);

//------------------------------------------
void setup()  { 
  BoardNumber 1;    
  InputPin(NOINPUT); // Adding/removing this makes no difference
  InputPin(38,45);
  InputPin(2,4);
  OutputPin(14,19); 
  
  lcd.begin(16, 2);  
  lcd.print("Hello world");
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("           ");
} 

//------------------------------------------
void loop()   { 
  ArdSimScan;  
  for (int i=1; i<8;  i++)  { 
     if (ReadInput( i+37, ON )) {
        lcd.setCursor(0, 1);
        lcd.print( i );
     }
  }
}      

