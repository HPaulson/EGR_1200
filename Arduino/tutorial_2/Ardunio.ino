/*
Stoplight
TUTORIAL 2
EGR 1200
*/

int red = 13; // digital pin for red light
int yellow = 12; // digital pin for yellow light
int green = 11; // digital pin for green light

void setup() {
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
}

void loop() {
  signalgo();
  signalwarn();
  signalstop();
}

void signalwarn() {
  digitalWrite(yellow, HIGH);
  delay(5000);
  digitalWrite(yellow, LOW);
}

void signalstop() {
  digitalWrite(red, HIGH);
  delay(20000);
  digitalWrite(red, LOW);
}

void signalgo() {
  digitalWrite(green, HIGH);
  delay(35000);
  digitalWrite(green, LOW);
}