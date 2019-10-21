// import Runway library
import com.runwayml.*;
// import serial libraty
import processing.serial.*;

// reference to runway instance
RunwayHTTP runway;
// instance of the port we will be connecting to
Serial myPort;  

// The caption to send
String data = "";

void setup() {
  size(100, 100);
  frameRate(25);
  // setup Runway
  runway = new RunwayHTTP(this);
  // don't send messages to Runway continuously
  runway.setAutoUpdate(false);

  printArray(Serial.list()); // list the available serial devices connected
  String portName = Serial.list()[3]; // our board is the third in the list (change accordingly)
  myPort = new Serial(this, portName, 9600);
  myPort.bufferUntil('\n');
}

void draw() {
  background(0);
}

// this function triggers itself when a message is receive via serial
void serialEvent (Serial myPort) {

  try {
    while (myPort.available() > 0) { 
      String inBuffer = myPort.readStringUntil('\n');
      if (inBuffer != null) {
        if (inBuffer.substring(0, 1).equals("{")) {
          JSONObject json = parseJSONObject(inBuffer);
          if (json != null) {

            data = json.toString(); // interpret the json object as a string
            runway.query(data); // send it to runway
            
          }
        }
      }
    }
  } 
  catch (Exception e) {
  }
}
