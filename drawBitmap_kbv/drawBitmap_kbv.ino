#include "MCUFRIEND_kbv.h"
#include "bitmap_mono.h"
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define GREY    0x8410
#define ORANGE  0xE880
int c = 0;
int color = 0;
int x = 0;
int y = 0;
int w = 320;
int h = 240;
int eyex = 95;
int eyey = 60;
int eyew = 122;
int eyeh = 33;
MCUFRIEND_kbv tft;
void setup()
{
  Serial.begin(9600);
  uint16_t ID = tft.readID();
  tft.begin(ID);
  tft.setRotation(1);
  tft.fillScreen(BLACK);
  eye(moslift, BLUE, x, y, w, h);
  tone(13, 200, 1000);
}
void eye(const uint8_t eyetype[], uint16_t COL, int x, int y, int w, int h)
{
  tft.drawBitmap(x, y, eyetype, w, h, COL);
}
void loop(void)
{
  if (Serial.available()) {
    c = Serial.read();
    if (c == '2') {
    tone(13, 200, 700);
    delay(1000);
    tone(13, 200, 700);
    delay(1000);
    tone(13, 200, 700);
  }
    if ((color != 0) && (c == '0')) {
      color = 0;
      eye(moslift, BLUE, x, y, w, h);
      eye(eyeblack, BLACK, eyex, eyey, eyew, eyeh);
      eye(eyeleft, BLUE, eyex, eyey, eyew, eyeh);
    }
    else if ((color != 1) && (c == '1')) {
      color = 1;
      eye(moslift, RED, x, y, w, h);
      eye(eyeblack, BLACK, eyex, eyey, eyew, eyeh);
      eye(messageup, RED, eyex, eyey, eyew, eyeh);
      tone(13, 200, 1000);
    }
  }
  if (color == 0) {
    eye(eyeblack, BLACK, eyex, eyey, eyew, eyeh);
    eye(eyeleft, BLUE, eyex, eyey, eyew, eyeh);
    delay(1000);
    eye(eyeblack, BLACK, eyex, eyey, eyew, eyeh);
    eye(eyeright, BLUE, eyex, eyey, eyew, eyeh);
    delay(1000);
  }
  else if (color == 1) {
    eye(eyeblack, BLACK, eyex, eyey, eyew, eyeh);
    eye(messagedown, RED, eyex, eyey, eyew, eyeh);
    delay(100);
    eye(eyeblack, BLACK, eyex, eyey, eyew, eyeh);
    eye(messageup, RED, eyex, eyey, eyew, eyeh);
    delay(100);
  }
}
