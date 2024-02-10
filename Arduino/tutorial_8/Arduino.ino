/*
Distance Meter with Alarms
TUTORIAL 8
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
int redPin = 3; // red LED pin for CLOSE alarm
int yellowPin = 4; // yellow LED pin for FAR alarm
int buzzerPin = 5; // buzzer pin

int resolution = 1024; // # of counts over full range
float fullscale = 5.0; // maximum voltage reading
int counts = 0;        // counts reading for analog input
float measvolts = 0.0; // voltage reading

int closelimit = 100; // distance limit for close alarm (mm)
int farlimit = 300;   // fdistance limit for far alarm (mm)
int toneclose = 750; // tone for buzzer associated with CLOSE alarm
int tonefar = 250; // tone for buzzer associated with FAR alarm
long duration = 0;    // time duration value used with distance sensor
long distance = 0;    // distance measured by ultrasonic sensor

LiquidCrystal lcd(LCD_PinRS, LCD_PinE, LCD_PinD4, LCD_PinD5, LCD_PinD6, LCD_PinD7);
void setup()
{
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(redPin, OUTPUT);
    pinMode(yellowPin, OUTPUT);
    pinMode(buzzerPin, OUTPUT);
    digitalWrite(redPin, LOW);
    digitalWrite(yellowPin, LOW);
    noTone(buzzerPin);
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
    digitalWrite(redPin, LOW);
    digitalWrite(yellowPin, LOW);
    lcd.setCursor(10, 1);
    if (distance > farlimit)
    {
        lcd.print(" FAR ");
        tone(buzzerPin, tonefar);
        digitalWrite(yellowPin, HIGH);
    }
    else if (distance < closelimit)
    {
        lcd.print("CLOSE ");
        tone(buzzerPin, toneclose);
        digitalWrite(redPin, HIGH);
    }
    else
    {
        lcd.print(distance);
        lcd.print(" mm ");
        noTone(buzzerPin);
    }
}