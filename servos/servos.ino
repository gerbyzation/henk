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
  for (int i = 0; i < 4; i++) {
    rotate(i + 1, 0);
  }
  delay(1000);
//  for (int i = 0; i < 4; i++) {
//    rotate(i + 1, 180);
//  }
  delay(1000);
}

void rotate(int finger, int degrees) {
  if (degrees > 180) degrees = 180;

  if (finger == 2) degrees = 180 - degrees;

  servos[finger - 1].write(degrees);
}
