#include <FastLED.h>

#define NUM_LEDS 240

const int LED_DATA_PIN = 6;
const int X_PIN = 0;

CRGB leds[NUM_LEDS];

int whiteLed = 0;
int currXval;


void setup() {
  FastLED.addLeds<WS2812B, LED_DATA_PIN, RGB>(leds, NUM_LEDS);
  Serial.begin(115200);
}

void loop() {

  currXval = analogRead(X_PIN);
  leds[whiteLed] = CRGB::Black;
  
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

  leds[whiteLed] = CRGB::White;

  FastLED.show();

  Serial.print("X-axis: ");
  Serial.print(currXval);
  Serial.print("\nwhiteLed: ");
  Serial.print(whiteLed);
  Serial.print("\n\n");

  delay(50);
}
