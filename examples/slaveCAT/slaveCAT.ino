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
    if(tx_status.Split){
    Serial.println("OFF");
    }else{
    Serial.println("ON");}

  Serial.print(" HSWR   = ");
    if(tx_status.SWR){
    Serial.println("YES");
    }else{
    Serial.println("NO");}

  Serial.print(" PTT    = ");
    if(tx_status.PTTis){
    Serial.println("ON");
    }else{
    Serial.println("OFF");}
  
  TRX_Status rx_status = Radio.ReadRXStatus();
  Serial.print(" S-Metr   = ");
  Serial.println(rx_status.SMValue);
  Serial.print(" DISCRIM   = ");
    if(!rx_status.Discr){
    Serial.println("OFF");
    }else{
    Serial.println("ON");}

  Serial.print(" DCS/CTCSS = ");
    if(!rx_status.Code){
    Serial.println("OFF");
    }else{
    Serial.println("ON");}
    
  Serial.print(" AF/SQL    = ");
    if(!rx_status.NR){
    Serial.println("OFF");
    }else{
    Serial.println("ON");}
  Serial.println(); 

  TOperatingMode ismode = Radio.GetOperatingMode();
  
  delay(3000);
}
