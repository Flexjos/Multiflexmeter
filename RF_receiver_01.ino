// RF_receiver_01

#include <DataCoder.h>
#include <VirtualWire.h>
#include "Wire.h" // For I2C
#include "LCD.h" // For LCD
#include "LiquidCrystal_I2C.h" // http://www.electroschematics.com/12459/arduino-i2c-lcd-backpack-introductory-tutorial/
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7);

const int rx_pin = 11;
const int led_pin = 13;
const int baudRate = 1000;

void setup()
{
  delay(1000);
  Serial.begin(9600);
  pinMode(led_pin,OUTPUT);
  digitalWrite(led_pin,LOW);
  SetupRFDataRxnLink(rx_pin, baudRate);

  // Set off LCD module
  lcd.begin (16,2); // 16 x 2 LCD module
  lcd.setBacklightPin(3,POSITIVE); // BL, BL_POL
  lcd.setBacklight(HIGH);
}

void loop()
{
   lcd.home (); // Set cursor to 0,0
   lcd.print("Multiflexmeter"); // Custom text
   lcd.setCursor (0,1); // Go to home of 2nd line
  
	uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  union RFData inDataSeq;//To store incoming data
  float inArray[RF_DATA_ARRAY_SIZE];
  if(RFLinkDataAvailable(buf, &buflen))
  {
        digitalWrite(led_pin, HIGH);
        for(int i =0; i< buflen; i++)
        {
          inDataSeq.s[i] = buf[i];
        }
        Serial.println();
        digitalWrite(led_pin, LOW);
        DecodeRFData(inArray, inDataSeq);

        //Toon ontvangen afstand en temp op display
        int afstand = inArray[0];
        String ultrasoon = "Afstand: ";
        ultrasoon += afstand;
        lcd.print(ultrasoon);
        delay(2000); 
        ultrasoon = "               ";
        lcd.setCursor (0,1); // ga naar begin van 2e regel
        lcd.print(ultrasoon);
        Serial.print("Afstand:");
        Serial.println(inArray[0]);
 //       delay(1000);
        int temp = inArray[1];
        String temperatuur = "Temperatuur: ";
        temperatuur += temp;
        lcd.setCursor (0,1); // ga naar begin van 2e regel
        lcd.print ("                ");
        lcd.setCursor (0,1); // ga naar begin van 2e regel
        lcd.print(temperatuur);
        delay(2000);
        lcd.setCursor (0,1); // ga naar begin van 2e regel
        lcd.print ("                ");
  }  
}