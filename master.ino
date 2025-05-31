#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <Wire.h>
#include <ESP32Encoder.h>  // https://github.com/madhephaestus/ESP32Encoder.git
#include "MenuManager.h"
#include "WiFi.h"
#include "EspNow.h"
#include <esp_now.h>
#include "esp_wifi.h"
#include "FireBaseServer.h"

#define WIFI_SSID "MedAli"
#define WIFI_PASSWORD "1234567891"
enum Mode { WIFI_,
            ESPNOW_ };
Mode currentMode;

#define CLK 4         // CLK ENCODER
#define DT 5          // DT ENCODER
#define Ok_Switch 15  // DT ENCODER
ESP32Encoder encoder;

// OLED setup
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define I2C_ADDRESS 0x3C
Adafruit_SH1106G oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Make it visible to other files
Adafruit_SH1106G& getOLED() {
  return oled;
}

MenuManager menuManager;
std::vector<EspNow*> devices;
FireBaseServer fireBaseServer;
volatile bool shouldSwitchToWiFi = false;
String newMAC = "";

void OnDataRecv(const esp_now_recv_info_t* recv_info, const uint8_t* data, int data_len) {
  Serial.println("Data received via ESP-NOW");
  EspNow* device = new EspNow(data, recv_info);
  bool exists = false;
  newMAC = device->getMAC();

  for (EspNow* dev : devices) {
    if (dev->getMAC() == newMAC) {
      dev->update(data);
      Serial.println("EspNow:(update) " + dev->toString());
      exists = true;
      break;
    }
  }
  if (!exists) {
    Serial.println("EspNow: (create) " + device->toString());
    devices.push_back(device);
  } else {
    delete device;
  }
  menuManager.espNowUpdate(devices);
  shouldSwitchToWiFi = true;
}

void setup() {
  Serial.println("void setup begin");

  Serial.begin(115200);
  // Initialize OLED
  if (!oled.begin(I2C_ADDRESS, true)) {
    Serial.println("OLED failed to start");
    while (1)
      ;
  }
  oled.clearDisplay();
  oled.display();

  encoder.attachHalfQuad(DT, CLK);
  pinMode(Ok_Switch, INPUT_PULLUP);
  encoder.setCount(0);

  // startESPNOW();

  menuManager.begin(encoder, Ok_Switch);
  menuManager.initServer();
  menuManager.initWifi();
  menuManager.initSettings();
  //switchMode(WIFI_);
  switchMode(ESPNOW_);

  Serial.println("void setup end");


  //----------------------------------------------------------
}

void loop() {
  menuManager.run();
  if (shouldSwitchToWiFi) {
    switchMode(WIFI_);
    if (currentMode == WIFI_ && WiFi.status() == WL_CONNECTED) {
      fireBaseServer.begin();
      for (EspNow* dev : devices) {
        if (dev->getName() == "RFID Device") {
          fireBaseServer.setID(dev->getMAC());
          fireBaseServer.update();
        }
      }
      Serial.print("fireBaseServer: " + fireBaseServer.toString());
      delay(500);
    } else {
      Serial.print("fireBaseServer: no internet to connection");
    }

    switchMode(ESPNOW_);

    shouldSwitchToWiFi = false;
  }
}

// ------------------- Switch Mode ------------------------
void switchMode(Mode mode) {
  if (mode == ESPNOW_ && currentMode != ESPNOW_) {

    WiFi.disconnect();  // 1. Disconnect from Wi-Fi
    delay(200);
    WiFi.mode(WIFI_STA);  // 2. Ensure STA mode (important for ESP-NOW)
    delay(200);
    esp_wifi_set_promiscuous(true);
    esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE);
    esp_wifi_set_promiscuous(false);

    if (esp_now_init() != ESP_OK) {
      Serial.println("ESP-NOW Init Failed");
      return;
    }
    esp_now_register_recv_cb(OnDataRecv);
    Serial.println("ESP-NOW end");

    currentMode = ESPNOW_;

  } else if (mode == WIFI_ && currentMode != WIFI_) {
    Serial.println("Switching to Wi-Fi...");
    esp_now_deinit();  // 1. Stop ESP-NOW first
    delay(200);
    WiFi.disconnect();  // 2. Disconnect from any Wi-Fi if needed, keep credentials
    delay(200);
    WiFi.mode(WIFI_STA);  // 3. Set Wi-Fi mode to Station (STA)
    delay(200);
    if (WiFi.SSID() == "") {
      WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    } else {
      WiFi.begin();
    }

    unsigned long start = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - start < 10000) {
      delay(100);
      Serial.print(".");
    }
    Serial.println("");
    Serial.print("WiFi.status:");
    Serial.println(WiFi.status());

    if (WiFi.status() == WL_CONNECTED) {
      Serial.print("Wi-Fi Connected!");
    } else {
      Serial.print("Wi-Fi Connection Failed");
    }
    Serial.println(" to" + WiFi.SSID());

    currentMode = WIFI_;
  }
}
