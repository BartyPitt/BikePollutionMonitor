#include <Arduino.h>
#include <Adafruit_GPS.h>

//Extra headers files that I made to help myself.
//Passwords.h Should not exist for someone else.......
#include "../Passwords.h"
#include "DebugMacros.h"
#include "PinConfig.h" // Include the pins in a seperate file to make my life easier.

Adafruit_GPS GPS(&Wire); //PLEASE DONT BREAK :(
#define GPSECHO false

uint32_t timer = millis();


typedef struct DataStoragePoints {
  uint16_t GasReading;
  int32_t longboy;
  int32_t lat;
  uint8_t seconds;
  uint8_t hours;
  unint8_t mins;
}DataStoragePoint;



void setup() {
  Serial.begin(115200);
  MainDebugPrint("Intialising");
  pinMode(LedPin , OUTPUT)
  // put your setup code here, to run once:

  GPS.begin(0x10);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_100_MILLIHERTZ); // 10 Hz update rate
  GPS.sendCommand(PGCMD_ANTENNA);
  delay(1000);
  GpsData(PMTK_Q_RELEASE);
}

void loop() {
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
  return true
}
