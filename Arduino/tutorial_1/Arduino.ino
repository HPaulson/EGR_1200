/*
Blinking Light
TUTORIAL 1
EGR 1200
*/

int red = 13; // digital pin for red light

void setup() {
  pinMode(red, OUTPUT);
}

void loop() {
  blink();
  blink();
  blink();
  delay(1000);
}

void blink() {
  digitalWrite(red, HIGH);
  delay(100);
  digitalWrite(red, LOW);
  delay(100);
}