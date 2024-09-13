//-----------------------------------------------------------
//ESP-NOW: Transmitter
//Ref: Random Nerd Tutorials https://randomnerdtutorials.com
//-----------------------------------------------------------
#include <esp_now.h>
#include <WiFi.h>
//-------------------------------------------------------------------------------------
uint8_t RxMACaddress[] = {0x7C, 0x9E, 0xBD, 0xF5, 0xBE, 0x30};
//-------------------------------------------------------------------------------------
typedef struct TxStruct
{
  int potVal;
}TxStruct;
TxStruct sentData;
//-------------------------------------------------------------------------------------
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) //callback function
{
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
//======================================================================================
void setup()
{
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  //------------------------------------------------------------------------------------
  if(esp_now_init() != ESP_OK)
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  //-------------------------------------------------------------------------------------
  esp_now_register_send_cb(OnDataSent);
  //-------------------------------------------------------------------------------------
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, RxMACaddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  //-------------------------------------------------------------------------------------
  if(esp_now_add_peer(&peerInfo) != ESP_OK)
  {
    Serial.println("Failed to add peer");
    return;
  }
}
//======================================================================================
void loop()
{
  sentData.potVal = analogRead(A0);
  //-------------------------------------------------------------------------------------
  esp_err_t result = esp_now_send(RxMACaddress, (uint8_t *) &sentData, sizeof(sentData));
  //-------------------------------------------------------------------------------------
  if (result == ESP_OK) Serial.println("Sent with success");
  else Serial.println("Error sending the data");
  //-------------------------------------------------------------------------------------
  delay(500);
}

Receiver Sketch

//-----------------------------------------------------------
//ESP-NOW: Receiver
//Ref: Random Nerd Tutorials https://randomnerdtutorials.com
//-----------------------------------------------------------
#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//-------------------------------------------------------------------------------------
Adafruit_SSD1306 display(128, 64, &Wire, -1);
//-------------------------------------------------------------------------------------
typedef struct RxStruct
{
  int potVal;
}RxStruct;
RxStruct receivedData;
//-------------------------------------------------------------------------------------
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len)
{
  memcpy(&receivedData, incomingData, sizeof(receivedData));
}
//======================================================================================
void setup()
{
  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) 
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  //-------------------------------------------------------------------------------------
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK)
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_recv_cb(OnDataRecv);
}
//======================================================================================
void loop()
{
  display.setTextColor(WHITE); display.clearDisplay();
  display.setTextSize(2); display.setCursor(20,0); display.print("ESP-NOW");
  display.setCursor(10,18); display.print("POT Value");
  display.setTextSize(3); display.setCursor(25,42); display.print(receivedData.potVal);
  display.display();
}