// timer_01
#include <LowPower.h>
const int transistorpin = 9; // pin 9 aangesloten op MOSFET

void setup() {
   pinMode(transistorpin, OUTPUT);
}
 
void loop() {
digitalWrite(transistorpin, HIGH);
LowPower.powerDown(SLEEP_4S, ADC_OFF, BOD_OFF); // pin 9 blijft 4 s hoog voor meting
digitalWrite(transistorpin, LOW);
     for (int i = 0; i < 103; i++)
     LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); // pin 9 blijft 15 min laag (correctie voor tijdafwijking)
}
