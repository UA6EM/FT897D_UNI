#include "SomeSerial.h"
#include "uniFT897D.h"

#define SOFTPORT  // если определено используем SofwareSerial
#define SERIAL1   //328PB ONLY

#ifdef  SOFTPORT
SomeSerial RadioPort(2, 3); // RX, TX
uniFT897D radio(RadioPort);
#else
  #ifdef SERIAL1
  SomeSerial RadioPort(&Serial1);
  #else
  SomeSerial RadioPort(&Serial);
  #endif
#endif

float ftFreq;

void setup() {
  Serial.begin(115200);
  delay(250);
  Serial.println("Start...");
  radio.Init(4800);
}

void loop() {
  
  ftFreq = radio.GetFrequency();
  Serial.print("Freq = ");
  Serial.println(ftFreq);
  
// ModeToSerial();

  delay(3000);
}
