
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
String esp1_mac = "E4:65:B8:1E:E0:A2";
uint8_t address[6]  = {0x08, 0xA6, 0xF7, 0xA1, 0x6F, 0x0A};//Write Drone side MAC address in HEX
bool connect;

void connected();

void setup() {
  connect = false;
  Serial.begin(115200);
  SerialBT.begin("ESP32_2", true); 
  Serial.println("The device started, now you can pair it with bluetooth!");
  
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
