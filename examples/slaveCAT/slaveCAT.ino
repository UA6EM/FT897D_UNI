#include <SomeSerial.h>
#include "uniFT897D.h"

#define SOFTPORT  // если определено используем SofwareSerial
#define SERIAL1   //328PB ONLY

#ifdef  SOFTPORT
SomeSerial RadioPort(2, 3); // RX, TX
uniFT897D Radio(RadioPort);
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
  Radio.Init(4800);
}

void loop() {
  
  ftFreq = Radio.GetFrequency();
  Serial.print("Freq = ");
  Serial.println(ftFreq);
  
  TTX_Status tx_status = Radio.ReadTXStatus();
  Serial.print(" Power  = ");
  Serial.println(tx_status.PowerValue);
  Serial.print(" Split    ");
  Serial.println(tx_status.Split);
  Serial.print(" SWR    = ");
  Serial.println(tx_status.SWR);
  Serial.print(" PTT    = ");
  Serial.println(tx_status.PTTis);
  Serial.println();
  
  TRX_Status rx_status = Radio.ReadRXStatus();
  Serial.print(" S-Metr   = ");
  Serial.println(rx_status.SMValue);
  Serial.print(" DISCRIM  = ");
  Serial.println(rx_status.Discr);
  Serial.print(" DCS/CTCSS = ");
  Serial.println(rx_status.Code);
  Serial.print(" AF/SQL    = ");
  Serial.println(rx_status.NR);
  Serial.println(); 

  TOperatingMode ismode = Radio.GetOperatingMode();
  
  delay(3000);
}
