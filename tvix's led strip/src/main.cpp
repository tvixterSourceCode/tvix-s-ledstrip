#include <Arduino.h>
#include <FastLED.h>
#include <IRremote.hpp>


const int num = 90;
int max_bright = 255;

int num_passed = 0;
const int farness = 20;
float mutliplier_of_w = 1;
float eventlasttime = millis();
float unbuttonlasttime = millis();
bool gonna_light;
bool setted = false;
bool button_pressed = false; 
int red = 255;
int blue = 255;
int green = 255;
char mode = 'r';
char modecolor = 'r';

#define Chanell_down 0xBA45FF00
#define Chanell 0xB946FF00
#define Chanell_up 0xB847FF00
#define pev 0xBB44FF00
#define next 0xBF40FF00
#define play_stop 0xBC43FF00
#define minus 0xF807FF00
#define plus 0xEA15FF00
#define eq 0xF609FF00
#define zero 0xE916FF00
#define plus_hundred 0xE619FF00
#define plus_twohundered 0xF20DFF00
#define one 0xF30CFF00
#define two 0xE718FF00
#define three 0xA15EFF00
#define four 0xF708FF00
#define five 0xE31CFF00
#define six 0xA55AFF00
#define seven 0xBD42FF00
#define eight 0xAD52FF00
#define nine 0xB54AFF00

CRGB leds[num];
CRGB rcolor = CRGB(rand() % 256, rand() % 256, rand() % 256);



void change_led(CRGB color,int brightness, int from , int to, bool is_button)
{
  if (button_pressed && is_button || !button_pressed)
  {
    for (int i = from; i < to;i++)
    {
      leds[i] = color;
      FastLED.setBrightness(brightness);
    }
      FastLED.show();
  }
  if (is_button)
  {
    setted = false;
  }
}

void check_remote() 
{
    if (IrReceiver.decode())
    { 
      switch (IrReceiver.decodedIRData.decodedRawData)
      {
      case plus:
        max_bright = (max_bright + 5) % 255;
        button_pressed = true;
        unbuttonlasttime = millis();
        change_led(CRGB(255,255,255),max_bright,0,ceil(max_bright / (255 / num)),true);
        change_led(CRGB(0,0,0),max_bright,ceil(max_bright / (255 / num)),num,true);
        break;
      case minus:
        max_bright = (max_bright - 5)% 255;
        button_pressed = true;
        unbuttonlasttime = millis();
        change_led(CRGB(255,255,255),max_bright,0,ceil(max_bright / (255 / num)),true);
        change_led(CRGB(0,0,0),max_bright,ceil(max_bright / (255 / num)),num,true);
        break;
      case Chanell_down:
        modecolor = 'r';
        button_pressed = true;
        unbuttonlasttime = millis();
        change_led(CRGB(255,0,0),max_bright,0,num,true);
        break;
      case Chanell:
        modecolor = 'g';
        button_pressed = true;
        unbuttonlasttime = millis();
        change_led(CRGB(0,255,0),max_bright,0,num,true);
        break;
      case Chanell_up:
        modecolor = 'b';
        button_pressed = true;
        unbuttonlasttime = millis();
        change_led(CRGB(0,0,255),max_bright,0,num,true);
        break;
      case pev:
        if(modecolor == 'r')
        {
          red = (red - 5)% 255;
          button_pressed = true;
          unbuttonlasttime = millis();
          change_led(CRGB(255,0,0),max_bright,0,ceil(red / (255 / num)),true);
          change_led(CRGB(0,0,0),max_bright,ceil(red / (255 / num)),num,true);
          }
        else if (modecolor == 'g')
        {
          green = (green - 5)% 255;
          button_pressed = true;
          unbuttonlasttime = millis();
          change_led(CRGB(0,255,0),max_bright,0,ceil(green / (255 / num)),true);
          change_led(CRGB(0,0,0),max_bright,ceil(green / (255 / num)),num,true);
        }
        else if (modecolor == 'b')
        {
          blue = (blue - 5)% 255;
          button_pressed = true;
          unbuttonlasttime = millis();
          change_led(CRGB(0,0,255),max_bright,0,ceil(blue / (255 / num)),true);
          change_led(CRGB(0,0,0),max_bright,ceil(blue / (255 / num)),num,true);
        }
        break;
        
        case next:
        if(modecolor == 'r')
        {
          red = (red + 5)% 255;
          button_pressed = true;
          unbuttonlasttime = millis();
          change_led(CRGB(255,0,0),max_bright,0,ceil(red / (255 / num)),true);
          change_led(CRGB(0,0,0),max_bright,ceil(red / (255 / num)),num,true);
          }
        else if (modecolor == 'g')
        {
          green = (green + 5)% 255;
          button_pressed = true;
          unbuttonlasttime = millis();
          change_led(CRGB(0,255,0),max_bright,0,ceil(green / (255 / num)),true);
          change_led(CRGB(0,0,0),max_bright,ceil(green / (255 / num)),num,true);
        }
        else if (modecolor == 'b')
        {
          blue = (blue + 5)% 255;
          button_pressed = true;
          unbuttonlasttime = millis();
          change_led(CRGB(0,0,255),max_bright,0,ceil(blue / (255 / num)),true);
          change_led(CRGB(0,0,0),max_bright,ceil(blue / (255 / num)),num,true);
        }
        break;
      case one:
        mode = 'r';
        change_led(CRGB(255,255,255),max_bright,0,1,true);
        button_pressed = true;
        unbuttonlasttime = millis();
        break;
      case two:
        mode = 'b';
        change_led(CRGB(255,255,255),max_bright,0,2,true);
        button_pressed = true;
        unbuttonlasttime = millis();
        break;
      case three:
        mode = 'g';
        change_led(CRGB(255,255,255),max_bright,0,3,true);
        button_pressed = true;
        unbuttonlasttime = millis();
        setted = false;
        break;
      case four:
        mode = 'w';
        change_led(CRGB(255,255,255),max_bright,0,4,true);
        button_pressed = true;
        unbuttonlasttime = millis();
        break;
      }
      Serial.println(mode);
      IrReceiver.resume();
    }
}

void blink_light(bool light,bool is_random)
{
  rcolor = light? CRGB(rand() % 256, rand() % 256, rand() % 256) : rcolor;
  rcolor = is_random? rcolor : CRGB(red,green,blue);
  for (int bi = light ? 0: max_bright; light? bi < max_bright : bi >= 0 ; light? bi++:bi--)
  {
    change_led(rcolor,bi,0,num,false);
    check_remote();
    delay(1);
    check_remote();
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  FastLED.addLeds<WS2812B,10,GRB>(leds,num);
  FastLED.clear();
  FastLED.show();
  IrReceiver.begin(11,true);
}

void loop() {
  // put your main code here, to run repeatedly:
  switch (mode)
  {
  case 'r':
    if (millis() - eventlasttime >= 1000+abs(90-num)) 
    {
      blink_light(gonna_light,true);
      gonna_light = !gonna_light;
      eventlasttime = millis();
      setted = false;
    }
    break;
  case 'b':
    if (millis() - eventlasttime >= 1000+abs(90-num)) 
    {
      blink_light(gonna_light,false);
      gonna_light = !gonna_light;
      eventlasttime = millis();
      setted = false;
    }
    break;
  case 'g':
    if (!setted && !button_pressed){
      change_led(CRGB(red,green,blue),max_bright,0,num,false);
      setted = true;
    }
    break;
  
  }
  if (millis() - unbuttonlasttime >= 3000)
  {
    button_pressed = false;
    unbuttonlasttime = millis();
  }
  check_remote();
  
}