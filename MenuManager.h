#ifndef MENUMANAGRER_H
#define MENUMANAGRER_H

#include <Adafruit_SH110X.h>
#include <Fonts/FreeSans9pt7b.h>
#include <U8g2_for_Adafruit_GFX.h>
#include "Menu.h"
#include "ActionItem.h"
#include "Home.h"
#include "Label.h"
#include "Button.h"
#include <functional>
#include <ESP32Encoder.h>  // https://github.com/madhephaestus/ESP32Encoder.git
#include "WiFi.h"
#include "EspNow.h"


class MenuManager : public Menu {
private:
  U8G2_FOR_ADAFRUIT_GFX u8g2;
  Menu* homePage;
  Menu* serveur;
  Menu* wifi;
  Menu* settings;
  Menu* espnow;
  Item* currentMenu;
  Home* home;
  ActionItem* Avaible_networks;
  ESP32Encoder encoder;
  long newPosition = 0;
  int ok_Switch;
  void onWiFiClick(bool select);

public:
  MenuManager();
  ~MenuManager() {}
  void begin(ESP32Encoder encoder, int Ok_Switch);
  void run();
  void initServer();
  void initWifi();
  void initSettings();
  void espNowUpdate(std::vector<EspNow*> devices);
};

#endif