/*
Intersection with Pedestrian Crossing
TUTORIAL 4

*/

int red = 13;                  // digital pin for red light
int yellow = 12;               // digital pin for yellow light
int green = 11;                // digital pin for green light
int xred = 7;                  // digital pin for intersecting red light
int xyellow = 6;               // digital pin for intersecting yellow light
int xgreen = 5;                // digital pin for intersecting green light
int button = 2;                // digital pin for pedestrian crosswalk pushbutton
int pedstopblue = 9;           // digital pin for pedestrian crossing blue "stop"
int pedgowhite = 8;            // digital pin for pedestrian crossing white "go"
int blinkcount = 0;            // initial setting for crosswalk blink counter
boolean buttonpressed = false; // initial setting for crosswalk pushbutton check
long starttime = 0;            // initial setting for time counter starttime
long endtime = 0;              // initial setting for time counter endtime

void setup()
{
    pinMode(button, INPUT);
    pinMode(red, OUTPUT);
    pinMode(yellow, OUTPUT);
    pinMode(green, OUTPUT);
    pinMode(xred, OUTPUT);
    pinMode(xyellow, OUTPUT);
    pinMode(xgreen, OUTPUT);
    pinMode(pedstopblue, OUTPUT);
    pinMode(pedgowhite, OUTPUT);
    digitalWrite(green, HIGH);
    digitalWrite(xred, HIGH);
    digitalWrite(pedstopblue, HIGH);
}
void loop()
{
    signalwarn();
    signalstop();
    if (buttonpressed == true)
        pedcross();
    crosstrafficgo();
    crosstrafficwarn();
    crosstrafficstop();
    if (buttonpressed == true)
        pedcross();
    signalgo();
}

void signalwarn()
{
    digitalWrite(green, LOW);
    digitalWrite(yellow, HIGH);
    starttime = millis();
    endtime = starttime;
    while ((endtime - starttime) <= 3000)
    {
        if (digitalRead(button) == HIGH)
            buttonpressed = true;
        endtime = millis();
    }
}

void signalstop()
{
    digitalWrite(yellow, LOW);
    digitalWrite(red, HIGH);
}

void signalgo()
{
    digitalWrite(red, LOW);
    digitalWrite(green, HIGH);
    starttime = millis();
    endtime = starttime;
    while ((endtime - starttime) <= 15000)
    {
        if (digitalRead(button) == HIGH)
            buttonpressed = true;
        endtime = millis();
    }
    while ((buttonpressed == false) && ((endtime - starttime) <= 42000))
    {
        if (digitalRead(button) == HIGH)
            buttonpressed = true;
        endtime = millis();
    }
}

void crosstrafficgo()
{
    digitalWrite(xred, LOW);
    digitalWrite(xgreen, HIGH);
    starttime = millis();
    endtime = starttime;
    while ((endtime - starttime) <= 15000)
    {
        if (digitalRead(button) == HIGH)
            buttonpressed = true;
        endtime = millis();
    }
    while ((buttonpressed == false) && ((endtime - starttime) <= 27000))
    {
        if (digitalRead(button) == HIGH)
            buttonpressed = true;
        endtime = millis();
    }
}

void crosstrafficwarn()
{
    digitalWrite(xgreen, LOW);
    digitalWrite(xyellow, HIGH);
    starttime = millis();
    endtime = starttime;
    while ((endtime - starttime) <= 3000)
    {
        if (digitalRead(button) == HIGH)
            buttonpressed = true;
        endtime = millis();
    }
}
void crosstrafficstop()
{
    digitalWrite(xyellow, LOW);
    digitalWrite(xred, HIGH);
}

void pedcross()
{
    digitalWrite(yellow, LOW);
    digitalWrite(red, HIGH);
    digitalWrite(pedstopblue, LOW);
    digitalWrite(pedgowhite, HIGH);
    delay(18000);
    digitalWrite(pedgowhite, LOW);
    for (blinkcount = 1; blinkcount < 6; blinkcount = blinkcount + 1)
    {
        digitalWrite(pedstopblue, HIGH);
        delay(500);
        digitalWrite(pedstopblue, LOW);
        delay(500);
    }
    digitalWrite(pedstopblue, HIGH);
    delay(2000);
    buttonpressed = false;
}