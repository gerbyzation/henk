/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo one;  // create servo object to control a servo
Servo two;
// twelve servo objects can be created on most boards
int buttonPin = 2;
int ledPin = 13;

int state = HIGH;
int reading;
int previous = LOW;
int pos = 0;    // variable to store the servo position

long time = 0;
long debounce = 200;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  one.attach(9);  // attaches the servo on pin 9 to the servo object
  two.attach(8);
}

void loop() {
  reading = digitalRead(buttonPin);

  if (reading == HIGH && previous == LOW && millis() - time > debounce) {
    if (state == HIGH)
      state = LOW;
    else
      state = HIGH;

    time = millis();
    
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

  if (state == HIGH) {
   for (pos = 0; pos <= 180; pos += 5) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      one.write(pos);              // tell servo to go to position in variable 'pos'
      delay(50);                       // waits 15ms for the servo to reach the position
    }
    for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      one.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
  }
  digitalWrite(ledPin, state);
  previous = reading;
//  one.write(0);
//  two.write(180);
//  delay(1000);
//  one.write(180);
//  two.write(0);
//  delay(1000);
}
