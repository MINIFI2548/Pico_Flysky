#include "Pico_Flysky.h"
#include "RPi_Pico_TimerInterrupt.h"

#ifdef BULITIN_LED 
#else 
  #define BULITIN_LED 25
#endif

#define UPDATE_TUME 3 

Pico_Flysky flysky;

RPI_PICO_Timer Timer0(0);
RPI_PICO_Timer Timer1(1);

void setup() {
  Serial.begin(115200); // Debugging
  Serial.println("IBus started");
  Serial1.begin(115200);
  flysky.begin(Serial1);

  pinMode(BULITIN_LED, OUTPUT);
  digitalWriteFast(BULITIN_LED, HIGH);

  Timer0.attachInterruptInterval(UPDATE_TUME * 1000, updateReceiver);
  Timer1.attachInterruptInterval(1000 * 1000, snedSignle);
}
int i = 0;
long t = millis();
void loop() {
 }

 bool updateReceiver(struct repeating_timer *t){
    (void) t;
    flysky.update();
    return true;
 }

 bool snedSignle(struct repeating_timer *t){
    (void) t;
    for (byte i = 0; i<10; i++){
      int value = flysky.readChannel(i, -100, 100);
      Serial.print("CH ");
      Serial.print(i);
      Serial.print(" : ");
      Serial.println(value);
    }
    Serial.println();
    return true;
 }