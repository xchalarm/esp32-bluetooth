#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
// String esp2_mac = "E4:65:B8:1D:AD:82"; // MAC address of the server ESP32
bool connect;

void setup() {
  connect = false;
  Serial.begin(115200);
  SerialBT.begin("ESP32_1", true); // Bluetooth device name for the client
  Serial.println("The device started, now trying to connect to the server ESP32!");
}

void loop() {
  // String mac = SerialBT.getBtAddressString();
  // Serial.println("MAC Address: " + mac);

  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    Serial.write(SerialBT.read());
    // }
  }
  if (SerialBT.hasClient()) SerialBT.println("Charam2");
  delay(50);
}