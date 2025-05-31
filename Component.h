#ifndef COMPONENT_H
#define COMPONENT_H

#include <U8g2_for_Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

class Component {
public:
   String name;
    bool visible = true;
    bool isErased; 

    Component(String name, bool isErased);
    virtual ~Component(){}
    virtual void draw(U8G2_FOR_ADAFRUIT_GFX &u8g2 ,Adafruit_SH1106G &display,int &x,int &y ) = 0;
    virtual void onClick();
};

#endif