// druk_temp_rf_transmitter
// Jos Goossen
// multiflexmeter.nl

#include <DataCoder.h>
// https://bayesianadventures.wordpress.com/2013/09/20/arduino-rf-communications-data-encoder-for-virtualwire/
#include <VirtualWire.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);


const int transmit_pin = 12;
const int led_pin = 13;
const int baudRate = 1000;

void setup()
{
  pinMode(led_pin,OUTPUT);
  SetupRFDataTxnLink(transmit_pin, baudRate);
  sensors.begin();
}

void loop()
{
  delay(50);
  sensors.requestTemperatures();
  int sensorVoltage = analogRead(0);
  // voor 30 psi sensor
  int cmdiepte = 68.95*(sensorVoltage-125)/27.27;
  float outArray[RF_DATA_ARRAY_SIZE];// aan te passen in  DataCoder.h
  
  outArray[0] = cmdiepte;
  outArray[1] = sensors.getTempCByIndex(0);
  
  union RFData outDataSeq;
  EncodeRFData(outArray, outDataSeq); 
  TransmitRFData(outDataSeq);  
  digitalWrite(led_pin, HIGH);
  delay(100);
  digitalWrite(led_pin,LOW);
  delay(500);
  }
