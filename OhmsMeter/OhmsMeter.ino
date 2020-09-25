#include <Adafruit_GFX.h> // Hardware-specific library
#include <MCUFRIEND_kbv.h>
//#include "utf8_decode.h"
MCUFRIEND_kbv tft;
#define BLACK 0x0000
#define NAVY 0x000F
#define DARKGREEN 0x03E0
#define DARKCYAN 0x03EF
#define MAROON 0x7800
#define PURPLE 0x780F
#define OLIVE 0x7BE0
#define LIGHTGREY 0xC618
#define DARKGREY 0x7BEF
#define BLUE 0x001F
#define GREEN 0x07E0
#define CYAN 0x07FF
#define RED 0xF800
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF
#define ORANGE 0xFD20
#define GREENYELLOW 0xAFE5
#define PINK 0xF81F
int raw = 0;
float Vin = 5;
float Vout = 0;
int R1 = 330;
int R2 = 0;
int old = 1;
void setup()
{

  analogReference(EXTERNAL);
  Serial.begin(9600);
  tft.reset();
  uint16_t identifier = tft.readID();
  Serial.print("ID = 0x");
  Serial.println(identifier, HEX);
  if (identifier == 0xEFEF) identifier = 0x9486;
  tft.begin(identifier);
  tft.setRotation(1);
tone(13, 500, 1000);

}



/* Recode russian fonts from UTF-8 to Windows-1251 */

String utf8rus(String source)
{
  int i, k;
  String target;
  unsigned char n;
  char m[2] = { '0', '\0' };

  k = source.length(); i = 0;

  while (i < k) {
    n = source[i]; i++;

    if (n >= 0xC0) {
      switch (n) {
        case 0xD0: {
            n = source[i]; i++;
            if (n == 0x81) {
              n = 0xA8;
              break;
            }
            if (n >= 0x90 && n <= 0xBF) n = n + 0x30;
            break;
          }
        case 0xD1: {
            n = source[i]; i++;
            if (n == 0x91) {
              n = 0xB8;
              break;
            }
            if (n >= 0x80 && n <= 0x8F) n = n + 0x70;
            break;
          }
      }
    }
    m[0] = n; target = target + String(m);
  }
  return target;
}
int resistance(int R, float vin, float vout) {
  return round(R * (1 / (vin / vout - 1)));
}
int adc() {
  raw = 0;
  for (int i = 0; i < 20; i++) {
    raw += analogRead(A5);
  }
  return raw / 20;
}
void loop()
{
  raw = adc();
  if (raw < 500 && raw > 0) {
    delay(100);
    raw = adc();
    if(raw < 500 && raw > 0){
      tone(13, 500, 200);
      Vout = (raw * Vin) / 1023.0;
      R2 = resistance(R1, Vin, Vout);
      Serial.print("Vout: ");
      Serial.println(Vout);
      Serial.print("R2: ");
      Serial.println(R2);
      tft.fillScreen(DARKGREEN);
      //tft.fillScreen(BLACK);
      //tft.setTextColor(RED);
      // tft.setTextColor(WHITE);
      tft.setTextSize(15);
      tft.setCursor(26, 58);
      tft.println(R2);
      old = 1;
      delay(2000);
    }
  }
  else {
  
    if (old) {
      old = 0;
      tft.fillScreen(ORANGE);
      //  tft.setTextColor(BLACK);
      tft.setTextSize(6);
     // tft.setCursor(35, 40);
     // tft.println("MOSLIFT");
    
      tft.setCursor(90, 90);
      tft.println("TEST");
      tft.setCursor(17, 140);
      tft.println("RESISTOR");
     // tft.setCursor(180, 220);
     // tft.setTextSize(1);
     // tft.println( "designed by MOSLIFT");
     tft.setTextSize(4);
     tft.setTextColor(BLACK);
      tft.setCursor(42, 40);
      tft.println("--[ // ]--");
      tft.setTextSize(1);
      tft.setCursor(250, 220);
       tft.println( "ver.1.2");
    }
  }

  // put your main code here, to run repeatedly:

  //    tft.fillScreen(0x0000);
  //    tft.setCursor(0, 0);
  //    tft.setTextSize(5);
  //    tft.println(msg);
  //tft.setCursor(x, y);
  // tft.println("[x=" + String(x) + ",y=" + String(y) + "]");
  //delay(5000);
  // tft.println("INVERT ON");
  //tft.invertDisplay(true);
  //delay(1000);
  //  tft.invertDisplay(false);
  // tft.println("INVERT OFF");
  // delay(1000);
  //if (++aspect >= 4) aspect = 0;
}
