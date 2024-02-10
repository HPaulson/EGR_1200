/*
Simple Voltmeter
TUTORIAL 6
EGR 1200
*/
#include <LiquidCrystal.h>
int LCD_PinRS = 8;  // LCD resistor select pin (RS)
int LCD_PinE = 9;   // LCD enable pin (E)
int LCD_PinD4 = 10; // LCD data pin D4
int LCD_PinD5 = 11; // LCD data pin D5
int LCD_PinD6 = 12; // LCD data pin D6
int LCD_PinD7 = 13; // LCD data pin D7

int resolution = 1024; // # of counts over full range
float fullscale = 5.0; // maximum voltage reading
int counts = 0;        // counts reading for analog input
float measvolts = 0.0; // voltage reading

LiquidCrystal lcd(LCD_PinRS, LCD_PinE, LCD_PinD4, LCD_PinD5, LCD_PinD6, LCD_PinD7);
void setup()
{
    lcd.begin(16, 2);
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print("ARDUINO");
    lcd.setCursor(0, 1);
    lcd.print("Voltage: ");
    lcd.setCursor(14, 1);
    lcd.print("mV");
}
void loop()
{
    Readvoltage();
    delay(250);
}

void Readvoltage()
{
    counts = analogRead(A0);
    measvolts = (counts * fullscale) / resolution;
    lcd.setCursor(9, 1);
    lcd.print(measvolts);
}