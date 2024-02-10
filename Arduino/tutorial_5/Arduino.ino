/*
Timer
TUTORIAL 5
EGR 1200
*/
#include <LiquidCrystal.h>
int LCD_PinRS = 8;  // LCD resistor select pin (RS)
int LCD_PinE = 9;   // LCD enable pin (E)
int LCD_PinD4 = 10; // LCD data pin D4
int LCD_PinD5 = 11; // LCD data pin D5
int LCD_PinD6 = 12; // LCD data pin D6
int LCD_PinD7 = 13; // LCD data pin D7
int seconds = 0;    // time in full seconds
int tenths = 0;     // time in tenths of seconds
LiquidCrystal lcd(LCD_PinRS, LCD_PinE, LCD_PinD4, LCD_PinD5, LCD_PinD6, LCD_PinD7);
void setup()
{
    lcd.begin(16, 2);
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print("ARDUINO");
    lcd.setCursor(0, 1);
    lcd.print("Time: ");
    lcd.setCursor(13, 1);
    lcd.print("sec");
}
void loop()
{
    seconds = millis() / 1000;
    tenths = (millis() / 100) - (10 * seconds);
    lcd.setCursor(6, 1);
    lcd.print(seconds);
    lcd.print(".");
    lcd.print(tenths);
}