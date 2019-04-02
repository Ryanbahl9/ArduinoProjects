#include <FastLED.h>

#define NUM_LEDS 240

const int LED_DATA_PIN = 6;
const int X_PIN = 0;

CRGB leds[NUM_LEDS];
CRGB redLED = CRGB::Red;
CRGB greenLED = CRGB::Green;

int lastState = 0;
int whiteLed = 0;
int currXval;


void setup() {
  FastLED.addLeds<WS2812B, LED_DATA_PIN, RGB>(leds, NUM_LEDS);
  Serial.begin(115200);
}

void loop() {

  currXval = analogRead(X_PIN);

  if (lastState == 0 || lastState == 1){
    leds[whiteLed] = CRGB::Green;
  }
  else {
    leds[whiteLed] = CRGB::Red;
  }


  
  
  if (currXval > 550) {
    whiteLed = 1 + whiteLed;
  }
  else if (currXval < 450) {
    whiteLed = whiteLed - 1;
  }

  if (whiteLed > NUM_LEDS-1){
    whiteLed = whiteLed - NUM_LEDS;
  }
  else if (whiteLed < 0) {
    whiteLed = whiteLed + NUM_LEDS;
  }


    
  if (leds[whiteLed] == redLED){
    lastState = 1;
  }
  else if (leds[whiteLed] == greenLED) {
    lastState = 2;
  }
  else {
    lastState = 0;
  }



  leds[whiteLed] = CRGB::White;

  FastLED.show();

  Serial.print("X-axis: ");
  Serial.print(currXval);
  Serial.print("\nwhiteLed: ");
  Serial.print(whiteLed);
  Serial.print("\n\n");

  //delay(50);
}
