/*
Intersection
TUTORIAL 3
EGR 1200
*/

int red = 13; // digital pin for red light
int yellow = 12; // digital pin for yellow light
int green = 11; // digital pin for green light
int xred = 7; // digital pin for intersecting red light
int xyellow = 6; // digital pin for intersecting yellow light
int xgreen = 5; // digital pin for intersecting green light

void setup() {
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(xred, OUTPUT);
  pinMode(xyellow, OUTPUT);
  pinMode(xgreen, OUTPUT);

  // Starting state: Green light & No crossing
  digitalWrite(green, HIGH);
  digitalWrite(xred, HIGH);
}

void loop() {
  // Run traffic light
  signalgo();
  signalwarn();
  signalstop();

  // Right cross walk
  crosstrafficgo();
  crosstrafficwarn();
  crosstrafficstop();
}

void signalgo() {
  digitalWrite(green, HIGH);
  delay(42000);
  digitalWrite(green, LOW);
}

void signalwarn() {
  digitalWrite(yellow, HIGH);
  delay(3000);
  digitalWrite(yellow, LOW);
}

void signalstop() {
  digitalWrite(red, HIGH);
}

void crosstrafficgo() {
    digitalWrite(xred, LOW);
    digitalWrite(xgreen, HIGH);
    delay(27000);
    digitalWrite(xgreen, LOW);
}

void crosstrafficwarn() {
    digitalWrite(xyellow, HIGH);
    delay(3000);
    digitalWrite(xyellow, LOW);
}

void crosstrafficstop() {
  digitalWrite(xred, HIGH);
  digitalWrite(red, LOW);
}

/*
Assignment:

1. The six subroutine fns are signalgo(), signalwarn(), signalstop(), crosstrafficgo(), crosstrafficwarn(), & crosstrafficstop();
2. In order (Same as above) - signalgo(), signalwarn(), signalstop(), crosstrafficgo(), crosstrafficwarn(), & crosstrafficstop();
3. Digital pin 6 controlls xyellow (The yellow crossing light)
4. It takes one min. to cycle through the full pattern.

*/