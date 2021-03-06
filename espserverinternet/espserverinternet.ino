/* Создание WiFi точки доступа и запуск на ней Web - сервера. */ 
#include <ESP8266WiFi.h> 
#include <WiFiClient.h> 
#include <ESP8266WebServer.h> 
#include <ESP8266mDNS.h>
/* Установка имени точки доступа и пароля входа в неё */ 
 

const char *ssid = "Xiaomi_SKORKU";
const char *password = "wsxcde234";

ESP8266WebServer server(80); 
const int led = 13;
const int led2 = 2; 
int count=-4;
/* Web - сервер из браузера виден по адресу http://192.168.4.1 */ 
/* Определения функций, при обращении к которым сервер будет пересылать браузеру соответствующие сообщения */ 

void led2_on(){ 
digitalWrite(led2, 0); 

server.send(200, "text/html",String(count));
if(count<32){
  count++; }
  else{count=-4;}
              } 
void led2_off() { 
digitalWrite(led2, 1); 
server.send(200, "text/html","gpio2 of"); 
} 

void setup() { 
// GPIO работают на выход 
 
pinMode(led2, OUTPUT); 
digitalWrite(led2, 1); 
delay(1000); 
Serial.begin(115200); 
 WiFi.mode ( WIFI_STA );
  WiFi.begin ( ssid, password );
/* You can remove the password parameter if you want the AP to be open. */ 

while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  Serial.println ( "" );
  Serial.print ( "Connected to " );
  Serial.println ( ssid );
  Serial.print ( "IP address: " );
  Serial.println ( WiFi.localIP() );
if ( MDNS.begin ( "esp8266" ) ) {
    Serial.println ( "MDNS responder started" );
  }

  server.on ( "/", handleRoot );
  server.on ( "/test.svg", drawGraph );
  server.on ( "/inline", []() {
    server.send ( 200, "text/plain", "this works as well" );
  } );
  server.onNotFound ( handleNotFound );
  server.begin();
  Serial.println ( "HTTP server started" );
server.on("/gpio2on", led2_on); 
server.on("/gpio2off", led2_off); 

server.begin(); 
Serial.println("HTTP server started"); 
} 
// Цикл по получению пакетов от браузера 
void loop() { 
server.handleClient(); 
}

void handleRoot() {
  digitalWrite ( led, 1 );
  char temp[400];
  int sec = millis() / 1000;
  int min = sec / 60;
  int hr = min / 60;

  snprintf ( temp, 400,

"<html>\
  <head>\
    <meta http-equiv='refresh' content='5'/>\
    <title>ESP8266 Demo</title>\
    <style>\
      body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
    </style>\
  </head>\
  <body>\
    <h1>Hello from ESP8266!</h1>\
    <p>Uptime: %02d:%02d:%02d</p>\
    <img src=\"/test.svg\" />\
  </body>\
</html>",

    hr, min % 60, sec % 60
  );
  server.send ( 200, "text/html", temp );
  digitalWrite ( led, 0 );
}

void handleNotFound() {
  digitalWrite ( led, 1 );
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += ( server.method() == HTTP_GET ) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for ( uint8_t i = 0; i < server.args(); i++ ) {
    message += " " + server.argName ( i ) + ": " + server.arg ( i ) + "\n";
  }

  server.send ( 404, "text/plain", message );
  digitalWrite ( led, 0 );
}
void drawGraph() {
  String out = "";
  char temp[100];
  out += "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"400\" height=\"150\">\n";
  out += "<rect width=\"400\" height=\"150\" fill=\"rgb(250, 230, 210)\" stroke-width=\"1\" stroke=\"rgb(0, 0, 0)\" />\n";
  out += "<g stroke=\"black\">\n";
  int y = rand() % 130;
  for (int x = 10; x < 390; x+= 10) {
    int y2 = rand() % 130;
    sprintf(temp, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke-width=\"1\" />\n", x, 140 - y, x + 10, 140 - y2);
    out += temp;
    y = y2;
  }
  out += "</g>\n</svg>\n";

  server.send ( 200, "image/svg+xml", out);
}

