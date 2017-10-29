// timer_100ms_meten_15minuten_slapen_P_MOSFET
#include <LowPower.h>
const int transistorpin = 9; // pin 9 aangesloten op MOSFET

void setup() {
   pinMode(transistorpin, OUTPUT);
}
 
void loop() {
digitalWrite(transistorpin, LOW);
delay(100); // pin 9 blijft 0,1 s LAAG voor meting (ivm P-MOSFET)
digitalWrite(transistorpin, HIGH);
   for (int i = 0; i < 209; i++)
   LowPower.powerDown(SLEEP_4S, ADC_OFF, BOD_OFF); // pin 9 blijft 15 min hoog (correctie voor tijdafwijking)
}
