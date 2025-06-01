/**************************************************************************/
/*!
    @file     readntag203.pde
    @author   KTOWN (Adafruit Industries)
    @license  BSD (see license.txt)

    This example will wait for any NTAG203 or NTAG213 card or tag,
    and will attempt to read from it.

    This is an example sketch for the Adafruit PN532 NFC/RFID breakout boards
    This library works with the Adafruit NFC breakout
      ----> https://www.adafruit.com/products/364

    Check out the links above for our tutorials and wiring diagrams
    These chips use SPI or I2C to communicate.

    Adafruit invests time and resources providing this open source code,
    please support Adafruit and open-source hardware by purchasing
    products from Adafruit!
*/
/**************************************************************************/
#ifdef ESP32
#pragma message(THIS Code IS FOR ESP8266 ONLY !)
#error Select ESP8266 board.
#endif

#include "DHTesp.h"
#include <ESP8266WiFi.h>
extern "C" {
#include <espnow.h>
}

typedef struct Data_EspNow {
  char name[32];
  char status[32];
  char charge[32];
  char ID[32];
} Data_EspNow;

Data_EspNow myData;
DHTesp dht;
float humidity = dht.getHumidity();
float temperature = dht.getTemperature();


uint8_t receiverMac[] = { 0x0C, 0xB8, 0x15, 0xF8, 0x83, 0x04 };  // Replace with actual MAC

void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("Send Status: ");
  Serial.println(sendStatus == 0 ? "Success" : "Fail");
}

void setup(void) {
  Serial.begin(115200);
  while (!Serial) delay(10);    // for Leonardo/Micro/Zero
  dht.setup(4, DHTesp::DHT22);  // Connect DHT sensor to GPIO 17

  Serial.println("Hello!");



  WiFi.mode(WIFI_STA);

  if (esp_now_init() != 0) {
    Serial.println("ESP-NOW init failed");
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);
  esp_now_add_peer(receiverMac, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);

  strcpy(myData.name, "ClimaTrack");
  strcpy(myData.status, "Active");
  strcpy(myData.charge, "35");
      pinMode(16,OUTPUT);
        pinMode(0,INPUT);
}
    bool state=false;

void loop(void) {
 // if (dht.getHumidity() != humidity || dht.getTemperature() != temperature) {
   if(!digitalRead(0))
   { 
    digitalWrite(16,0);
    humidity = dht.getHumidity();
    temperature = dht.getTemperature();
    Serial.print(humidity, 1);
    Serial.print("\t\t");
    Serial.print(temperature, 1);
    Serial.print("\t\t");
    String data=String(temperature, 1) + "," + String(humidity, 1);
    strcpy(myData.ID,data.c_str());
    esp_now_send(receiverMac, (uint8_t *)&myData, sizeof(myData));
    delay(250);
    digitalWrite(16,1);

  }

}