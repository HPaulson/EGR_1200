/*
Final Presentation
EGR 1200
*/

#include <LiquidCrystal.h>
#include <Adafruit_ADS1015.h>

int LCD_PinRS = 8;      // LED resistor select pin (RS)
int LCD_PinE = 9;       // LED enable pin (E)
int LCD_PinD4 = 10;     // LED data pin D4
int LCD_PinD5 = 11;     // LED data pin D5
int LCD_PinD6 = 12;     // LED data pin D6
int LCD_PinD7 = 13;     // LED data pin D7
int buttonPin = 2;      // button pin
int resolution = 32768; // 16 bit system --> 65536 counts over full range
// (Note: because both positive & negative voltages may be read, resolution=counts/2)
float fullscale = 6.144; // maximum voltage reading
// (Note: "fullscale" is set as default value, but can changed below if gain is used.)
float excitationA = 4.67;   // excitation for sensor A (V)
int zerocountsA = 0;        // zero counts reading for sensor A input
int countsA = 0;            // counts reading for sensor A input
float voltageA = 0;         // voltage reading for sensor A (mV)
float gagefactorA = 2.06;   // GF for gage A (change in resistance per strain)
int strainA = 0;            // strain reading for strain gage A (microstain)
float excitationB = 4.67;   // excitation for sensor B (V)
int zerocountsB = 0;        // zero counts reading for sensor B input
int countsB = 0;            // counts reading for sensor B input
float voltageB = 0;         // voltage reading for sensor B (mV)
float gagefactorB = 2.06;   // GF for gage B (change in resistance per strain)
int strainB = 0;            // strain reading for strain gage B (microstain)
boolean zerobutton = false; // used to determine if zero button is pressed

int redLED = 6;
int greenLED = 3;

LiquidCrystal lcd(LCD_PinRS, LCD_PinE, LCD_PinD4, LCD_PinD5, LCD_PinD6, LCD_PinD7);
Adafruit_ADS1115 ads1115;
void setup()
{
    lcd.begin(16, 2);
    lcd.clear();
    pinMode(buttonPin, OUTPUT);
    pinMode(redLED, OUTPUT);
    pinMode(greenLED, OUTPUT);
    ads1115.setGain(GAIN_SIXTEEN); // selected gain
    fullscale = 0.256;             // maximum voltage reading (V) based on chosen gain
    ads1115.begin();
    zerovalues();
}
void loop()
{
    pinMode(buttonPin, INPUT);
    digitalWrite(buttonPin, LOW);
    pinMode(buttonPin, OUTPUT);
    if (zerobutton == true)
        zerovalues();
    else
        readvalues();
    int maxStrain = highestStrain(strainA, strainB);
    int blinkSpeedMS = blinkSpeed(maxStrain);
    if (blinkSpeedMS == 0)
    {
        digitalWrite(redLED, LOW);
        digitalWrite(greenLED, HIGH);
    }
    else
    {
        digitalWrite(greenLED, LOW);
        blink(blinkSpeedMS);
    }
}

void readvalues()
{
    if (digitalRead(buttonPin) == HIGH)
        zerovalues();
    countsA = ads1115.readADC_Differential_0_1();
    countsB = ads1115.readADC_Differential_2_3();
    voltageA = ((countsA - zerocountsA) * fullscale * 1000) / resolution;
    voltageB = ((countsB - zerocountsB) * fullscale * 1000) / resolution;
    strainA = 1000000 * (4 * voltageA) / (gagefactorA * excitationA * 1000);
    strainB = 1000000 * (4 * voltageB) / (gagefactorB * excitationB * 1000);
    lcd.setCursor(0, 0);
    lcd.print("StrainA= ");
    lcd.print(strainA);
    lcd.print(" ue ");
    lcd.setCursor(0, 1);
    lcd.print("StrainB= ");
    lcd.print(strainB);
    lcd.print(" ue ");
    debugprint();
    delay(500);
}

void zerovalues()
{
    delay(500);
    lcd.setCursor(0, 0);
    lcd.print("Ready to zero...");
    lcd.setCursor(0, 1);
    lcd.print("Release button. ");
    delay(3000);
    zerocountsA = ads1115.readADC_Differential_0_1();
    zerocountsB = ads1115.readADC_Differential_2_3();
}

void debugprint()
{
    Serial.begin(9600);
    Serial.print("zerocountsA = ");
    Serial.println(zerocountsA);
    Serial.print("countsA = ");
    Serial.println(countsA);
    Serial.print("voltageA = ");
    Serial.println(voltageA);
    Serial.print("strainA = ");
    Serial.println(strainA);
    Serial.println();
    Serial.print("zerocountsB = ");
    Serial.println(zerocountsB);
    Serial.print("countsB = ");
    Serial.println(countsB);
    Serial.print("voltageB = ");
    Serial.println(voltageB);
    Serial.print("strainB = ");
    Serial.println(strainB);
    Serial.println();
    Serial.println();
    Serial.println();
}

int highestStrain(int strainA, int strainB)
{
    int absStrainA = abs(strainA);
    int absStrainB = abs(strainB);

    if (absStrainA >= absStrainB)
    {
        return absStrainA;
    }
    else
    {
        return absStrainB;
    }
}

int blinkSpeed(int strain)
{
    // Green - 3, Input
    // Red - 6, Input
    int absStrain = strain;
    int blinkSpeedMS;

    if (absStrain < 600)
    {
        blinkSpeedMS = 0;
    }
    else if (absStrain >= 800)
    {
        blinkSpeedMS = 50;
    }
    else
    {
        blinkSpeedMS = 2000 - (absStrain - 600) * 9.75;
    }
    return blinkSpeedMS;
}

void blink(int delayMS)
{
    digitalWrite(redLED, HIGH);
    delay(50);
    digitalWrite(redLED, LOW);
    delay(delayMS);
}