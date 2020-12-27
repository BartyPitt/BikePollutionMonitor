
#include "Arduino.h"
#include "SPIFFS.h"


bool senderHelp();
int iterator = 1 ; 

void setup() {
  Serial.begin(115200);
  
  if (!SPIFFS.begin(true)) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
    File file = SPIFFS.open("/test.txt", FILE_WRITE);
 if (!file) {
    Serial.println("There was an error opening the file for writing");
    return;
  }
  if (file.print("TEST")) {
    Serial.println("File was written");
  } else {
    Serial.println("File write failed");
  } 

}

void loop() {
  delay(1000);
  String BigString = String( String(iterator , HEX) + "$");
  myLog.append(BigString.c_str(),false);
  

}
