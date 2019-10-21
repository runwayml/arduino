// import Runway library
import com.runwayml.*;
// import serial libraty
import processing.serial.*;

// reference to runway instance
RunwayHTTP runway;
// instance of the port we will be connecting to
Serial myPort;  

// The caption to display 
String txt;
// result image will be stored here
PImage runwayResult;

void setup() {
  size(600, 600);
  frameRate(25);
  // setup Runway
  runway = new RunwayHTTP(this);
  // don't send messages to Runway continuously
  runway.setAutoUpdate(false);

  printArray(Serial.list()); // list the available serial devices connected
  String portName = Serial.list()[3]; // our board is the third in the list (change accordingly)
  myPort = new Serial(this, portName, 9600); // this app - 3rd board in the list - talking speed
  myPort.bufferUntil('\n'); // read the data line by line

  background(0);
  textAlign(CENTER, BOTTOM);
  textSize(12);
  stroke(255);
  fill(255);
}

void draw() {
  background(0);
  if (runwayResult != null) {
    image(runwayResult, 0, 0, width, height);
  }
  if (txt!=null) {
    text(txt, width/2, height);
  }
}

// this function triggers itself when a message is receive via serial
void serialEvent (Serial myPort) {

  try {
    while (myPort.available() > 0) {  // if connection is ok
      String inBuffer = myPort.readStringUntil('\n'); // read line by line
      if (inBuffer != null) { // is buffer is not null
        if (inBuffer.substring(0, 1).equals("{")) { //parse the begining { 
          JSONObject json = parseJSONObject(inBuffer); // parse the json string to a json object
          if (json != null) { // if json object is not null

            // read the data and store it in a variable
            txt =json.getString("caption");
            // send the data to runway
            String data = json.toString(); // interpret the json object as a string
            runway.query(data); // send it to runway
            
          }
        }
      }
    }
  } 
  catch (Exception e) {
  }
}

// this is called when new Runway data is available
void runwayDataEvent(JSONObject runwayData) {
  // point the sketch data to the Runway incoming data 
  String base64ImageString = runwayData.getString("result");
  // try to decode the image from
  try {
    PImage result = ModelUtils.fromBase64(base64ImageString);
    if (result != null) {
      runwayResult = result;
    }
  }
  catch(Exception e) {
    e.printStackTrace();
  }
}
