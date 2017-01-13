import controlP5.*;
import processing.serial.*;

ControlP5 cp5;

boolean closed = false;

Serial myPort;  // Create object from Serial class
int val;      // Data received from the serial port
String input;

void setup() {
  size(400, 400);
  smooth();
  
  cp5 = new ControlP5(this);
  
  cp5.addToggle("toggle")
    .setPosition(150, 180)
    .setSize(100, 40);
  // I know that the first port in the serial list on my mac
  // is always my  FTDI adaptor, so I open Serial.list()[0].
  // On Windows machines, this generally opens COM1.
  // Open whatever port is the one you're using.
  String portName = Serial.list()[2];
  myPort = new Serial(this, portName, 9600);
}

void draw() {
  background(0);             // Set background to white
  if (closed == true) {              // If the serial value is 0,
    fill(0);                   // set fill to black
  } 
  else {                       // If the serial value is not 0,
    fill(204);                 // set fill to light gray
  }
  rect(50, 50, 100, 100);
}

void toggle(boolean state) {
  if (state == true) {
    // close the door!
    myPort.write("close\n");
    closed = true;
  } else {
    println("open it again");
    myPort.write("open\n");
    closed = false;
  }
}

void serialEvent(Serial myPort) {
  input = myPort.readStringUntil('\n');
  if (input != null) {
    println(input);
  }
}