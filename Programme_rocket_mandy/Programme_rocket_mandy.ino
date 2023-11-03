#include <IRremote.h>
#include <Adafruit_NeoPixel.h>

const int RECV_PIN = D2;
IRrecv irrecv(RECV_PIN);
decode_results results;

#define PIN            D7
#define NUMPIXELS      12

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Variables pour le mode arc-en-ciel
unsigned long previousMillis = 0;
const long interval = 50;
int currentPixel = 0;
int rainbowStep = 5;
int mode = 0;  // 0 pour aucun effet, 1 pour arc-en-ciel

void setup() {
  Serial.begin(9600);

  pinMode(D3, OUTPUT);
  digitalWrite(D3, LOW);
  pinMode(D4, OUTPUT);
  digitalWrite(D4, HIGH);

  irrecv.enableIRIn();
  strip.begin();
  strip.show();
}

void loop() {
  if (irrecv.decode(&results)) {
    unsigned int lastOctets = results.value & 0x000F;
    Serial.println(lastOctets, HEX);
    irrecv.resume();

    switch (lastOctets) {
      case 0xA:
        mode = 1;  // Activer le mode arc-en-ciel
        break;
      case 0xB:
        mode = 0;  // Désactiver l'effet
        colorWipe(strip.Color(255, 0, 0));  // Rouge
        break;
      case 0xC:
        mode = 0;  // Désactiver l'effet
        colorWipe(strip.Color(0, 0, 0));  // Éteindre les LEDs
        break;
      case 0xD:
        mode = 0;  // Désactiver l'effet
        colorWipe(strip.Color(0, 0, 255));  // Bleu
        break;
    }
  }

  if (mode == 1) {
    updateRainbow();
  }
}

void colorWipe(uint32_t c) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(50);
  }
}

void updateRainbow() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    if (currentPixel < strip.numPixels()) {
      int color = Wheel(((currentPixel * rainbowStep) % 255));
      strip.setPixelColor(currentPixel, color);
      strip.show();
      currentPixel++;
    } else {
      currentPixel = 0;
    }
    previousMillis = currentMillis;
  }
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
