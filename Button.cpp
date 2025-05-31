#include "Button.h"

Button::Button( String text, std::function<void(bool)> cb, bool isErased)
    : Component(text,isErased), onClickCallback(cb) {}

void Button::draw(U8G2_FOR_ADAFRUIT_GFX &u8g2 ,Adafruit_SH1106G &display ,int &x,int &y) {
    if (!visible) return;
  //  display.setTextColor(selected ? SH110X_BLACK : SH110X_WHITE);
  //  if (selected) display.fillRect(x, y, width, height, SH110X_WHITE);

       u8g2.setCursor(x,y);

    u8g2.print(name);
    u8g2.setCursor(x+90,y);
    u8g2.print(selected?"(on)":"(off)");

    y+=11;
}

void Button::onClick() {
    selected = !selected;
    if (onClickCallback) onClickCallback(selected);
}