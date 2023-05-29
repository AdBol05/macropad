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

#define n1 2
#define n2 3
#define n3 13
#define n4 14
#define n5 15
#define n6 21
#define n7 22
#define n8 26
#define n9 27
#define n0 28

#define enter 9
#define plus 10
#define minus 11
#define comma 12

int currentStateCLK;
int lastStateCLK;
unsigned long lastButtonPress = 0;
unsigned int mode = 0;
unsigned int prevmode = 0;
bool modeSW = false;
String lock = "locked";
String mode_str = "GNRL";
String K1 = "E";
String K2 = "T";
String K3 = "V";
String K4 = "S";
String K5 = "#";

void displayUpdate(){
  u8x8.clear();
  u8x8.setCursor(6,0);
  u8x8.print(mode_str);
  u8x8.setCursor(1,6);
  u8x8.print(K1);
  u8x8.setCursor(4,6);
  u8x8.print(K2);
  u8x8.setCursor(7,6);
  u8x8.print(K3);
  u8x8.setCursor(10,6);
  u8x8.print(K4);
  u8x8.setCursor(13,6);
  u8x8.print(K5);
  u8x8.setCursor(5,1);
  u8x8.print(lock);
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
 lastStateCLK = digitalRead(CLK);
 displayUpdate();
 Keyboard.begin();
}

void loop() {
  //rotary encoder input handling
  if (digitalRead(CLK) != lastStateCLK  && digitalRead(CLK) == 1){
    if (digitalRead(DT) == digitalRead(CLK)) {
      if (modeSW == true) {mode --;}
      else {
        Keyboard.press(KEY_DOWN_ARROW);
        delay(100);
        Keyboard.releaseAll();
        }
      } 
    if (digitalRead(DT) != digitalRead(CLK)) {
      if (modeSW == true) {mode ++;}
      else {
        Keyboard.press(KEY_UP_ARROW);
        delay(100);
        Keyboard.releaseAll();
        }
      }
switch (mode){ //display modes
  case 0:
    mode_str = "GNRL";
    K1 = "E";
    K2 = "T";
    K3 = "V";
    K4 = "S";
    K5 = "#";
    break;
  case 1:
    mode_str = "PROG";
    K1 = "S";
    K2 = "R";
    K3 = "U";
    K4 = "X";
    K5 = "K";
    break;
  case 2:
    mode_str = "DISC";
    K1 = "M";
    K2 = "H";
    K3 = "R";
    K4 = "B";
    K5 = "#";
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

if(digitalRead(Key1) == LOW){ //KEY #1 macros
    digitalWrite(LED_BUILTIN, LOW);
  switch (mode){
    case 0:
      Keyboard.press(KEY_LEFT_GUI);
      delay(10);
      Keyboard.press('e');
      delay(200);
      Keyboard.releaseAll();
      break; 
    case 1:
      Keyboard.press(KEY_LEFT_CTRL);
      delay(10);
      Keyboard.press('s');
      delay(200);
      Keyboard.releaseAll();
      break;
    case 2:
      Keyboard.press(KEY_LEFT_CTRL);
      delay(10);
      Keyboard.press(KEY_LEFT_SHIFT);
      delay(10);
      Keyboard.press('m');
      delay(200);
      Keyboard.releaseAll();
      break;
  }
}
if(digitalRead(Key2) == LOW){ //KEY #2 macros
  switch (mode){
    case 0:
      Keyboard.press(KEY_LEFT_CTRL);
      delay(10);
      Keyboard.press(KEY_LEFT_SHIFT);
      delay(10); 
      Keyboard.press(KEY_ESC);
      delay(200);
      Keyboard.releaseAll();
      break;
    case 1:
      Keyboard.press(KEY_LEFT_CTRL);
      delay(10);
      Keyboard.press('r');
      delay(200);
      Keyboard.releaseAll();
      break;
    case 2:
      Keyboard.press(KEY_LEFT_CTRL);
      delay(10);
      Keyboard.press(KEY_LEFT_SHIFT);
      delay(10);
      Keyboard.press('d');
      delay(200);
      Keyboard.releaseAll();
      break;
  }
}
if(digitalRead(Key3) == LOW){ //KEY #3 macros
  switch (mode){
    case 0:
      Keyboard.press(KEY_LEFT_GUI);
      delay(10);
      Keyboard.press('v');
      delay(200);
      Keyboard.releaseAll();
      break;
    case 1:
      Keyboard.press(KEY_LEFT_CTRL);
      delay(10);
      Keyboard.press('u');
      delay(200);
      Keyboard.releaseAll();
      break;
    case 2:
      Keyboard.press(KEY_LEFT_SHIFT);
      delay(10);
      Keyboard.press(KEY_ESC);
      delay(200);
      Keyboard.releaseAll();
      break;
  }
}
if(digitalRead(Key4) == LOW){ //KEY #4 macros
  switch (mode){
    case 0:
      Keyboard.press(KEY_LEFT_CTRL);
      delay(10);
      Keyboard.press('s');
      delay(200);
      Keyboard.releaseAll();
      break;
    case 1:
      Keyboard.press(KEY_LEFT_CTRL);
      delay(10);
      Keyboard.press('x');
      delay(200);
      Keyboard.releaseAll();
      break;
    case 2:
      Keyboard.press(KEY_LEFT_CTRL);
      delay(10);
      Keyboard.press('b');
      delay(200);
      Keyboard.releaseAll();
      break;
  }
}
if(digitalRead(Key5) == LOW){ //KEY #5 macros
  switch (mode){
    case 0:
      Keyboard.press(KEY_LEFT_GUI);
      delay(10);
      Keyboard.press(KEY_LEFT_SHIFT);
      delay(10);
      Keyboard.press('s');
      delay(200);
      Keyboard.releaseAll();
      break;
    case 1:
      Keyboard.press(KEY_LEFT_CTRL);
      delay(10);
      Keyboard.press('k');
      delay(200);
      Keyboard.releaseAll();
      break;
    case 2:
      Keyboard.press(KEY_LEFT_GUI);
      delay(10);
      Keyboard.press(KEY_LEFT_SHIFT);
      delay(10);
      Keyboard.press('s');
      delay(200);
      Keyboard.releaseAll();
      break;
  }
}

//Numpad
if(digitalRead(n1) == LOW){Keyboard.press(KEY_KP_1);delay(50);Keyboard.releaseAll();}
if(digitalRead(n2) == LOW){Keyboard.press(KEY_KP_2);delay(50);Keyboard.releaseAll();}
if(digitalRead(n3) == LOW){Keyboard.press(KEY_KP_3);delay(50);Keyboard.releaseAll();}
if(digitalRead(n4) == LOW){Keyboard.press(KEY_KP_4);delay(50);Keyboard.releaseAll();}
if(digitalRead(n5) == LOW){Keyboard.press(KEY_KP_5);delay(50);Keyboard.releaseAll();}
if(digitalRead(n6) == LOW){Keyboard.press(KEY_KP_6);delay(50);Keyboard.releaseAll();}
if(digitalRead(n7) == LOW){Keyboard.press(KEY_KP_7);delay(50);Keyboard.releaseAll();}
if(digitalRead(n8) == LOW){Keyboard.press(KEY_KP_8);delay(50);Keyboard.releaseAll();}
if(digitalRead(n9) == LOW){Keyboard.press(KEY_KP_9);delay(50);Keyboard.releaseAll();}
if(digitalRead(n0) == LOW){Keyboard.press(KEY_KP_0);delay(50);Keyboard.releaseAll();}
if(digitalRead(enter == LOW){Keyboard.press(KEY_KP_ENTER);delay(50);Keyboard.releaseAll();}
if(digitalRead(plus) == LOW){Keyboard.press(KEY_KP_PLUS);delay(50);Keyboard.releaseAll();}
if(digitalRead(minus) == LOW){Keyboard.press(KEY_KP_MINUS);delay(50);Keyboard.releaseAll();}
if(digitalRead(comma) == LOW){Keyboard.press(KEY_KP_DOT);delay(50);Keyboard.releaseAll();}

  if(prevmode != mode){ //update display when mode changes
    displayUpdate();
    prevmode = mode;
  }

  if(mode >= 3) {mode = 0;} //modes limiter
delay(1);
}
