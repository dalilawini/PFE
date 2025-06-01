#include "MenuManager.h"

extern Adafruit_SH1106G& getOLED();  // Get reference to global OLED

MenuManager::MenuManager()
  : Menu("root") {
}


void MenuManager::begin(ESP32Encoder encoder, int ok_Switch) {
  this->encoder = encoder;
  this->ok_Switch = ok_Switch;
  
  home = new Home(this);
  currentMenu=home;
  espnow = new Menu("ESP-NOW", ESPNOW);
  espnow->addItem(new Menu(" <-- "));
  addItem(espnow);
}

void MenuManager::run() {
  int encoderSteps = encoder.getCount() / 2;
  currentMenu->display();

  if (encoderSteps != newPosition) {
    if (encoderSteps > newPosition) {
      currentMenu->next();
    } else {
      currentMenu->previous();
    }
    newPosition = encoderSteps;
  }

  if (!digitalRead(ok_Switch)) {
    currentMenu->onClick();
    if (currentMenu->isMenu()) {
      currentMenu = (Menu*)(currentMenu->getSelectedItem());
    } else {
      currentMenu = (ActionItem*)(currentMenu->getSelectedItem());
    }
    delay(250);
  }
}

void MenuManager::initServer() {
  serveur = new Menu("Server", SERVER);
  serveur->addItem(new Menu(" <-- "));
  addItem(serveur);
}

void MenuManager::initWifi() {

  Button* wifiButton = new Button(
    "WiFi", [this](bool selected) {
      this->onWiFiClick(selected);
    },
    false);
  Avaible_networks = new ActionItem("Avaible networks");
  Avaible_networks->addItem(wifiButton);

  ActionItem* Current_network = new ActionItem("Current network");
  Current_network->addItem(new Label(" <-- ",""));
  
  wifi = new Menu("Wifi", WIFI);
  wifi->addItem(Current_network);
  wifi->addItem(Avaible_networks);
  wifi->addItem(new Menu(" <-- "));
  addItem(wifi);
}
void MenuManager::initSettings() {
  settings = new Menu("Settings", SETTINGS);
  settings->addItem(new Menu(" <-- "));
  addItem(settings);
}
void MenuManager::espNowUpdate(std::vector<EspNow*> devices) {
  espnow->clearItems();

  for (int i = 0; i < devices.size(); i++) {
    EspNow* dev = devices[i];
    if(dev!= nullptr){
    ActionItem* Device = new ActionItem(dev->getName());
    Device->addItem(new Label("charge", dev->getCharge() + "%"));
    Device->addItem(new Label("Status", dev->getStatus()));
    Device->addItem(new Label("ID", dev->getID()));
    Device->addItem(new Label("Mac", dev->getMAC()));
    Device->addItem(new Label(" <-- ",""));
    espnow->addItem(Device);
    if(dev->getName()=="ClimaTrack"){
      home->setID_T_H(dev->getID());
      Serial.println(dev->getID());
    }
    }
  }

  espnow->addItem(new Menu(" <-- "));
}

void MenuManager::onWiFiClick(bool select) {
  if (select) {
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    int n = WiFi.scanNetworks();
    if (n == 0) {
      Avaible_networks->addItem(new Label("no networks found", ""));
    } else {
      for (int i = 0; i < n; ++i) {
        // Print SSID and RSSI for each network found
        Serial.println(WiFi.SSID(i));
        Serial.println(WiFi.RSSI(i));
        Avaible_networks->addItem(new Label(WiFi.SSID(i), String(WiFi.RSSI(i))));
      }
      Avaible_networks->addItem(new Label(" <-- ",""));
    }
  } else {
    Avaible_networks->clearItems();
  }
}