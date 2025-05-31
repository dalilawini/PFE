#include "EspNow.h"

extern Adafruit_SH1106G& getOLED();  // Get reference to global OLED
EspNow::EspNow(const uint8_t* incomingData, const esp_now_recv_info_t* recv_info) {

  memcpy(&myData, incomingData, sizeof(myData));
  this->name = String(myData.name);
  this->status = String(myData.status);
  this->charge = String(myData.charge);
  this->ID = String(myData.ID);

  if (recv_info != NULL) {
    char macStr[18];
    snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X",
             recv_info->src_addr[0], recv_info->src_addr[1], recv_info->src_addr[2],
             recv_info->src_addr[3], recv_info->src_addr[4], recv_info->src_addr[5]);
    this->MAC = String(macStr);
  }
}

void  EspNow::update(const uint8_t* incomingData){
  memcpy(&myData, incomingData, sizeof(myData));
  this->name = String(myData.name);
  this->status = String(myData.status);
  this->charge = String(myData.charge);
  this->ID = String(myData.ID);
}

String EspNow::toString(){
  return  ("name:"+name+",charge: " +charge+",status:"+ status+",ID:"+ ID+",MAC:"+ MAC);
}
EspNow::EspNow(String name, String charge, String status, String ID, String MAC)
  : name(name), charge(charge), status(status), ID(ID), MAC(MAC) {}
