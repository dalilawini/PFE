#ifndef ITEM_H
#define ITEM_H
#include <Arduino.h>
#include "BitMap.h"

class Item {
protected:
public:
  String name;
  Item(const String& itemName)
    : name(itemName) {}  // Parameterized constructor

  virtual ~Item() {
  }

  virtual void display() = 0;
  virtual void previous() = 0;
  virtual void next() = 0;
  virtual Item* getSelectedItem() =0;
  virtual bool isMenu(){ return false;}
  virtual void onClick(){}
  Item* parentMenu;


};

#endif
