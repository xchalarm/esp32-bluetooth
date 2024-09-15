//This example code is in the Public Domain (or CC0 licensed, at your option.)
//By Evandro Copercini - 2018
//
//This example creates a bridge between Serial and Classical Bluetooth (SPP)
//and also demonstrate that SerialBT have the same functionalities of a normal Serial

#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
// String esp1_mac = "E4:65:B8:1E:E0:A2";
uint8_t address[6]  = {0xE4, 0x65, 0xB8, 0x1E, 0xE0, 0xA2};//Write Drone side MAC address in HEX
bool connect;

void connected();

void setup() {
  connect = false;
  Serial.begin(115200);
  SerialBT.begin("ESP32_2", true); 
  Serial.println("The device started, now you can pair it with bluetooth!");
  // connect = SerialBT.connect(address);
  
  // if(connect) {
  //   Serial.println("Connected Succesfully!");
  // }
  // } else {
  //   while(!SerialBT.connected(10000)) {
  //     Serial.println("Failed to connect. Make sure remote device is available and in range, then restart app."); 
  //   }
  // }
  // // disconnect() may take upto 10 secs max
  // if (SerialBT.disconnect()) {
  //   Serial.println("Disconnected Succesfully!");
  // }
  // // this would reconnect to the name(will use address, if resolved) or address used with connect(name/address).
  // SerialBT.connect();
}

void loop() {
  // String mac = SerialBT.getBtAddressString();
  // Serial.println("MAC Address: " + mac);
  connected();
  SerialBT.println("Charam");
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    Serial.write(SerialBT.read());
  }
  delay(50);
}

void connected(){
  if (SerialBT.connect(address)) {
    if (connect) {
      return;
      // SerialBT.println(3);
    }
    connect = true;
    Serial.println("Connected to the server ESP32!");
  }else {
    Serial.println("Fail to connect to the server ESP32!");
    connect = false;
  }
}