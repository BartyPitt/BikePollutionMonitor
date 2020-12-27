#include <Ticker.h>

#include "Arduino.h"
#include <Adafruit_GPS.h>
#include <Ticker.h>
#include <logger_spiffs.h>


LoggerSPIFFS myLog("/log/Data.log");
bool senderHelp();
int iterator = 1 ; 

void setup() {
  Serial.begin(115200);
  myLog.begin();
  myLog.setFlusherCallback(senderHelp);
  myLog.flush();
  // put your setup code here, to run once:

}

void loop() {
  delay(1000);
  String BigString = String( String(iterator , HEX) + "$");
  myLog.append(BigString.c_str(),false);
  if (Serial){
    myLog.flush();
  }
  // put your main code here, to run repeatedly:

}


bool senderHelp(char* buffer, int n){
  int index=0;
  // Check if there is another string to print
  while(index<n && strlen(&buffer[index])>0){
    Serial.print("---");
    int bytePrinted=Serial.print(&buffer[index]);
    Serial.println("---");
    // +1, the '\0' is processed
    index += bytePrinted+1;
  }
  return true;
}
