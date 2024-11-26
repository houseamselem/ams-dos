/*
 * 
 * 
 */

//
#include "OLEDManager.h"

//
OLEDManager::OLEDManager(Mode mode) : currentMode(mode), u8g2(nullptr) {
    if (mode == MODE_64x32) {
        u8g2 = new U8G2_SSD1306_64X32_1F_F_HW_I2C(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
    } else if (mode == MODE_128x32) {
        u8g2 = new U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
    } else if (mode == MODE_128x64) {
        u8g2 = new U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI(U8G2_R0, /* SCL=*/ 5, /* SDA=*/ 4, /* CS=*/ U8X8_PIN_NONE, /* DC=*/ 2, /* RES=*/ 0);
    }
}

//
void OLEDManager::init() {
    if (u8g2) {
        u8g2->begin();
        u8g2->enableUTF8Print();
        delay(1000);
        u8g2->clearBuffer();
    }
}

//
void OLEDManager::refresh() {
    if (u8g2) {
        u8g2->sendBuffer();
    }
}

//
void OLEDManager::drawBattery(int x, int y, int val) {

  // Implementation for drawBattery similar to the provided ino file.
  // Replace `u8g2` calls with `u8g2->` for the class member.

  //
  int cnt = 1;
  int h = 9;

  //
  switch (val) {
    case 1:
      u8g2->drawBitmap(x, y, cnt, h, battery_l1);
      u8g2->drawBitmap(x + 8, y, cnt, h, battery_r0);
      break;
    case 2:
      u8g2->drawBitmap(x, y, cnt, h, battery_l2);
      u8g2->drawBitmap(x + 8, y, cnt, h, battery_r0);
      break;
    case 3:
      u8g2->drawBitmap(x, y, cnt, h, battery_l2);
      u8g2->drawBitmap(x + 8, y, cnt, h, battery_r1);
      break;
    case 4:
      u8g2->drawBitmap(x, y, cnt, h, battery_l2);
      u8g2->drawBitmap(x + 8, y, cnt, h, battery_r2);
      break;
    default:
      u8g2->drawBitmap(x, y, cnt, h, battery_l0);
      u8g2->drawBitmap(x + 8, y, cnt, h, battery_r0);
      break;
  }

}

//
void OLEDManager::drawHourglass(int x, int y, int val) {
    if (u8g2) {
        u8g2->setFont(u8g2_font_unifont_t_symbols);
        u8g2->drawGlyph(x, y, 0x23f3);
    }  
}

//
void OLEDManager::drawPie(int x, int y, int val) {

  // Implementation for drawPie similar to the provided ino file.
  // Replace `u8g2` calls with `u8g2->` for the class member.

  //
  int cnt = 1;
  int h = 16;

  u8g2->drawBitmap(x, y, cnt, h, circle_l0);
  u8g2->drawBitmap(x + 8, y, cnt, h, circle_r0);

}

//
void OLEDManager::drawWifi(int x, int y, long rssi) {

  // Implementation for drawWifi similar to the provided ino file.
  // Replace `u8g2` calls with `u8g2->` for the class member.

  //
  int val = getRSSIVal(rssi);

  //
  int cnt = 1;
  int h = 9;

  //
  switch (val) {
    case 1:
      u8g2->drawBitmap(x, y, cnt, h, wifi_l1);
      u8g2->drawBitmap(x + 8, y, cnt, h, wifi_r0);
      break;
    case 2:
      u8g2->drawBitmap(x, y, cnt, h, wifi_l2);
      u8g2->drawBitmap(x + 8, y, cnt, h, wifi_r0);
      break;
    case 3:
      u8g2->drawBitmap(x, y, cnt, h, wifi_l2);
      u8g2->drawBitmap(x + 8, y, cnt, h, wifi_r1);
      break;
    case 4:
      u8g2->drawBitmap(x, y, cnt, h, wifi_l2);
      u8g2->drawBitmap(x + 8, y, cnt, h, wifi_r2);
      break;
    default:
      u8g2->drawBitmap(x, y, cnt, h, wifi_l0);
      u8g2->drawBitmap(x + 8, y, cnt, h, wifi_r0);
      break;
  }

}

//
void OLEDManager::textTime(int x, int y, const char* timeStr) {
    if (u8g2) {
        u8g2->setFont(u8g2_font_timR08_tr);
        u8g2->drawStr(x, y, timeStr);
    }
}

//
void OLEDManager::textPrompt() {
    if (!u8g2) return;
    if (currentMode == MODE_64x32) {
        u8g2->setFontMode(0);
        u8g2->setFont(u8g2_font_timR08_tr);
        u8g2->drawStr(0, 10, "AMSLAN");
        u8g2->drawStr(0, 21, "Connecting...");
        u8g2->drawStr(0, 32, "Please wait.");
    } else if (currentMode == MODE_128x32) {
        u8g2->setFontMode(0);
        u8g2->setFont(u8g2_font_timR08_tr);
        u8g2->drawStr(0, 10, "AMSLAN");
        u8g2->drawStr(0, 21, "Connecting...");
        u8g2->drawStr(0, 32, "Please wait.");
    } else if (currentMode == MODE_128x64) {
        u8g2->setFont(u8g2_font_unifont_t_symbols);
        u8g2->drawGlyph(-2, 20, 0x2617);
        u8g2->setFontMode(1);
        u8g2->setFont(u8g2_font_6x10_mr);
        u8g2->drawStr(18, 10, "Advanced Micro");
        u8g2->drawStr(18, 20, "Copyright (C) 2022");
        u8g2->drawStr(0, 30, "AMS650 ATmega328 BIOS");
        u8g2->drawStr(0, 40, "80MHz Processor");
        u8g2->drawStr(0, 50, "Memory Test: 4192KB");
        u8g2->drawStr(0, 60, "F2 to enter setup.");
    }
}

//
void OLEDManager::textTH(int p, float t) {
    if (u8g2) {
        u8g2->setFont(u8g2_font_timR08_tr);
        char pStr[8];
        char tStr[8];
        dtostrf(p, 2, 0, pStr);
        dtostrf(t, 2, 2, tStr);
        u8g2->drawStr(0, 21, "P (Pa):");
        u8g2->drawStr(31, 21, pStr);
        u8g2->drawStr(0, 32, "T (C):");
        u8g2->drawStr(31, 32, tStr);
    }
}

//
int OLEDManager::getRSSIVal(long rssi) {
    if (rssi < -70)
        return 1;
    else if (rssi < -60)
        return 2;
    else if (rssi < -50)
        return 3;
    return 4;
}



//
const uint8_t OLEDManager::battery_l0[] = {
    0xff, // 11111111
    0x80, // 10000000
    0x80, // 10000000
    0x80, // 10000000
    0x80, // 10000000
    0x80, // 10000000
    0x80, // 10000000
    0x80, // 10000000
    0xff  // 11111111
};

//
const uint8_t OLEDManager::battery_l1[] = {
  0xff, // 11111111
  0x80, // 10000000
  0xb0, // 10110000
  0xb0, // 10110000
  0xb0, // 10110000
  0xb0, // 10110000
  0xb0, // 10110000
  0x80, // 10000000
  0xff  // 11111111
};

//
const uint8_t OLEDManager::battery_l2[] = {
  0xff, // 11111111
  0x80, // 10000000
  0xb6, // 10110110
  0xb6, // 10110110
  0xb6, // 10110110
  0xb6, // 10110110
  0xb6, // 10110110
  0x80, // 10000000
  0xff  // 11111111
};

//
const uint8_t OLEDManager::battery_r0[] = {
  0xfe, // 11111110
  0x02, // 00000010
  0x03, // 00000011
  0x03, // 00000011
  0x03, // 00000011
  0x03, // 00000011
  0x03, // 00000011
  0x02, // 00000010
  0xfe  // 11111110
};

//
const uint8_t OLEDManager::battery_r1[] = {
  0xfe, // 11111110
  0x02, // 00000010
  0xc3, // 11000011
  0xc3, // 11000011
  0xc3, // 11000011
  0xc3, // 11000011
  0xc3, // 11000011
  0x02, // 00000010
  0xfe  // 11111110
};

//
const uint8_t OLEDManager::battery_r2[] = {
  0xfe, // 11111110
  0x02, // 00000010
  0xdb, // 11011011
  0xdb, // 11011011
  0xdb, // 11011011
  0xdb, // 11011011
  0xdb, // 11011011
  0x02, // 00000010
  0xfe  // 11111110
};



//
const uint8_t OLEDManager::circle_l0[] = {
  0x07, // 00000111
  0x18, // 00011000
  0x20, // 00100000
  0x40, // 01000000
  0x40, // 01000000
  0x80, // 10000000
  0x80, // 10000000
  0x80, // 10000000
  0x80, // 10000000
  0x80, // 10000000
  0x80, // 10000000
  0x40, // 01000000
  0x40, // 01000000
  0x20, // 00100000
  0x18, // 00011000
  0x07  // 00000111
};

//
const uint8_t OLEDManager::circle_l1[] = {
  0x07, // 00000111
  0x18, // 00011000
  0x20, // 00100000
  0x40, // 01000000
  0x40, // 01000000
  0x80, // 10000000
  0x80, // 10000000
  0x80, // 10000000
  0xff, // 11111111
  0xff, // 11111111
  0xff, // 11111111
  0x7f, // 01111111
  0x7f, // 01111111
  0x3f, // 00111111
  0x1f, // 00011111
  0x07  // 00000111
};

//
const uint8_t OLEDManager::circle_l2[] = {
  0x07, // 00000111
  0x1f, // 00011111
  0x3f, // 00111111
  0x7f, // 01111111
  0x7f, // 01111111
  0xff, // 11111111
  0xff, // 11111111
  0xff, // 11111111
  0xff, // 11111111
  0xff, // 11111111
  0xff, // 11111111
  0x7f, // 01111111
  0x7f, // 01111111
  0x3f, // 00111111
  0x1f, // 00011111
  0x07  // 00000111
};

//
const uint8_t OLEDManager::circle_r0[] = {
  0xe0, // 11100000
  0x18, // 00011000
  0x04, // 00000100
  0x02, // 00000010
  0x02, // 00000010
  0x01, // 00000001
  0x01, // 00000001
  0x01, // 00000001
  0x01, // 00000001
  0x01, // 00000001
  0x01, // 00000001
  0x02, // 00000010
  0x02, // 00000010
  0x04, // 00000100
  0x18, // 00011000
  0xe0  // 11100000
};

//
const uint8_t OLEDManager::circle_r1[] = {
  0xe0, // 11100000
  0xf8, // 11111000
  0xfc, // 11111100
  0xfe, // 11111110
  0xfe, // 11111110
  0xff, // 11111111
  0xff, // 11111111
  0xff, // 11111111
  0x01, // 00000001
  0x01, // 00000001
  0x01, // 00000001
  0x02, // 00000010
  0x02, // 00000010
  0x04, // 00000100
  0x18, // 00011000
  0xe0  // 11100000
};

//
const uint8_t OLEDManager::circle_r2[] = {
  0xe0, // 11100000
  0xf8, // 11111000
  0xfc, // 11111100
  0xfe, // 11111110
  0xfe, // 11111110
  0xff, // 11111111
  0xff, // 11111111
  0xff, // 11111111
  0xff, // 11111111
  0xff, // 11111111
  0xff, // 11111111
  0xfe, // 11111110
  0xfe, // 11111110
  0xfc, // 11111100
  0xf8, // 11111000
  0xe0  // 11100000
};



//
const uint8_t OLEDManager::wifi_l0[] = {
  0x00, // 00000000
  0x00, // 00000000
  0x00, // 00000000
  0x00, // 00000000
  0x07, // 00000111
  0x04, // 00000100
  0x3c, // 00111100
  0x24, // 00100100
  0x3f  // 00111111
};

//
const uint8_t OLEDManager::wifi_l1[] = {
  0x00, // 00000000
  0x00, // 00000000
  0x00, // 00000000
  0x00, // 00000000
  0x07, // 00000111
  0x04, // 00000100
  0x3c, // 00111100
  0x3c, // 00111100
  0x3f  // 00111111
};

//
const uint8_t OLEDManager::wifi_l2[] = {
  0x00, // 00000000
  0x00, // 00000000
  0x00, // 00000000
  0x00, // 00000000
  0x07, // 00000111
  0x07, // 00000111
  0x3f, // 00111111
  0x3f, // 00111111
  0x3f  // 00111111
};

//
const uint8_t OLEDManager::wifi_r0[] = {
  0x1e, // 00011110
  0x12, // 00010010
  0xf2, // 11110010
  0x92, // 10010010
  0x92, // 10010010
  0x92, // 10010010
  0x92, // 10010010
  0x92, // 10010010
  0xfe  // 11111110
};

//
const uint8_t OLEDManager::wifi_r1[] = {
  0x1e, // 00011110
  0x12, // 00010010
  0xf2, // 11110010
  0xf2, // 11110010
  0xf2, // 11110010
  0xf2, // 11110010
  0xf2, // 11110010
  0xf2, // 11110010
  0xfe  // 11111110
};

//
const uint8_t OLEDManager::wifi_r2[] = {
  0x1e, // 00011110
  0x1e, // 00011110
  0xfe, // 11111110
  0xfe, // 11111110
  0xfe, // 11111110
  0xfe, // 11111110
  0xfe, // 11111110
  0xfe, // 11111110
  0xfe  // 11111110
};
