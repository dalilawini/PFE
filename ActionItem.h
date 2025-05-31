#ifndef ACTIONITEM_H
#define ACTIONITEM_H

#include <Adafruit_SH110X.h>
#include "Item.h"
#include <Fonts/FreeSans9pt7b.h>
#include <U8g2_for_Adafruit_GFX.h>
#include "Component.h"

class ActionItem : public Item {
private:
  //const unsigned char* icon1;
  //const unsigned char* icon2;
  std::vector<Component*> items;

  int selectedIndex = 0;
  U8G2_FOR_ADAFRUIT_GFX u8g2_for_adafruit_gfx;


public:
  //Menu(const String& name, const unsigned char* icon1 = nullptr,const unsigned char* icon2 = nullptr);
  ActionItem(const String& name);
  ~ActionItem(){
      for (Component* item : items) {
        delete item;
    }
  }
  void display() override;
  void addItem(Component* comp);
  void previous() override;
    void onClick() override;
  void next() override;
  Item* getSelectedItem() override;
  bool isA(int x){}
  void clearItems();

};

#endif