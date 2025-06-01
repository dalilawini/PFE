#include "Home.h"

extern Adafruit_SH1106G& getOLED();  // Get reference to global OLED

Home::Home(Item* parentMenu)
  : Item("home Page"), parentMenu(parentMenu) {
}


void Home::next() {
}

void Home::previous() {
}

Item* Home::getSelectedItem() {
  return parentMenu;
}

void Home::display() {
  int startIndex = 0;
  Adafruit_SH1106G& oled = getOLED();                      // get the oled object reference
  u8g2_for_adafruit_gfx.begin(oled);                       // connect u8g2 procedures to Adafruit GFX
  u8g2_for_adafruit_gfx.setFontMode(1);                    // use u8g2 transparent mode (this is default)
  u8g2_for_adafruit_gfx.setFontDirection(0);               // left to right (this is default)
  u8g2_for_adafruit_gfx.setForegroundColor(SH110X_WHITE);  // apply Adafruit GFX color

  oled.clearDisplay();
  oled.drawBitmap(104, 0, HighBattery, 24, 8, 1);
  oled.drawBitmap(90, 0, wifiicon, 12, 12, 1);

  // oled.drawRoundRect(0, 27, 128, 20, 32, SH110X_WHITE);
  u8g2_for_adafruit_gfx.setFont(u8g2_font_6x12_tr);  // select u8g2 font from here: https://github.com/olikraus/u8g2/wiki/fntlistall
  u8g2_for_adafruit_gfx.setCursor(0, 8);             // start writing at this position
  u8g2_for_adafruit_gfx.print("home page");

  int commaIndex = input.indexOf(',');
  String temp1 = input.substring(0, commaIndex);
  String temp2 = input.substring(commaIndex + 1);

  float value1 = temp1.toFloat();
  float value2 = temp2.toFloat();
  u8g2_for_adafruit_gfx.setFont(u8g2_font_helvB14_tr);  // select u8g2 font from here: https://github.com/olikraus/u8g2/wiki/fntlistall
  u8g2_for_adafruit_gfx.setCursor(0, 30);            // start writing at this position
  u8g2_for_adafruit_gfx.print(value1);
  u8g2_for_adafruit_gfx.print(" C");
  u8g2_for_adafruit_gfx.setCursor(40, 50);  // start writing at this position
  u8g2_for_adafruit_gfx.print(value2);
  u8g2_for_adafruit_gfx.print(" %");



  oled.display();
}
