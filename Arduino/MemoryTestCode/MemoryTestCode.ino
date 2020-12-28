
#include <Arduino.h>
#include <SPIFFS.h>


typedef struct DataStoragePoints {
  uint16_t GasReading;
  int32_t longboy;
  int32_t lat;
  uint8_t seconds;
  uint8_t hours;
  uint8_t mins;
}DataStoragePoint;


DataStoragePoints ExampleData = {10,232,234,54,100,90};


bool LogReadings(DataStoragePoint* Output);


void setup() {
  Serial.begin(115200);
  
  if (!SPIFFS.begin(true)) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  LogReadings(&ExampleData);
  LogReadings(&ExampleData);
  ReadFromFile("/test.txt");

}

void loop() {

}


bool LogReadings(DataStoragePoint* Output , String FileName){
  String Gas = String(Output->GasReading , HEX);
  String seconds = String(Output->seconds , HEX);
  String mins = String(Output->mins , HEX);
  String hours = String(Output->hours , HEX);
  String lat = String(Output->lat , HEX);
  String longboy = String(Output->longboy , HEX);
  String BigString = String("$" + Gas + "," + seconds + "," + mins + "," + hours +  "," + lat  + "," +  longboy + "£");


 File file = SPIFFS.open("/test.txt", FileName);

 if (!file) {
    Serial.println("There was an error opening the file for writing");
    return false;
  }
  if (file.print(BigString)) {
    Serial.println("File was written");
    return true;
  } else {
    Serial.println("File write failed");
    return false;
  } 
  file.close();
}


bool ReadFromFile(String Filename){
  File ReadFile = SPIFFS.open(Filename);
 
    if(!ReadFile){
        Serial.println("Failed to open file for reading");
        return false;
    }
 
    Serial.println("File Content:");
 
    while(ReadFile.available()){
 
        Serial.write(ReadFile.read());
    }
 
    ReadFile.close();
}
