#include <SPI.h>
#include <LoRa.h>

//define the pins used by the transceiver module
#define ss 5
#define rst 14
#define dio0 2
#define btn 15
#define PA_OUTPUT_PA_BOOST_PIN 2
#define ON "1ON"
#define OFF "1OFF"
//#define ON "2ON"
//#define OFF "2OFF"

int txpower = 20,counter = 0;
String x,last_x;

void setup() {
  //delay(3000);
  //initialize Serial Monitor
  pinMode(btn,INPUT);
  Serial.begin(115200);
  delay(1000);
  while (!Serial);
  Serial.println("LoRa Sender");
  LoRa.setTxPower(txpower);
  LoRa.setSpreadingFactor(6);
  //LoRa.setSignalBandwidth(250E3);
  //LoRa.setCodingRate4(5);
  //LoRa.setPreambleLength(65535);
  //LoRa.disableCrc();
  //LoRa.disableInvertIQ();
  //setup LoRa transceiver module
  LoRa.setPins(ss, rst, dio0);
 

  //replace the LoRa.begin(---E-) argument with your location's frequency 
  //433E6 for Asia
  //866E6 for Europe
  //915E6 for North America
  while (!LoRa.begin(865402500)) {
    Serial.println(".");
    delay(500);
  }
   // Change sync word (0xF3) to match the receiver
  // The sync word assures you don't get LoRa messages from other LoRa transceivers
  // ranges from 0-0xFF
  LoRa.setSyncWord(0xFF);
  Serial.println("LoRa Initializing OK!");
}

void loop() {
  //Serial.println("Send some data");
  //Serial.println(counter);
 // x = Serial.readString();

 /* if(x.length()<1)
  {
    
  }*/
  //Send LoRa packet to receiver
 // if(x.length()>=1)
 //{
  //Serial.print("Sending the data to gateway = ");

  
    //if(digitalRead(btn)==1)
  /*
  { 
    x = ON;
  }
  if(digitalRead(btn)==0)
  { 
    x = OFF;
  }
*/
 

 // if(last_x!=x)
 // {
   Serial.println(counter); 
   LoRa.beginPacket();
   LoRa.print(counter);
   LoRa.endPacket();
   counter++;
 // }*/
  
  //last_x = x;
 delay(1000);
}
