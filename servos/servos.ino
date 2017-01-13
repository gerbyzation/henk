#include <Servo.h>
#include <CapacitiveSensor.h>

long time = 0;
int state = HIGH;

boolean detection;
boolean previous = false;

int debounce = 200;
int nDetects;

CapacitiveSensor cs_4_2 = CapacitiveSensor(4, 2);

Servo servos[4];
int servoPins[4] = {9, 8, 7, 6};
int ledPin = 13;
// 1 is pink/ring
// 2 is thumb
// 3 is pointy finger
// 4 is middle finger

int anglesClosed[4] = {90, 90, 90, 100};
int anglesHandShake[4] = {70, 70, 70, 80};

bool closed = false;

int pos = 0;    // variable to store the servo position

void setup() {
  Serial.begin(9600);
  cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);  //Calibrate the sensor... 
  Serial.println("setup done");
  
  for (int i = 0; i < 4; i++) {
    servos[i].attach(servoPins[i]);
  }
  pinMode(ledPin, OUTPUT);

  // reset to open hand position
  openHand();
}

void loop() {
  // Take reading and count detections in sequence
  long sensorReading = cs_4_2.capacitiveSensor(30);
  if (sensorReading > 60) {
    detection = true;
    nDetects++;
  } else {
    detection = false;
    nDetects = 0;
  }

  // stuff to control LED
  if(detection == true  && millis() - time>debounce) {
    if(state == LOW) {
      state = HIGH;
    } else {
//       state = LOW;
       time = millis();     
    }
  } else {
    state = LOW;
  }

  digitalWrite(ledPin, state);
  previous = detection;

  Serial.print("time ");
  Serial.print(millis()-time);
  Serial.print(" the other thing ");
  Serial.print(detection);
  Serial.print(" detects ");
  Serial.println(nDetects);

  
  if (!closed && nDetects > 25) {
    handShake();
    closed = true;
  } else {
    openHand();
  }

  delay(10);
}

void handShake() {
  for (int i = 0; i < 4; i++) {
    rotate(i+1, anglesHandShake[i]);
  }
  delay(2000);
  openHand();
  delay(5000);
  closed = false;
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
