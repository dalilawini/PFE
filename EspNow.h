#ifndef ESPNOW_H
#define ESPNOW_H

#include <Adafruit_SH110X.h>
#include <Fonts/FreeSans9pt7b.h>
#include <U8g2_for_Adafruit_GFX.h>
#include <esp_now.h>

typedef struct Data_EspNow {
  char name[32];
  char status[32];
  char charge[32];
  char ID[32];
} Data_EspNow;

class EspNow {
private:
  U8G2_FOR_ADAFRUIT_GFX u8g2;
  String name;
  String charge;
  String status;
  String ID;
  String MAC="";
 Data_EspNow myData;

public:
  EspNow(const uint8_t* incomingData, const esp_now_recv_info_t* recv_info);
  EspNow(String name, String charge, String status, String ID, String MAC);
  ~EspNow() {}
  void update(const uint8_t* incomingData);
  String getName() {
    return name;
  }
  String getCharge() {
    return charge;
  }
  String getStatus() {
    return status;
  }
  String getID() {
    return ID;
  }
  String getMAC() {
    return MAC;
  }
  
  String toString();
};

#endif