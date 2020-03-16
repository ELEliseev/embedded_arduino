/*********************************************************************
This is an example for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

This example is for a 128x64 size display using I2C to communicate
3 pins are required to interface (2 I2C and one reset)

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/

//#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <TimerOne.h>
#include <avr/wdt.h>
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 
//БУАД ФУНКЦИИ
//ВХОДЫ
#define VKZ 2
#define VKO 3
#define REV 4
 

//ВЫХОДЫ
#define OPEND    8
#define CLOSED   9
#define ARR     10
#define REVOUT  11
#define ZUMMER  12
 uint16_t COUNT=0;
 int flagopendoor=LOW;
 int flagclosedoor=HIGH;
 char Error1[]="Одновременно вкз вко";
 char Error2[]="Время ожидания ВКЗ";
 char Error3[]="Время ожидания ВКО";
 int ERR=0;
 int blinking=LOW;
 int opening=LOW;
 int closing=HIGH;
 int Tk=120; //контрольное время 12 секунд
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000001, B00000000,
  B00000101, B01000000,
  B00000011, B10000000,
  B00100001, B00001000,
  B11000001, B00000110,
  B00110001, B00011000,
  B01001101, B01100100,
  B00000011, B10000000,
  B00000011, B10000000,
  B01001101, B01100100,
  B00110001, B00011000,
  B11000001, B00000110,
  B00100001, B00001000,
  B00000011, B10000000,
  B00000101, B01000000,
  B00000001, B00000000 };

  static const unsigned char PROGMEM logo17_glcd_bmp[] =
{ 
  B11111111, B11111111,B11111111, B11111111,B11111111, B11111111,B11111111, B11111111,B11111111, B11111111,B11111111, B11111111,B11111111, B11111111,B11111111, B11111111,
  B11111111, B11111111,B11111111, B11111111,B11111111, B11111111,B11111111, B11111111,B11111111, B11111111,B11111111, B11111111,B11111111, B11111111,B11111111, B11111111,
  B11000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000011,
  B11000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000011,
  B11000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000011,
  B11000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000011,
  B11000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000011,
  B11000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000011,
  B11000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000011,
  B11000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000011,
  B11000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000011,
  B11000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000011,
  B11000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000011,
  B11000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000011,
  B11000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000011,
  B11000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000011,
  B11000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000011,
  B11000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000011,
  B11000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000011,
  B11000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000011,
  B11000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000011,
  B11000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000011,
  B11000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000011,
  B11000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000011,
  B11000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000011,
  B11000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000011,
  B11000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000011,
  B11000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000011,
  B11000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000011,
  B11000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000011,
  B11000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000011,
  B11000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000011,
  B11000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000011,
  B11000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000011,
  B11000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000011,
  B11000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000011,
  B11000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000011,
  B11000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000011,
  B11111111, B11111111,B11111111, B11111111,B11111111, B11111111,B11111111, B11111111,B11111111, B11111111,B11111111, B11111111,B11111111, B11111111,B11111111, B11111111,
  B11111111, B11111111,B11111111, B11111111,B11111111, B11111111,B11111111, B11111111,B11111111, B11111111,B11111111, B11111111,B11111111, B11111111,B11111111, B11111111,
  B10000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000001,
  B10000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000001,
  B10000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000001,
  B10000000, B00000000,B11111111, B11111111,B11111110, B11000000,B00000000, B00000110,B11111111, B11111111,B11111110, B00111111,B11111111, B11111000,B00000000, B00000001,
  B10000000, B00000000,B11111111, B11111111,B11111110, B11000000,B00000000, B00000110,B11111111, B11111111,B11111110, B00111111,B11111111, B11111000,B00000000, B00000001,
  B10000000, B00000000,B11000000, B00000000,B00000000, B11000000,B00000000, B00000110,B11000000, B00000000,B00000110, B00110000,B00000000, B00011000,B00000000, B00000001,
  B10000000, B00000000,B11000000, B00000000,B00000000, B11000000,B00000000, B00000110,B11000000, B00000000,B00000110, B00110000,B00000000, B00011000,B00000000, B00000001,
  B10000000, B00000000,B11000000, B00000000,B00000000, B11000000,B00000000, B00000110,B11000000, B00000000,B00000110, B00110000,B00000000, B00011000,B00000000, B00000001,
  B10000000, B00000000,B11000000, B00000000,B00000000, B11000000,B00000000, B00000110,B11000000, B00000000,B00000110, B00110000,B00000000, B00011000,B00000000, B00000001,
  B10000000, B00000000,B11111111, B11111111,B11111110, B11111111,B11111111, B11111110,B11111111, B11111111,B11111110, B11111111,B11111111, B11111110,B00000000, B00000001,
  B10000000, B00000000,B11111111, B11111111,B11111110, B11111111,B11111111, B11111110,B11111111, B11111111,B11111110, B11111111,B11111111, B11111110,B00000000, B00000001,
  B10000000, B00000000,B11000000, B00000000,B00000110, B00000000,B00000000, B00000110,B11000000, B00000000,B00000110, B11000000,B00000000, B00000110,B00000000, B00000001,
  B10000000, B00000000,B11000000, B00000000,B00000110, B00000000,B00000000, B00000110,B11000000, B00000000,B00000110, B11000000,B00000000, B00000110,B00000000, B00000001,
  B10000000, B00000000,B11000000, B00000000,B00000110, B00000000,B00000000, B00000110,B11000000, B00000000,B00000110, B11000000,B00000000, B00000110,B00000000, B00000001,
  B10000000, B00000000,B11000000, B00000000,B00000110, B00000000,B00000000, B00000110,B11000000, B00000000,B00000110, B11000000,B00000000, B00000110,B00000000, B00000001,
  B10000000, B00000000,B11000000, B00000000,B00000110, B00000000,B00000000, B00000110,B11000000, B00000000,B00000110, B11000000,B00000000, B00000110,B00000000, B00000001,
  B10000000, B00000000,B11000000, B00000000,B00000110, B00000000,B00000000, B00000110,B11000000, B00000000,B00000110, B11000000,B00000000, B00000110,B00000000, B00000001,
  B10000000, B00000000,B11111111, B11111111,B11111110, B11111111,B11111111, B11111110,B11000000, B00000000,B00000110, B11000000,B00000000, B00000110,B00000000, B00000001,
  B10000000, B00000000,B11111111, B11111111,B11111110, B11111111,B11111111, B11111110,B11000000, B00000000,B00000110, B11000000,B00000000, B00000110,B00000000, B00000001,
  B10000000, B00000000,B00000000 ,B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000001,
  B10000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000001,
  B10000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000000,B00000000, B00000001,
  B11111111, B11111111,B11111111, B11111111,B11111111, B11111111,B11111111, B11111111,B11111111, B11111111,B11111111, B11111111,B11111111, B11111111,B11111111, B11111111,
  B11111111, B11111111,B11111111, B11111111,B11111111, B11111111,B11111111, B11111111,B11111111, B11111111,B11111111, B11111111,B11111111, B11111111,B11111111, B11111111};

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void setup()   {    
  pinMode(VKZ,INPUT_PULLUP);   // установить вывод 2 режим входа
 pinMode(VKO,INPUT_PULLUP);   // установить вывод 2 режим входа
 pinMode(REV,INPUT_PULLUP);   // установить вывод 2 режим входа      
 pinMode(OPEND,OUTPUT);   // установить вывод 8 в режим выхода
 pinMode(CLOSED,OUTPUT);   // установить вывод 8 в режим выхода
 pinMode(ARR,OUTPUT);   // установить вывод 8 в режим выхода
 pinMode(REVOUT,OUTPUT);   // установить вывод 8 в режим выхода
 pinMode(ZUMMER,OUTPUT);   // установить вывод 8 в режим выхода
   Timer1.initialize(100000); // инициализация таймера100000 (0,1раз/сек )
  Timer1.attachInterrupt( timerIsr ); // прерывание по переполнению    
 // Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
 
display.cp437(true);
 
  display.clearDisplay();

  // miniature bitmap display
  display.drawBitmap(0, 0,  logo17_glcd_bmp, 128, 64, WHITE);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(50,4);
 display.println(utf8rus("Елисеев Е.Л."));
  display.display();
  delay(1000);

 
  display.clearDisplay();
  // text display tests
  display.setCursor(0,0);
 display.setTextSize(2);
  display.setTextColor(WHITE);
 display.println(utf8rus("стенд для ремонта"));
 display.println(utf8rus("БУАД"));
 display.println(utf8rus("версия 1.1"));
  display.display();
  delay(1000);
  display.clearDisplay();
  
  display.setCursor(0,0);
 display.setTextSize(2);
  display.setTextColor(WHITE);
 display.println(utf8rus("ТЕСТ БУАД"));
display.display();
  testscrolltext();
  delay(2000);

 wdt_enable(WDTO_4S);  // разрешение работы сторожевого таймера с тайм-аутом 8с
}


void loop() {
 display.clearDisplay();  
if(blinking==HIGH){
if(COUNT>20){
   digitalWrite(ZUMMER,HIGH);
 display.invertDisplay(true);
  COUNT=0;
  }
 else if(COUNT>10) { 
  digitalWrite(ZUMMER,LOW);
 display.invertDisplay(false);} 
 
}

 display.setTextSize(2);
  display.setTextColor(WHITE);
  if(digitalRead(VKZ)==HIGH){
   display.setCursor(0,34);
 display.println(utf8rus("ВКЗ "));}
 else{ display.setCursor(0,34);
 display.println(utf8rus("вкз "));
  }
  if(digitalRead(VKO)==HIGH){
   display.setCursor(45,34);
 display.println(utf8rus("ВКО "));}
 else{ display.setCursor(45,34);
 display.println(utf8rus("вко "));
  }
 if(digitalRead(REV)==HIGH){
   display.setCursor(90,34);
 display.println(utf8rus("РЕВ"));}
 else{ display.setCursor(90,34);
 display.println(utf8rus("рев"));
  }
  if(closing==HIGH){
   display.setCursor(0,50);
 display.println(">>>||<<<");}
 if(opening==HIGH){
   display.setCursor(0,50);
 display.println("|<<<>>>|");}
 
 //display.display();
  
  switch(ERR ){
 case 0:
 display.setCursor(0,0);
 display.setTextSize(2);
  display.setTextColor(WHITE);
 display.println(utf8rus("ТЕСТ"));
 display.display();
 break;
 case 1:
 //display.clearDisplay(); 
 display.setCursor(0,0);
 display.setTextSize(2);
  display.setTextColor(WHITE);
 display.println(utf8rus(Error1));
 display.display();
 
 blinking=HIGH;
 break;
 case 2: 
 //display.clearDisplay(); 
 display.setCursor(0,0);
 display.setTextSize(2);
  display.setTextColor(WHITE);
 display.println(utf8rus(Error2));
 display.display();
 
 blinking=HIGH;
 break;
  case 3: 
 //display.clearDisplay(); 
 display.setCursor(0,0);
 display.setTextSize(2);
  display.setTextColor(WHITE);
 display.println(utf8rus(Error3));
 display.display();

 blinking=HIGH;
 break;}
 
if((flagclosedoor==HIGH)&&(flagopendoor==LOW)){//запуск закрытия
  closedoor();
  }
  
 if((flagopendoor==HIGH)&&(flagclosedoor==LOW)){//запуск открытия
   opendoor();
   }

 if(((closing==HIGH)||(opening==HIGH))&&(digitalRead(VKZ)!=1)&&(digitalRead(VKO)!=1)){//проверка на одн вко и вкз при закрытии и открытии
  digitalWrite(CLOSED,LOW);
  digitalWrite(OPEND,LOW); 
  closing=LOW;
  opening=LOW;
  flagclosedoor=LOW;
  flagopendoor=LOW;
  ERR=1;  
  } 
  
  if((closing==HIGH)&&(digitalRead(REV)!=1)){//реверс при закрытии
   digitalWrite(CLOSED,LOW);
    digitalWrite(OPEND,LOW);
   delay(500);
   flagclosedoor=LOW;//запрет запуска закрытия
   flagopendoor=HIGH;//разрешение запуска открытия
   closing=LOW;//останавливаем процесс закрытия
  }
 
  if((closing==HIGH)&&(COUNT>Tk)&&(digitalRead(VKZ)!=0)){ //контр время закрытия
  digitalWrite(CLOSED,LOW);
  digitalWrite(OPEND,LOW);
  opening=LOW;
  closing=LOW;
  flagclosedoor=LOW;
  flagopendoor=LOW;
  ERR=2; } 
    if((opening==HIGH)&&(COUNT>Tk)&&(digitalRead(VKO)!=0)){ //контр время открытия
  digitalWrite(CLOSED,LOW);
  digitalWrite(OPEND,LOW);
  opening=LOW;
  closing=LOW;
  flagclosedoor=LOW;
  flagopendoor=LOW;
  ERR=3; }  
    if((closing==HIGH)&&(digitalRead(VKZ)==0)){//удачное закрытие получаем ВКЗ
    digitalWrite(CLOSED,LOW);
    delay(1000);
    closing=LOW;
    flagopendoor=HIGH;
       }
   if((opening==HIGH)&&(digitalRead(VKO)==0)){//удачное открытие получаем ВКО
    digitalWrite(OPEND,LOW);
    delay(1000);
    opening=LOW;
    flagclosedoor=HIGH;
       }    

      wdt_reset();
 }

void closedoor(){
  flagclosedoor=LOW;//запрет закрытия сброс флага запуска
  COUNT=0;
  digitalWrite(CLOSED,HIGH);
  closing=HIGH;
}
  
 void opendoor(){
  flagopendoor=LOW;//запрет открытия сброс флага запуска
  COUNT=0;
  digitalWrite(OPEND,HIGH);
  opening=HIGH;
}
  
 

       




void testscrolltext(void) {
  display.setTextSize(4);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
 // display.clearDisplay();
  //display.println("ТЕСТ");
  display.display();
  delay(1);
 
  display.startscrollright(0x00, 0x0F);
  delay(5000);
  display.stopscroll();
  delay(1000);
  display.clearDisplay();
  //display.startscrollleft(0x00, 0x0F);
 // delay(2000);
  //display.stopscroll();
  //delay(1000);    
 // display.startscrolldiagright(0x00, 0x07);
  //delay(2000);
 // display.startscrolldiagleft(0x00, 0x07);
  //delay(2000);
 // display.stopscroll();
}
void timerIsr() //прерывание каждые 0,1 секунды 
{
COUNT++;
}


