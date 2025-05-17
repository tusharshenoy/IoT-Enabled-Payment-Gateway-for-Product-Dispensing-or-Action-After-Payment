#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

int productQuantities[4] = {0, 0, 0, 0};
int selectedProductIndex = -1;

const int productPrices[] = {10, 10, 20, 20};

void drawHeader() {
  tft.fillScreen(TFT_BLACK);
  tft.fillRect(0, 0, 240, 40, TFT_SKYBLUE);
  tft.setTextColor(TFT_BLACK, TFT_GOLD);
  tft.setTextSize(2);
  tft.setCursor(20, 10);
  tft.print("NMAMIT SmartVend");
}

void drawTable() {

  tft.fillRect(0, 40, 240, 40, TFT_GOLD);
  tft.setTextColor(TFT_BLACK, TFT_SKYBLUE);
  tft.setTextSize(2);
  tft.setCursor(10, 50);
  tft.print("Products");
  tft.setCursor(130, 50);
  tft.print("Price");
  tft.setCursor(200, 50);
  tft.print("Qty");

  for (int i = 0; i < 4; i++) {
    int y = 70 + i * 30;
    uint16_t bgColor = (i % 2 == 0) ? TFT_SKYBLUE : TFT_GOLD;
    if (i == selectedProductIndex) {
      bgColor = TFT_MAGENTA;
    }
    tft.fillRect(0, y, 240, 30, bgColor);
    tft.setTextColor(TFT_BLACK, bgColor);
    tft.setCursor(10, y + 10);
    tft.print("Product ");
    tft.print(i + 1);
    tft.setCursor(140, y + 10);
    tft.print(productPrices[i]);  // Display the price
    tft.setCursor(210, y + 10);
    tft.print(productQuantities[i]);  // Display the quantity
  }
}

void drawButton(int x, int y, int w, int h, const char *label, uint16_t color, bool active = false) {
  uint16_t fillColor = active ? color : TFT_DARKGREY;
  uint16_t textColor = active ? TFT_WHITE : TFT_LIGHTGREY;
  
  tft.fillRect(x, y, w, h, fillColor);
  tft.drawRect(x, y, w, h, TFT_WHITE);
  tft.setTextColor(textColor);
  tft.setTextSize(2);
  int16_t x1, y1;
  uint16_t w1, h1;

  w1 = strlen(label) * 12; 
  h1 = 16; 
  tft.setCursor(x + (w - w1) / 2, y + (h - h1) / 2);
  tft.print(label);
}

void drawButtons(int activeButton = -1) {
  drawButton(10, 220, 100, 40, "Increase", TFT_BLUE, activeButton == 4);
  drawButton(130, 220, 100, 40, "Decrease", TFT_RED, activeButton == 5);
  drawButton(10, 270, 100, 40, "Proceed", TFT_GREEN, activeButton == 6);
  drawButton(130, 270, 100, 40, "Cancel", TFT_ORANGE, activeButton == 7);
}