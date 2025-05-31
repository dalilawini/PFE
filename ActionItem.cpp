#include "ActionItem.h"

extern Adafruit_SH1106G& getOLED();  // Get reference to global OLED

ActionItem::ActionItem(const String& name)
  : Item(name) {
}

void ActionItem::onClick() {
  items[selectedIndex]->onClick();
  Serial.print(name + " : parent class clicked");
}

void ActionItem::addItem(Component* comp) {
  items.push_back(comp);
}
void ActionItem::clearItems() {
  auto it = items.begin();
  while (it != items.end()) {
    if ((*it)->isErased) {
      delete *it;
      it = items.erase(it);  // erase returns the next valid iterator
    } else {
      ++it;
    }
  }
}


void ActionItem::next() {
  selectedIndex = (selectedIndex + 1) % items.size();
}

void ActionItem::previous() {
  selectedIndex = (selectedIndex - 1 + items.size()) % items.size();
}
Item* ActionItem::getSelectedItem() {
  if (items[selectedIndex]->name == " <-- ") {
    return parentMenu;
  }
  return this;
}

void ActionItem::display() {
  Adafruit_SH1106G& oled = getOLED();                      // get the oled object reference
  u8g2_for_adafruit_gfx.begin(oled);                       // connect u8g2 procedures to Adafruit GFX
  u8g2_for_adafruit_gfx.setFontMode(1);                    // use u8g2 transparent mode (this is default)
  u8g2_for_adafruit_gfx.setFontDirection(0);               // left to right (this is default)
  u8g2_for_adafruit_gfx.setForegroundColor(SH110X_WHITE);  // apply Adafruit GFX color
  oled.clearDisplay();
  u8g2_for_adafruit_gfx.setFont(u8g2_font_6x12_tr);  // select u8g2 font from here: https://github.com/olikraus/u8g2/wiki/fntlistall
  u8g2_for_adafruit_gfx.setCursor(0, 8);             // start writing at this position
  u8g2_for_adafruit_gfx.print(" -Menu: " + name + " -");
  u8g2_for_adafruit_gfx.setCursor(0, 20);
  int x = 10;
  int y = 20;
  int i = selectedIndex > 4 ? selectedIndex - 4 : 0;
  for (i; i < items.size(); i++) {
    u8g2_for_adafruit_gfx.setCursor(0, y);
    u8g2_for_adafruit_gfx.print(selectedIndex == i ? "* " : "  ");
    items[i]->draw(u8g2_for_adafruit_gfx, oled, x, y);  // start writing at this position

    // u8g2_for_adafruit_gfx.setFont(selectedIndex == i ? u8g2_font_helvR10_tf : u8g2_font_helvR08_tf);  // apply Adafruit GFX color
    //u8g2_for_adafruit_gfx.println(items[i]);
  }

  oled.display();
}