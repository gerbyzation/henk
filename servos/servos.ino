/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo servos[4];
int servoPins[4] = {9, 8, 7, 6};
int ledPin = 13;
// 1 is pink/ring
// 2 is thumb
// 3 is pointy finger
// 4 is middle finger

int anglesClosed[4] = {90, 90, 90, 100};
int anglesHandShake[4] = {60, 60, 60, 70};

bool closed = false;

int pos = 0;    // variable to store the servo position

long time = 0;
long debounce = 200;

void setup() {
  for (int i = 0; i < 4; i++) {
    servos[i].attach(servoPins[i]);
  }
  pinMode(ledPin, OUTPUT);
}

void loop() {
  openHand();
  delay(5000);
  if (!closed) {
    handShake();
    closed = true;
  } else {
    openHand();
  }
  delay(3000);
//  handShake();
}

void handShake() {
  for (int i = 0; i < 4; i++) {
    rotate(i+1, anglesHandShake[i]);
  }
  delay(2000);
  openHand();
}

void closeHand() {
  for (int i = 0; i < 4; i++) {
    rotate(i+1, anglesClosed[i]);
  }
}

void openHand () {
  for (int i = 0; i < 4; i++) {
    rotate(i + 1, 0);
  }
}

void rotate(int finger, int degrees) {
  if (degrees > 180) degrees = 180;

  if (finger == 2) degrees = 180 - degrees;

  servos[finger - 1].write(degrees);
}
