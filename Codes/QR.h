#include <JPEGDecoder.h>

void jpegRender(int xpos, int ypos) {
  uint16_t *pImg;
  uint16_t mcu_w = JpegDec.MCUWidth;
  uint16_t mcu_h = JpegDec.MCUHeight;
  uint32_t max_x = JpegDec.width;
  uint32_t max_y = JpegDec.height;

  bool swapBytes = tft.getSwapBytes();
  tft.setSwapBytes(true);
  
  uint32_t min_w = jpg_min(mcu_w, max_x % mcu_w);
  uint32_t min_h = jpg_min(mcu_h, max_y % mcu_h);

  uint32_t win_w = mcu_w;
  uint32_t win_h = mcu_h;


  uint32_t drawTime = millis();

  max_x += xpos;
  max_y += ypos;

  while (JpegDec.read()) { 
    pImg = JpegDec.pImage ; 

    int mcu_x = JpegDec.MCUx * mcu_w + xpos;
    int mcu_y = JpegDec.MCUy * mcu_h + ypos;

    if (mcu_x + mcu_w <= max_x) win_w = mcu_w;
    else win_w = min_w;

    if (mcu_y + mcu_h <= max_y) win_h = mcu_h;
    else win_h = min_h;

    if (win_w != mcu_w)
    {
      uint16_t *cImg;
      int p = 0;
      cImg = pImg + win_w;
      for (int h = 1; h < win_h; h++)
      {
        p += mcu_w;
        for (int w = 0; w < win_w; w++)
        {
          *cImg = *(pImg + w + p);
          cImg++;
        }
      }
    }
    uint32_t mcu_pixels = win_w * win_h;

    if (( mcu_x + win_w ) <= tft.width() && ( mcu_y + win_h ) <= tft.height())
      tft.pushImage(mcu_x, mcu_y, win_w, win_h, pImg);
    else if ( (mcu_y + win_h) >= tft.height())
      JpegDec.abort();
  }

  tft.setSwapBytes(swapBytes);
}

void drawSdJpeg(const char *filename, int xpos, int ypos) {
  File jpegFile = SD.open( filename, FILE_READ); 
 
  if ( !jpegFile ) {
    Serial.print("ERROR: File \""); Serial.print(filename); Serial.println ("\" not found!");
    return;
  }

  Serial.println("===========================");
  Serial.print("Drawing file: "); Serial.println(filename);
  Serial.println("===========================");
  bool decoded = JpegDec.decodeSdFile(jpegFile);
  if (decoded) {
  Serial.println("");
  jpegRender(xpos, ypos);
  }
  else {
    tft.fillScreen(TFT_RED);
    tft.setTextColor(TFT_BLACK);
    tft.setTextSize(2);
    tft.setCursor(20, 140);
    tft.print("JPG ERROR");
    Serial.println("Stream timeout, resuming...");
    Serial.println("Jpeg file format not supported!");
  }
}
