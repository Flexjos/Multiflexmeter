// meet_01
#include <RunningMedian.h>
#include <NewPing.h>
#include <SPI.h>
#include <SD.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include "RTClib.h"
RTC_DS3231 rtc;
const int chipSelect = 10; // 4(Nano)/10(atmega328P-PU)

#define ONE_WIRE_BUS 2
#define DISTANCE_ECHO 3
#define DISTANCE_TRIGGER 6
#define MAX_ULTRASONIC_DISTANCE 450
NewPing sonar(DISTANCE_TRIGGER, DISTANCE_ECHO, MAX_ULTRASONIC_DISTANCE);

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup()  
{  
Serial.begin(9600);
sensors.begin();
rtc.begin();
if (!SD.begin(chipSelect)) { return; }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
}  
  
void loop()  
{
// meet temperatuur
sensors.requestTemperatures();
float temp = sensors.getTempCByIndex(0);
// float Vsound=331.23 * sqrt((temp+273.15)/273.15);
float Vsound=331.23 + 0.606*temp;
  
// maak string met meetdata voor SD-Card
  String gegevensString = "";
  DateTime now = rtc.now();
  float distance_cm = getDistanceFromUltrasonicSensor();
  float afstand_tempcorrectie = distance_cm*(Vsound/350.877);
  
  gegevensString += String(now.unixtime()) + "," + String(temp) + "," + String(afstand_tempcorrectie);
  Serial.println(gegevensString);

// schrijf naar SD-Card
  File dataFile = SD.open("datalog.csv", FILE_WRITE);
  if (dataFile) {dataFile.println(gegevensString);
    dataFile.close();}
  else {Serial.println("datalog.csv niet beschikbaar");}
delay(10000);
  }  

// meet 21x afstand en neem mediaan
float getDistanceFromUltrasonicSensor(){
  RunningMedian samples = RunningMedian(21);
  for(int i= 0; i<21; i++){  
      delay(50);  
      float pingVal = sonar.ping();  
      float distance = pingVal / US_ROUNDTRIP_CM;  
     samples.add(distance);  
   }     
   return samples.getMedian();
}
