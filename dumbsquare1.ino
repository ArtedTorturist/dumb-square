
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void setup() {
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();

}
int ste=1;
int z=0;

int anar(int, int=0);
float anarf(int, float=0);
int scsq(int, int, int);

void loop() {
  int ain0=0;
  int ain1=0;
  int xp=64;
  int yp=32;
  int sc=4;
  int sock;
  bool upd=false;
  while(z==0){
    while(ste==0){
      ain1=anar(1);
      ain0=anar(0, 3);
      if(anar(1)!=ain1){
        upd=true;
        switch(ain0){
          case 0:
          sc=anar(1, 64);
          break;
          case 1:
          xp=anar(1, 128);
          break;
          case 2:
          yp=anar(1, 64);
        }
      }
      if(upd==true){
        upd=false;
        ste=1;
      }
    }
    while(ste==1){
      display.clearDisplay();
      sock=scsq(xp, yp, sc);
      display.display();
      ste=0;
    }
  }
}

int scsq(int sx, int sy, int ss){
  int h=0;
  int w=0;
  int qc=ss/2;
  
  if(sy+qc>64){
    sy=64-ss;
  } else if(sy-qc<0){
    sy=0;
  } else {
    sy=sy-qc;
  }

  if(sx+qc>128){
    sx=128-ss;
  } else if(sx-qc<0){
    sx=0;
  } else {
    sx=sx-qc;
  }
  
  while(h<ss){
    while(w<ss){
      display.drawPixel(sx+w, sy+h, SSD1306_WHITE);
      ++w;
    }
    w=0;
    ++h;
  }
  return ss;
}

int anar(int ap, int sl){
  float scav;
  float fa=0;
  int a=0;
  switch(ap){
    case 0:
    a=analogRead(A0);
    break;
    case 1:
    a=analogRead(A1);
    break;
    case 2:
    a=analogRead(A2);
    break;
    case 3:
    a=analogRead(A3);
    break;
    case 4:
    a=analogRead(A4);
    break;
    case 5:
    a=analogRead(A5);
    break;
    default:
    a=-300;
    break;
  }
  if(a!=-300&&sl!=0){
    scav=sl;
    fa=a;
    scav=scav/1023.0f*fa;
    a=scav;
  }
  return a;
}
