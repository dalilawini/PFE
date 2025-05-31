#include "Label.h"

Label::Label( String text,String data, bool isErased)
    : Component(text, isErased), data(data) {}

void Label::draw(U8G2_FOR_ADAFRUIT_GFX &u8g2 ,Adafruit_SH1106G &display ,int &x,int &y) {
    if (!visible) return;
   // display.setTextColor(SH110X_WHITE);
     u8g2.setCursor(x,y);

    u8g2.print(name+":"+data);
    y+=10;

}
