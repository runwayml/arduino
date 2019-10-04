// Morse alphabet code from :
//https://www.instructables.com/id/Arduino-Based-Text-to-Morse-Translator/

// wifi lib
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
// json lib
#include <ArduinoJson.h>

// wifi settings
ESP8266WiFiMulti WiFiMulti;
const char* ssid = "put-your-wifi-ssid-here"; // wifi ID
const char* pass = "put-your-wifi-password-here"; // wifi password
const char* host = "http://192.168.8.102:8000/data"; // route provided by runway
//use your own computer ip on the network and the port given by runway

const int ledPin = 2; // use the D2 pin to light our led
const int time_base = 50; // sets a dot to 50 milliseconds
const int dash = 3 * time_base; // sets a dash to 150 milliseconds

void setup() {
  Serial.begin(115200);
  wifi_connect();
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // print if we are connected
  Serial.println("");
  Serial.print("connected : ");
  Serial.println(WiFiMulti.run() == WL_CONNECTED );
  Serial.println("");

  // get the data and serialize it to read it as a json object
  String dat = http_get(); // get the data from arduino as a string
  //Serial.println(dat); // print the raw data from runway

  // Use arduinojson.org/assistant to compute the capacity.
  // We don't really know the size in this case so might want to adjust it for longer bits of text
  StaticJsonDocument<500> doc;
  deserializeJson(doc, dat); // write the result from httpget to a JSON doc
  String out = doc["out"]; // extract the line corresponding to the "out" key

  // run through ou line character by character and make it blink our led.
  for (int i = 0 ; i < out.length() ; i++) {
    Serial.println(out.charAt(i));
    morse_alphabet(out.charAt(i));
  }

  // take some time before the next line
  digitalWrite(2, LOW);
  delay(1000);

}


void wifi_connect() {
  Serial.println();
  Serial.println();
  Serial.println();
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid, pass);
  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }
  delay(1000);
  Serial.print("connected : ");
  Serial.println(WiFiMulti.run() == WL_CONNECTED );
}

String http_get() {
  String result = "";
  if ((WiFiMulti.run() == WL_CONNECTED)) {
    WiFiClient client;
    HTTPClient http;
    Serial.print("[HTTP] begin...\n");
    if (http.begin(client, host)) { // HTTP
      Serial.print("[HTTP] GET...\n");
      // start connection and send HTTP header
      int httpCode = http.GET();
      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);
        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          result = http.getString();
          //Serial.println(payload);
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }
      http.end();
    } else {
      Serial.printf("[HTTP} Unable to connect\n");
    }
  }
  return result;
}


void morse_alphabet(char in) {

  if (in == 'a') { // checks if letter a was typed on serial
    digitalWrite(ledPin, HIGH); // turns light on
    delay(time_base); // delays for the time of a dot 
    digitalWrite(ledPin, LOW); // turns off light
    delay(time_base); // waits for time of a dot (Morse code specifies time between parts of a letter to be one dot)
    digitalWrite(ledPin, HIGH); // turns on light
    delay(dash); // delays for the time of a dash (3 times dot)
    digitalWrite(ledPin, LOW); // turns off light
    delay(3 * time_base);
  } // waits for 3 times dot time (Morse code specifies the time between two letters to be 3 dots)

  // Morse code for b (dash dot dot dot)
  if (in == 'b') {
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(3 * time_base);
  }

  // Morse code for c (dash dot dash dot)
  if (in == 'c') {
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(3 * time_base);
  }

  // Morse code for d (dash dot dot)
  if (in == 'd') {
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(3 * time_base);
  }

  //Morse code for e (dot)
  if (in == 'e') {
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(3 * time_base);
  }

  // Morse code for f (dot dot dash dot)
  if (in == 'f') {
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(3 * time_base);
  }

  // Morse code for g (dash dash dot)
  if (in == 'g') {
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(3 * time_base);
  }

  // Morse code for h (dot dot dot dot)
  if (in == 'h') {
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(3 * time_base);
  }

  // Morse code for i (dot dot)
  if (in == 'i') {
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(3 * time_base);
  }

  // Morse code for j (dot dash dash dash)
  if (in == 'j') {
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(3 * time_base);
  }

  // Morse code for k (dash dot dash)
  if (in == 'k') {
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(3 * time_base);
  }

  // Morse code for l (dot dash dot dot)
  if (in == 'l') {
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(3 * time_base);
  }

  // Morse code for m (dash dash)
  if (in == 'm') {
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(3 * time_base);
  }

  // Morse code for n (dash dot)
  if (in == 'n') {
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(3 * time_base);
  }

  // Morse code for o (dash dash dash)
  if (in == 'o') {
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(3 * time_base);
  }

  // Morse code for p (dot dash dash dot)
  if (in == 'p') {
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(3 * time_base);
  }

  // Morse code for q (dash dash dot dash)
  if (in == 'q') {
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(3 * time_base);
  }

  // Morse code for r (dot dash dot)
  if (in == 'r') {
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(3 * time_base);
  }

  // Morse code for s (dot dot dot)
  if (in == 's') {
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(3 * time_base);
  }

  // Morse code for t (dash)
  if (in == 't') {
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(3 * time_base);
  }

  // Morse code for u (dot dot dash)
  if (in == 'u') {
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(3 * time_base);
  }

  // Morse code for v (dot dot dot dash)
  if (in == 'v') {
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(3 * time_base);
  }

  // Morse code for w (dot dash dash)
  if (in == 'w') {
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(3 * time_base);
  }

  // Morse code for x (dash dot dot dash)
  if (in == 'x') {
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(3 * time_base);
  }

  // Morse code for y (dash dot dash dash)
  if (in == 'y') {
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(3 * time_base);
  }


  // Morse code for z (dash dash dot dot)
  if (in == 'z') {
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(3 * time_base);
  }

  // Morse code for a space (delay of seven dots)
  if (in == ' ') {
    digitalWrite(ledPin, LOW);
    delay(7 * time_base);
  } // keeps the light off for seven dots, as specified by Morse code

  // Morse code for 1 (dot dash dash dash dash)
  if (in == '1') {
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(3 * time_base);
  }

  // Morse code for two (dot dot dash dash dash)
  if (in == '2') {
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(3 * time_base);
  }

  // Morse code for 3 (dot dot dot dash dash)
  if (in == '3') {
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(3 * time_base);
  }

  // Morse code for 4 (dot dot dot dot dash)
  if (in == '4') {
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(3 * time_base);
  }

  // Morse code for 5 (dot dot dot dot dot)
  if (in == '5') {
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(3 * time_base);
  }

  // Morse code for 6 (dash dot dot dot dot)
  if (in == '6') {
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(3 * time_base);
  }

  // Morse code for 7 (dash dash dot dot dot)
  if (in == '7') {
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(3 * time_base);
  }

  // Morse code for 8 (dash dash dash dot dot)
  if (in == '8') {
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(3 * time_base);
  }

  // Morse code for 9 (dash dash dash dash dot)
  if (in == '9') {
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(time_base);
    digitalWrite(ledPin, LOW);
    delay(3 * time_base);
  }

  // Morse code for 0 (dash dash dash dash dash)
  if (in == '0') {
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(time_base);
    digitalWrite(ledPin, HIGH);
    delay(dash);
    digitalWrite(ledPin, LOW);
    delay(3 * time_base);
  }
}
