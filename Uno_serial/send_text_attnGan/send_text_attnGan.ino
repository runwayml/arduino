// json lib
#include <ArduinoJson.h>


// Alfred Lord Tennyson - THE EAGLE
String  poem [] = {
  "He clasps the crag with crooked hands;",
  "Close to the sun in lonely lands,",
  "Ring’d with the azure world, he stands.",
  "The wrinkled sea beneath him crawls;",
  "He watches from his mountain walls,",
  "And like a thunderbolt he falls."
};

int pindex = 0;


void setup() {
  Serial.begin(9600);
}

void loop() {

 
  int index = map(analogRead(0), 0, 1023, 0, 5);
  //Serial.println(analogRead(0));


  // test if the value has changed from previous frame
  if (pindex != index) {
    pindex = index;
    //Serial.println("");
    //Serial.println(index);

    // Create a json object with the correct formatting from our poem
    // Use arduinojson.org/assistant to compute the capacity.
    // use the longest phrase of the poem to compute the size
    const size_t capacity = JSON_OBJECT_SIZE(1) +55 ;
    DynamicJsonDocument root(capacity);
    // Add data to it : key == "caption" / content == line from our poem
    root["caption"] = poem[index];

    // write data to a string with json formatting
    String json;
    serializeJson(root, json);
    Serial.println(json);
   
    delay(100);
  }
}
