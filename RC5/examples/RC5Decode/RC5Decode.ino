/*
 *  Wiring notes:
 *  
 *  Using IR sensor like this:
 *    http://www.adafruit.com/products/157
 *  wired as follows:
 *   pin1 - arduino pin 7 
 *   pin2 - ground
 *   pin3 - 5V
 *  
 *  This code will display address, command and toggle for decoded sequences.
 *  Pressing the power button twice gives this result:
 *     a:0 c:12 t:0  <- first press, a:0 => TV1, c:12 => Standby command.
 *     a:0 c:12 t:0
 *     a:0 c:12 t:0
 *     a:0 c:12 t:1  <- second press, toggle changes
 *     a:0 c:12 t:1
 *
 */
 
#include <RC5.h>
int Ledpin = 3;
int IR_PIN = 7;
unsigned int tip;
RC5 rc5(IR_PIN);

void setup() {                
  Serial.begin(9600);
  Serial.println("Starting");
  pinMode( Ledpin, OUTPUT);
}

void loop() {
  unsigned char toggle;
  unsigned char address;
  unsigned char command;
  if (rc5.read(&tip))
  {
    Serial.print("tip:");
    Serial.println(tip&4095);
    digitalWrite(Ledpin, HIGH);
    delay(50);
    digitalWrite(Ledpin, LOW);
  }
  
}
