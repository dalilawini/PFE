#include "Menu.h"

extern Adafruit_SH1106G& getOLED();  // Get reference to global OLED
U8G2_FOR_ADAFRUIT_GFX u8g2_for_adafruit_gfx;

Menu::Menu(const String& name, const unsigned char* icon)
  : Item(name), icon(icon) {
}

void Menu::addItem(Item* item) {
  items.push_back(item);
  item->parentMenu= this;
}
void Menu::clearItems() {
  for (Item* item : items) {
    delete item;
  }
  items.clear();  // now it's safe
}

bool Menu::isMenu() {
  return true;
}

void Menu::next() {
  selectedIndex = (selectedIndex + 1) % items.size();
}

void Menu::previous() {
  selectedIndex = (selectedIndex - 1 + items.size()) % items.size();
}

Item* Menu::getSelectedItem() {
   if (items[selectedIndex]->name == " <-- ") {
    return parentMenu;
  }
  return items[selectedIndex];
}

void Menu::display() {
  int startIndex = 0;
  Adafruit_SH1106G& oled = getOLED();                      // get the oled object reference
  u8g2_for_adafruit_gfx.begin(oled);                       // connect u8g2 procedures to Adafruit GFX
  u8g2_for_adafruit_gfx.setFontMode(1);                    // use u8g2 transparent mode (this is default)
  u8g2_for_adafruit_gfx.setFontDirection(0);               // left to right (this is default)
  u8g2_for_adafruit_gfx.setForegroundColor(SH110X_WHITE);  // apply Adafruit GFX color

  oled.clearDisplay();
  oled.drawRoundRect(0, 27, 128, 20, 32, SH110X_WHITE);
  u8g2_for_adafruit_gfx.setFont(u8g2_font_6x12_tr);  // select u8g2 font from here: https://github.com/olikraus/u8g2/wiki/fntlistall
  u8g2_for_adafruit_gfx.setCursor(0, 8);             // start writing at this position
  u8g2_for_adafruit_gfx.print(" -Menu: " + name + " -");

  for (int i = 0; i < items.size(); i++) {
    Item* item = items[i];
    if (item) {
      Menu* submenu = (Menu*)item;
      if (item->isMenu() && submenu->icon) {
        if (selectedIndex == i) {
          oled.clearDisplay();
          // Example: drawBitmap(x, y, bitmap, w, h, color)
          oled.drawBitmap(48, 0, submenu->icon, 32, 32, SH110X_WHITE);
          u8g2_for_adafruit_gfx.setCursor(32, 50);
          u8g2_for_adafruit_gfx.setFont(u8g2_font_helvR12_tf);  // select u8g2 font from here: https://github.com/olikraus/u8g2/wiki/fntlistall
          u8g2_for_adafruit_gfx.print(submenu->name);
          break;
        }
        // <- draw label only
      } else {

        if (selectedIndex == (i + 1)) {
          startIndex = 23;
        } else if (selectedIndex == (i - 1)) {
          startIndex = 57;
        } else if (selectedIndex == i) {
          startIndex = 40;
        } else {
          continue;
        }
        u8g2_for_adafruit_gfx.setFont(selectedIndex == i ? u8g2_font_helvR10_tf : u8g2_font_helvR08_tf);  // apply Adafruit GFX color
        u8g2_for_adafruit_gfx.setCursor(30, startIndex);                                                  // start writing at this position
        u8g2_for_adafruit_gfx.print(item->name);
      }
    }
  }
  oled.display();
}
