#include <Wire.h>
#include <SPI.h>
#include <U8x8lib.h>
#include <Keyboard.h>

U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);

#define CLK 6
#define DT 7
#define SW 8
#define Key1 16
#define Key2 17
#define Key3 18
#define Key4 19
#define Key5 20

int currentStateCLK;
int lastStateCLK;
unsigned long lastButtonPress = 0;
unsigned int mode = 0;
unsigned int prevmode = 0;
bool modeSW = false;
String lock = "locked";
String mode_str = "MEDIA";

void displayUpdate(){
  u8x8.clear();
  u8x8.setCursor(5,0);
  u8x8.print(mode_str);
  u8x8.setCursor(5,1);
  u8x8.print(lock);
  //u8x8.setCursor(2,3);
  //u8x8.print(mode);
}

void setup() {
 pinMode(CLK,INPUT_PULLDOWN);
 pinMode(DT,INPUT_PULLDOWN);
 pinMode(SW, INPUT_PULLUP);
 pinMode(Key1, INPUT_PULLUP);
 pinMode(Key2, INPUT_PULLUP);
 pinMode(Key3, INPUT_PULLUP);
 pinMode(Key4, INPUT_PULLUP);
 pinMode(Key5, INPUT_PULLUP);
 u8x8.begin();
 u8x8.setFont(u8x8_font_chroma48medium8_r);
 u8x8.noInverse();
 u8x8.clear();
 pinMode(LED_BUILTIN, OUTPUT);
 digitalWrite(LED_BUILTIN, HIGH);
 lastStateCLK = digitalRead(CLK);
 displayUpdate();
 Keyboard.begin();
}

void loop() {
  //rotary encoder input handling
  digitalWrite(LED_BUILTIN, HIGH);

  if (digitalRead(CLK) != lastStateCLK  && digitalRead(CLK) == 1){
    if (digitalRead(DT) == digitalRead(CLK)) {
      if (modeSW == true) {mode --;}
      else {
        Keyboard.press(KEY_F5);
        delay(200);
        Keyboard.releaseAll();
        }
      } 
    if (digitalRead(DT) != digitalRead(CLK)) {
      if (modeSW == true) {mode ++;}
      else {
        Keyboard.press(KEY_F5);
        delay(200);
        Keyboard.releaseAll();
        }
      }
switch (mode){
  case 0:
    mode_str = "MEDIA";
    break;
  case 1:
    mode_str = "PROGR";
    break;
} 
    if (modeSW == true) {displayUpdate();}
  }

  //mode change based on rotary encoder
  lastStateCLK = digitalRead(CLK);
  int btnState = digitalRead(SW);
  if (btnState == LOW) {
    delay(200);
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

if(Key1 == LOW){
  switch (mode){
    case 0:
      Keyboard.press(KEY_LEFT_CTRL);
      delay(200);
      Keyboard.releaseAll();
      break;
    case 1:
      Keyboard.press(KEY_LEFT_SHIFT);
      delay(200);
      Keyboard.releaseAll();
      break;
  }
}
if(Key2 == LOW){
  switch (mode){
    case 0:
      Keyboard.press(KEY_LEFT_ALT);
      delay(200);
      Keyboard.releaseAll();
      break;
    case 1:
      Keyboard.press(KEY_LEFT_GUI);
      delay(200);
      Keyboard.releaseAll();
      break;
  }
}
if(Key3 == LOW){
  switch (mode){
    case 0:
      Keyboard.press(KEY_RIGHT_CTRL);
      delay(200);
      Keyboard.releaseAll();
      break;
    case 1:
      Keyboard.press(KEY_RIGHT_SHIFT);
      delay(200);
      Keyboard.releaseAll();
      break;
  }
}
if(Key4 == LOW){
  switch (mode){
    case 0:
      Keyboard.press(KEY_RIGHT_ALT);
      delay(200);
      Keyboard.releaseAll();
      break;
    case 1:
      Keyboard.press(KEY_RIGHT_GUI);
      delay(200);
      Keyboard.releaseAll();
      break;
  }
}
if(Key5 == LOW){
  switch (mode){
    case 0:

      Keyboard.press(KEY_UP_ARROW);
      delay(200);
      Keyboard.releaseAll();
      break;
    case 1:
      Keyboard.press(KEY_DOWN_ARROW);
      delay(200);
      Keyboard.releaseAll();
      break;
  }
}

  if(prevmode != mode){
    displayUpdate();
    prevmode = mode;
  }

  if(mode >= 2) {mode = 0;}
delay(1);
}
