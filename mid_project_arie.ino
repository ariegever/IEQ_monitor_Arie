#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include "Adafruit_SHT4x.h"
#include "SparkFun_SCD30_Arduino_Library.h"

#define CS_PIN 10

Adafruit_SHT4x sht4;
SCD30 airSensor;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  // Setup SHT40 
  if (!sht4.begin()) {
    Serial.println("SHT40 not found! Check wiring.");
    while (1);
  }
  sht4.setPrecision(SHT4X_HIGH_PRECISION);
  sht4.setHeater(SHT4X_NO_HEATER);
  Serial.println("SHT40 OK");

  // Setup SCD30 
  if (!airSensor.begin()) {
    Serial.println("SCD30 not found! Check wiring.");
    while (1);
  }
  Serial.println("SCD30 OK");

  //  Setup SD card 
  if (!SD.begin(CS_PIN)) {
    Serial.println("SD card failed! Check wiring or FAT32 format.");
    while (1);
  }
  Serial.println("SD card OK");

  // Write CSV header
  File dataFile = SD.open("data.csv", FILE_WRITE);
  if (dataFile) {
    dataFile.println("millis,T_SHT40,RH_SHT40,CO2_SCD30,T_SCD30,RH_SCD30");
    dataFile.close();
  } else {
    Serial.println("Error opening data.csv!");
    while (1);
  }

  Serial.println("Setup complete. Logging started.");
  Serial.println("millis,T_SHT40,RH_SHT40,CO2_SCD30,T_SCD30,RH_SCD30");
}

void loop() {
  // Read T/RH from SHT40 
  sensors_event_t humidity, temp;
  sht4.getEvent(&humidity, &temp);
  float t_sht  = temp.temperature;
  float rh_sht = humidity.relative_humidity;

  // Read CO2/T/RH from SCD30 
  float co2 = 0, t_scd = 0, rh_scd = 0;
  if (airSensor.dataAvailable()) {
    co2   = airSensor.getCO2();
    t_scd = airSensor.getTemperature();
    rh_scd = airSensor.getHumidity();
  }

  unsigned long t_ms = millis();

  //  Serial.println 
  Serial.print(t_ms);   Serial.print(",");
  Serial.print(t_sht);  Serial.print(",");
  Serial.print(rh_sht); Serial.print(",");
  Serial.print(co2);    Serial.print(",");
  Serial.print(t_scd);  Serial.print(",");
  Serial.println(rh_scd);

  //  Log to SD card
  File dataFile = SD.open("data.csv", FILE_WRITE);
  if (dataFile) {
    dataFile.print(t_ms);   dataFile.print(",");
    dataFile.print(t_sht);  dataFile.print(",");
    dataFile.print(rh_sht); dataFile.print(",");
    dataFile.print(co2);    dataFile.print(",");
    dataFile.print(t_scd);  dataFile.print(",");
    dataFile.println(rh_scd);
    dataFile.close();
  } else {
    Serial.println("ERROR: Could not write to SD!");
  }

  // Delay 30 seconds 
  delay(30000);
}