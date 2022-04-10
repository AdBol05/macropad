#include <Wire.h>
#include <SPI.h>
#include <U8x8lib.h>

U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);

#define CLK 6
#define DT 7
#define SW 8

int currentStateCLK;
int lastStateCLK;
unsigned long lastButtonPress = 0;
int mode = 0;
bool modeSW = false;
String lock = "locked";

void displayUpdate(){
  u8x8.clear();
  u8x8.setCursor(1,1);
  u8x8.print("     MODE     ");
  u8x8.setCursor(5,2);
  u8x8.print(lock);
  u8x8.setCursor(2,3);
  u8x8.print(mode);
}

void setup() {
 pinMode(CLK,INPUT_PULLDOWN);
 pinMode(DT,INPUT_PULLDOWN);
 pinMode(SW, INPUT_PULLUP);
 u8x8.begin();
 u8x8.setFont(u8x8_font_chroma48medium8_r);
 u8x8.noInverse();
 u8x8.clear();
 pinMode(LED_BUILTIN, OUTPUT);
 digitalWrite(LED_BUILTIN, HIGH);
 lastStateCLK = digitalRead(CLK);
 displayUpdate();
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  if (digitalRead(CLK) != lastStateCLK  && digitalRead(CLK) == 1){
    if (digitalRead(DT) == digitalRead(CLK)) {
      if (modeSW == true) {mode ++;}
      } 
    if (digitalRead(DT) != digitalRead(CLK)) {
      if (modeSW == true) {mode --;}
      } 
    if (modeSW == true) {displayUpdate();}
  }

  lastStateCLK = digitalRead(CLK);
  int btnState = digitalRead(SW);
  if (btnState == LOW) {
    delay(100);
    if (modeSW == false) {
      modeSW = true;
      lock = "change";
      }
    else {
      modeSW = false;
      lock = "locked";
      }
    displayUpdate();
    }
  
delay(10);
}
