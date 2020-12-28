/*
Code written by Barty Pitt from Imperial Collage London.
in December 2020.
Designed to record the pollution and then tag each of these points with a gps co-ordinate
Uses an adafruit gps and using an adafruit pollution sensor.
The code is writen for ESP32 and tested on esp32 Wroom. with 4mb of Flash.
Should work with many other boards although this is not garunteed.
Not sure if 

*/



#include <Arduino.h>
#include <SPIFFS.h>
#include <Adafruit_GPS.h>
#include <Ticker.h>
#include <Wire.h>

//Extra headers files that I made to help myself.
//Passwords.h Should not exist for someone else.......
//#include "../Passwords.h"
#include "DebugMacros.h"
#include "PinConfig.h" // Include the pins in a seperate file to make my life easier.


 #define GPSECHO false


// The Gps is attached to the defult i2c pins , atleast I hope it is. 

typedef struct DataStoragePoints {
 //Gas reading 
  uint16_t GasReading; 
//Gps Reading
  int32_t longboy;
  int32_t lat;
//Time got form the gps.
  uint8_t seconds;
  uint8_t hours;
  uint8_t mins;
}DataStoragePoint;


void setup() {
  Serial.begin(115200);
  MainDebugPrint("Intialising");
  pinMode(LedPin , OUTPUT);


  Wire.begin(SDAPin ,SCLPin); //Setting up the i2c to run of two non standard ports.
  Adafruit_GPS GPS(&Wire); //PLEASE DONT BREAK

  GPS.begin(0x10);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_100_MILLIHERTZ); // 10 Hz update rate
  GPS.sendCommand(PGCMD_ANTENNA);
  
  delay(1000);
  GpsData(PMTK_Q_RELEASE);
  ReadFromFile("/logs/log1.log")
}

void loop() {
  DataStoragePoint DataStore;
  GatherReadings(&DataStore);
  LogReadings(&DataStore, "/logs/log1.log");
  delay(1000); // his thing is powered of a portable charger , when the esp32 is powered down it drops bellow the minium threshold.
  // put your main code here, to run repeatedly:

}

bool GatherReadings(DataStoragePoint* Output){
  GPS.read();
  Output->GasReading = analogRead(AnalogPin);
  Output->seconds = GPS.seconds;
  Output->mins = GPS.minute;
  Output->hours = GPS.hour;
  Output->lat = GPS.latitude_fixed;
  Output->longboy = GPS.latitude_fixed;
  return true;
}

bool LogReadings(DataStoragePoint* Output , String FileName){
  String Gas = String(Output->GasReading , HEX);
  String seconds = String(Output->seconds , HEX);
  String mins = String(Output->mins , HEX);
  String hours = String(Output->hours , HEX);
  String lat = String(Output->lat , HEX);
  String longboy = String(Output->longboy , HEX);
  String BigString = String("$" + Gas + "," + seconds + "," + mins + "," + hours +  "," + lat  + "," +  longboy + "£");


 File file = SPIFFS.open(FileName , FILE_APPEND);

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