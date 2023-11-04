// Nom du fichier : IR_LED_Control.ino

#include <IRremote.h>
#include <Adafruit_NeoPixel.h>

const int RECV_PIN = D2;
IRrecv irrecv(RECV_PIN);
decode_results results;

#define PIN            D7
#define NUMPIXELS      12

bool rainbow_On=false;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int mode = 0;

void setup() {
  Serial.begin(9600);

  pinMode(D3, OUTPUT);
  digitalWrite(D3, LOW);
  
  pinMode(D4, OUTPUT);
  digitalWrite(D4, HIGH);

  irrecv.enableIRIn(); 
  strip.begin();
  strip.show();

  for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(0,0,255));
    strip.show();
    delay(50);
  }
}
void rainbow(int wait) {
  uint16_t i, j;
  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void loop() {
  if (irrecv.decode(&results)) {
    unsigned int lastOctets = results.value & 0x000F;
    Serial.println(lastOctets, HEX);
    irrecv.resume();

    if (lastOctets == 0xA) {
      mode++;
      if (mode > 3) {
        mode = 0;
      }

      switch(mode) {
        case 0:
          for(int i=0; i<strip.numPixels(); i++) {
            strip.setPixelColor(i, strip.Color(0,0,255)); 
            strip.show();
            delay(50);
          }
          break;
        case 1:
          for(int i=0; i<strip.numPixels(); i++) {
            strip.setPixelColor(i, strip.Color(255,0,0)); 
            strip.show();
            delay(50);
          }
          break;
        case 2:
          for(int i=0; i<strip.numPixels(); i++) {
            strip.setPixelColor(i, strip.Color(166,0,205)); 
            strip.show();
            delay(50);
          }
          break;
        case 3:
          for(int i=0; i<strip.numPixels(); i++) {
            strip.setPixelColor(i, strip.Color(255,255,255)); 
            strip.show();
            delay(50);
          }
          break;
       
      }
    }
    if (lastOctets == 0xB) {
      // Augmente la luminosité
      uint8_t brightness = strip.getBrightness();
      brightness += 20;
      if (brightness > 255) brightness = 255;
      strip.setBrightness(brightness);
      strip.show();
    }
    if (lastOctets == 0xC) {
      // Éteint les LEDs
      for(int i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(0,0,0));
        strip.show();
      }
    }
    if (lastOctets == 0xD) {
       if (rainbow_On==false)
       {
        rainbow_On=true;
       }else
       {
       rainbow_On=false;
        }
      
    }
   lastOctets =0xF;
  }
   delay(400);
   if (rainbow_On==true)
   {
    rainbow(20);
   }
}
