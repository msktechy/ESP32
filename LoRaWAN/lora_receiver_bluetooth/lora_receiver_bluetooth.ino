#include <SPI.h>
#include <LoRa.h>
#include "BluetoothSerial.h"

BluetoothSerial ESP_BT;

//define the pins used by the transceiver module
#define ss 5
#define rst 14
#define dio0 2

int Node,availableBytes;
byte b;
String LoRaData;
String snr;
String freqErr;
String rssi;


void setup() {
  //initialize Serial Monitor
  Serial.begin(115200);
    ESP_BT.begin("LoRa Range test");
  while (!Serial);
  Serial.println("LoRa Receiver");

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
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print("Received packet '");

    // read packet
    while (LoRa.available()) {
     LoRaData = LoRa.readString();
        Serial.print("LoRa1Data = ");
        Serial.println(LoRaData);
        ESP_BT.print("LoRa1Data = ");
        ESP_BT.println(LoRaData);
  

    // print RSSI of packet
   
    }

    // print RSSI of packet
    Serial.print("RSSI = ");
    rssi = String(LoRa.packetRssi());
    Serial.println(rssi);
    ESP_BT.print("RSSI = ");
    ESP_BT.println(rssi);
    snr = LoRa.packetSnr();
    Serial.print("SNR = ");
    Serial.println(snr);
    ESP_BT.print("SNR = ");
    ESP_BT.println(snr);
    freqErr = LoRa.packetFrequencyError();
    Serial.print("Frequency Error = ");
    Serial.println(freqErr);
    ESP_BT.print("Frequency Error = ");
    ESP_BT.println(freqErr);
    availableBytes = LoRa.available();
    Serial.print("Available Bytes = ");
    Serial.println(availableBytes);
    ESP_BT.print("Available Bytes = ");
    ESP_BT.println(availableBytes);
    b = LoRa.peek();
    Serial.print("Next Byte = ");
    Serial.println(availableBytes);   
    ESP_BT.print("Next Byte = ");
    ESP_BT.println(availableBytes); 
    Serial.println();
    ESP_BT.println();
    ESP_BT.println();    
  }
}
