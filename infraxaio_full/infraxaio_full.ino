// Nom du fichier : IR_LED_Control.ino

#include <IRremote.h>
#include <Adafruit_NeoPixel.h>

const int RECV_PIN = D2;
IRrecv irrecv(RECV_PIN);
decode_results results;

#define PIN            D7  // Définir la broche de données
#define NUMPIXELS      12  // Définir le nombre de pixels

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
 
  pinMode(D3,OUTPUT);digitalWrite(D3,LOW);
  pinMode(D4,OUTPUT);digitalWrite(D4,HIGH);
  irrecv.enableIRIn();  // Démarrer le récepteur
  strip.begin();  // Initialiser la bande de LEDs
  strip.show();   // Initialiser toutes les pixels à 'off'

  for(int i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(0,0,255));  // Pixel 'i' en rouge
        strip.show();
        delay(50);
        //strip.setPixelColor(i, strip.Color(0,0,0));  // Pixel 'i' éteint
      }
}

void loop() {
  if (irrecv.decode(&results)) {
  // Masquer tous les octets sauf les deux derniers
    unsigned int lastOctets = results.value & 0x000F;
    Serial.println(lastOctets, HEX);
    irrecv.resume();  // Recevoir la prochaine valeur
    
    if (lastOctets == 0xA) {  // Remplacez 0xXXXXXXXX par le code de votre bouton
      // Action pour le bouton 1
      for(int i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(255,255,255));  // Pixel 'i' en rouge
        strip.show();
        delay(50);
        //strip.setPixelColor(i, strip.Color(0,0,0));  // Pixel 'i' éteint
      }
    }
   if (lastOctets == 0xB) {  // Remplacez 0xXXXXXXXX par le code de votre bouton
      // Action pour le bouton 1
      for(int i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(255,0,0));  // Pixel 'i' en rouge
        strip.show();
        delay(50);
        //strip.setPixelColor(i, strip.Color(0,0,0));  // Pixel 'i' éteint
      }
    }
    if (lastOctets == 0xC) {  // Remplacez 0xXXXXXXXX par le code de votre bouton
      // Action pour le bouton 1
      for(int i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(0,255,0));  // Pixel 'i' en rouge
        strip.show();
        delay(50);
        //strip.setPixelColor(i, strip.Color(0,0,0));  // Pixel 'i' éteint
      }
    }
    if (lastOctets == 0xD) {  // Remplacez 0xXXXXXXXX par le code de votre bouton
      // Action pour le bouton 1
      for(int i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(0,0,255));  // Pixel 'i' en rouge
        strip.show();
        delay(50);
        //strip.setPixelColor(i, strip.Color(0,0,0));  // Pixel 'i' éteint
      }
    }
  }
}
