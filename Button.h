#ifndef BUTTON_H
#define BUTTON_H

#include "Component.h"
#include <functional>

class Button : public Component {
public:
    bool selected=false;
    std::function<void(bool)> onClickCallback;

    Button(String text, std::function<void(bool)> cb, bool isErased=true);
    void draw(U8G2_FOR_ADAFRUIT_GFX &u8g2 ,Adafruit_SH1106G &display ,int &x,int &y) override;
    void onClick() override;
};

#endif