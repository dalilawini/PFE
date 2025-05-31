#ifndef LABEL_H
#define LABEL_H

#include "Component.h"

class Label : public Component {
public:
  String data;
  Label(String text, String data, bool isErased=true);
  void draw(U8G2_FOR_ADAFRUIT_GFX &u8g2 ,Adafruit_SH1106G &display,int &x,int &y) override;
};

#endif