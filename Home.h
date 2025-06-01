#ifndef HOME_H
#define HOME_H

#include <Adafruit_SH110X.h>
#include "Item.h"
#include <Fonts/FreeSans9pt7b.h>
#include <U8g2_for_Adafruit_GFX.h>

class Home : public Item {
private:
  String label;
  Item* parentMenu;
  int selectedIndex = 0;
U8G2_FOR_ADAFRUIT_GFX u8g2_for_adafruit_gfx;
String input="0.0,0.0";


public:
  Home(Item* parentMenu);
  void display() override;
  void previous() override;
  void next() override;
  Item* getSelectedItem() override;
  void setID_T_H(String data){input=data;};



};

#endif