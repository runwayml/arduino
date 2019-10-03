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
const char* host = "http://192.168.8.102:8000/query"; // route provided by runway
//use your own computer ip on the network and the port given by runway

// Robert Frost - The Road not taken
// https://www.poetryfoundation.org/poems/44272/the-road-not-taken
String  poem [] = {
  "Two roads diverged in a yellow wood,",
  "And sorry I could not travel both",
  "And be one traveler, long I stood",
  "And looked down one as far as I could",
  "To where it bent in the undergrowth;",
  "Then took the other, as just as fair,",
  "And having perhaps the better claim,",
  "Because it was grassy and wanted wear;",
  "Though as for that the passing there",
  "Had worn them really about the same,",
  "And both that morning equally lay",
  "In leaves no step had trodden black.",
  "Oh, I kept the first for another day!",
  "Yet knowing how way leads on to way,",
  "I doubted if I should ever come back.",
  "I shall be telling this with a sigh",
  "Somewhere ages and ages hence:",
  "Two roads diverged in a wood, and I—",
  "I took the one less traveled by,",
  "And that has made all the difference."
};

int pindex = 0;


void setup() {
  Serial.begin(115200);
  delay(100);
  wifi_connect();
}

void loop() {

  // read data from analog 17 (eg A0)
  // https://learn.adafruit.com/adafruit-feather-huzzah-esp8266/pinouts
  // https://learn.adafruit.com/micropython-hardware-analog-i-o/analog-to-digital-converter
  // map the data from 0-340 to 0-19 (ie the number of lines in our poem)
  int index = map(analogRead(17), 0, 340, 0, 19);
  // Serial.println(analogRead(17));


  // test if the value has changed from previous frame
  if (pindex != index) {
    pindex = index;
    Serial.println("");
    Serial.println(index);
    
    // print if we are connected
    Serial.println("");
    Serial.print("connected : ");
    Serial.println(WiFiMulti.run() == WL_CONNECTED );
    Serial.println("");

    // Create a json object with the correct formatting from our poem
    // Use arduinojson.org/assistant to compute the capacity.
    // use the longest phrase of the poem to compute the size
    StaticJsonDocument<500> doc; // create a static document
    JsonObject root = doc.to<JsonObject>(); // make it a json object
    // Add data to it : key == "caption" / content == line from our poem
    root["caption"] = poem[index];

    serializeJson(root, Serial); // print json to serial output

    // write data to a string with json formatting
    String json;
    serializeJson(root, json);
    http_post(json); // post it !

   
    delay(1000);
  }
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

void http_post(String content) {
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {
    WiFiClient client;
    HTTPClient http;
    Serial.print("[HTTP] begin...\n");
    if (http.begin(client, host)) {  // HTTP withe the route defined by runway
      // post to http
      http.addHeader("Content-Type", "application/json");
      int httpCode = http.POST(content);
      // handle response
      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] POST... code: %d\n", httpCode);
        // file found at server
        if (httpCode == HTTP_CODE_OK) {
        }
      } else {
        Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }
      // close
      http.end();
    }
  }

}
