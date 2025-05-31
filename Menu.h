#ifndef MENU_H
#define MENU_H

#include <Adafruit_SH110X.h>
#include "Item.h"
#include <Fonts/FreeSans9pt7b.h>
#include <U8g2_for_Adafruit_GFX.h>

class Menu : public Item {
private:
  const unsigned char* icon;
  std::vector<Item*> items;
  String label;
  int selectedIndex = 0;



public:
  Menu(const String& name, const unsigned char* icon = nullptr);
  void display() override;
  void addItem(Item* item);
  void previous() override;
  void next() override;
  bool isMenu() override;
  Item* getSelectedItem() override;
  void clearItems();
};

#endif