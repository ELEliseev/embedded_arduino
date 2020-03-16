/* Создание WiFi точки доступа и запуск на ней Web - сервера. */ 
#include <ESP8266WiFi.h> 
#include <WiFiClient.h> 
#include <ESP8266WebServer.h> 

/* Установка имени точки доступа и пароля входа в неё */ 
const char *ssi = "myTABLO"; 
const char *passw = "11223344"; 
ESP8266WebServer server(80); 
const int GPIO1 = 5; // led0 - это GPIO0 
 char bufferInfo[13]={'0','0','0','1','0','0','0','0','1','0','0','0','\0'};

void getInfo(){             
server.send(200, "text/html",bufferInfo);
              }             


void root(){ 
server.send(200, "text/html","<h1>This is web-server on Wifi-esp-12.<br>He controls GPIO.<br>Command:/gpioxxon /gpioxxoff</h1>"); 
} 
void setup() { 

pinMode(GPIO1, INPUT_PULLUP); 
delay(1000); 
Serial.begin(115200); 
//Serial.println(); 
//Serial.print("Configuring access point..."); 
/* You can remove the password parameter if you want the AP to be open. */ 
WiFi.softAP(ssi, passw); 
//WiFi.begin ( ssid, password );

IPAddress myIP = WiFi.softAPIP(); 
//Serial.print("AP IP address: "); 
//Serial.println(myIP); 

server.on("/gpio2on", getInfo); 


server.begin(); 
//Serial.println("HTTP server started"); 
attachInterrupt(digitalPinToInterrupt (GPIO1), interupt, RISING );
//Serial.println( bufferInfo );
} 
// Цикл по получению пакетов от браузера 
void loop() { 
  server.handleClient(); 
}
void interupt(){
  detachInterrupt(GPIO1);
 delayMicroseconds(1300);
 for(int i=11;i>=0;i--){
  if(digitalRead(GPIO1)==HIGH){
    bufferInfo[i]='1';}
    else {
     bufferInfo[i]='0';}
      delayMicroseconds(2000);
    }
 attachInterrupt(digitalPinToInterrupt (GPIO1), interupt, RISING );
  }







