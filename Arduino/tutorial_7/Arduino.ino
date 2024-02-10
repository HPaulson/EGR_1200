/*
Distance Meter
TUTORIAL 7
EGR 1200
*/

#include <LiquidCrystal.h>
int LCD_PinRS = 8;  // LCD resistor select pin (RS)
int LCD_PinE = 9;   // LCD enable pin (E)
int LCD_PinD4 = 10; // LCD data pin D4
int LCD_PinD5 = 11; // LCD data pin D5
int LCD_PinD6 = 12; // LCD data pin D6
int LCD_PinD7 = 13; // LCD data pin D7
int trigPin = 6;    // ultrasonic distance sensor trigger pin
int echoPin = 7;    // ultrasonic distance sensor echo pin

int resolution = 1024; // # of counts over full range
float fullscale = 5.0; // maximum voltage reading
int counts = 0;        // counts reading for analog input
float measvolts = 0.0; // voltage reading

int closelimit = 200; // distance limit for close alarm (mm)
int farlimit = 400;   // fdistance limit for far alarm (mm)
long duration = 0;    // time duration value used with distance sensor
long distance = 0;    // distance measured by ultrasonic sensor

LiquidCrystal lcd(LCD_PinRS, LCD_PinE, LCD_PinD4, LCD_PinD5, LCD_PinD6, LCD_PinD7);
void setup()
{
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    lcd.begin(16, 2);
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print("ARDUINO");
    lcd.setCursor(0, 1);
    lcd.print("Distance: ");
}

void loop()
{
    Readdistance();
    delay(250);
}

void Readvoltage()
{
    counts = analogRead(A0);
    measvolts = (counts * fullscale) / resolution;
    lcd.setCursor(9, 1);
    lcd.print(measvolts);
}

void Readdistance()
{
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.340 / 2;
    lcd.setCursor(10, 1);
    if (distance > farlimit)
    {
        lcd.print(" MAX ");
    }
    else if (distance < closelimit)
    {
        lcd.print("MIN ");
    }
    else
    {
        lcd.print(distance);
        lcd.print(" mm ");
    }
}