#include <IRremote.h>
#include <FastLED.h>

const unsigned long int POWER_BTN = 16753245;

const unsigned long int VOL_PLUS_BTN = 16736925;
const unsigned long int VOL_MINUS_BTN = 16754775;

const unsigned long int FAST_FORWARD_BTN = 16761405;
const unsigned long int REWIND_BTN = 16720605;

const unsigned long int PAUSE_PLAY_BTN = 16712445;

const unsigned long int DOWN_ARROW_BTN = 16769055;
const unsigned long int UP_ARROW_BTN = 16748655;

const unsigned long int FUNC_STOP_BTN = 16769565;
const unsigned long int EQ_BTN = 16750695;
const unsigned long int ST_REPT_BTN = 16756815;

const unsigned long int ZERO_BTN = 16738455;
const unsigned long int ONE_BTN = 16724175;
const unsigned long int TWO_BTN = 16718055;
const unsigned long int THREE_BTN = 16743045;
const unsigned long int FOUR_BTN = 16716015;
const unsigned long int FIVE_BTN = 16726215;
const unsigned long int SIX_BTN = 16734885;
const unsigned long int SEVEN_BTN = 16728765;
const unsigned long int EIGHT_BTN = 16730805;
const unsigned long int NINE_BTN = 16732845;

const unsigned long int REPEATED_BTN = 4294967295;

const int NUM_LEDS = 240;

const int IR_PIN = 8;
const int LED_PIN = 6;

unsigned long int recievedFromIR = 0;

IRrecv receiver(IR_PIN);
decode_results output;


CRGB leds[NUM_LEDS];


void AllColor(CRGB::HTMLColorCode color);
void PatternOne();
void ResetLEDs();
bool isIrBtn(unsigned long int irValue);
void PrintIrBtnName(unsigned long int irValue, char preface[] = "");


void setup() {
  // put your setup code here, to run once:
  delay(100);
  Serial.begin(9600);
  output.decode_type = 1;
  receiver.enableIRIn();
  FastLED.addLeds<WS2812B, LED_PIN, RGB>(leds, NUM_LEDS);
  ResetLEDs();
  while(true){
    if (receiver.decode(&output)){
      receiver.decode(&output);
      PrintIrBtnName(output.value);
      if (output.value == POWER_BTN){
        break;
      }
      else {
        receiver.resume();
      }
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  if (receiver.decode(&output)){
    Serial.print("\n");
    if (isIrBtn(output.value)){
      recievedFromIR = output.value;
    }
    /*
    if (output.value != REPEATED_BTN && output.value != 0) {
      recievedFromIR = output.value;
    }
    */
    PrintIrBtnName(output.value, "Output value: ");
    PrintIrBtnName(recievedFromIR, "recievedFromIR: ");
    receiver.resume();
    switch(recievedFromIR){
      case POWER_BTN:
      case ONE_BTN:
        Serial.print("\nCalling number 1");
        PatternOne();
        break;
      case  TWO_BTN:
        AllColor(CRGB::Red);
        Serial.print("\nCalling Pattern 2");
        break;
      case THREE_BTN:
        AllColor(CRGB::Blue);
        Serial.print("\nCalling Pattern 3");
        break;
      default:
        AllColor(CRGB::Green);
        break;
    }
  }
  delay(10);
}

void AllColor(CRGB::HTMLColorCode color){
  for(int i = 0; i < NUM_LEDS; i++){
    leds[i] = color;
  }
  FastLED.show();
}

void PatternOne(){
  int currentLED = 0;
  
  ResetLEDs();

  leds[currentLED] = CRGB::White;
  FastLED.show();
  while(true){
    if (receiver.decode(&output)) {
      PrintIrBtnName(output.value, "Output value: ");
      if (isIrBtn(output.value) && output.value != ONE_BTN){
        return;
      }
      receiver.resume();
    }
    leds[currentLED] = CRGB::Black;
    currentLED = (currentLED + 1) % NUM_LEDS;
    leds[currentLED] = CRGB::White;
    FastLED.show();
    delay(10);
  } 
}

void ResetLEDs(){
  for(int i = 0; i < NUM_LEDS; i++){
    leds[i] = CRGB::Black;
  }
  Serial.print("");
  FastLED.show();
}

bool isIrBtn(unsigned long int irValue){
  switch(irValue){
    case POWER_BTN:
    case VOL_PLUS_BTN:      
    case VOL_MINUS_BTN:
    case FAST_FORWARD_BTN:
    case REWIND_BTN:
    case PAUSE_PLAY_BTN:
    case DOWN_ARROW_BTN:
    case UP_ARROW_BTN:
    case FUNC_STOP_BTN:
    case EQ_BTN:
    case ST_REPT_BTN:
    case ZERO_BTN:
    case ONE_BTN:
    case TWO_BTN:
    case THREE_BTN:
    case FOUR_BTN:
    case FIVE_BTN:
    case SIX_BTN:
    case SEVEN_BTN:
    case EIGHT_BTN:
    case NINE_BTN:
      break;
  
    case REPEATED_BTN:
      return false;
      break;
    
    default:
      return false;
      break;
  }
  return true;
}


void PrintIrBtnName(unsigned long int irValue, char preface[]){
  Serial.print("\n");
  Serial.print(preface);
  switch(irValue){
    case POWER_BTN:
      Serial.print("Power");
      break;
      
    case VOL_PLUS_BTN:
      Serial.print("Volume Up");
      break;
      
    case VOL_MINUS_BTN:
      Serial.print("Volume Down");
      break;
      
    case FAST_FORWARD_BTN:
      Serial.print("Fast Forward");
      break;
      
    case REWIND_BTN:
      Serial.print("Rewind");
      break;
      
    case PAUSE_PLAY_BTN:
      Serial.print("Pause / Play");
      break;
      
    case DOWN_ARROW_BTN:
      Serial.print("Down Arrow");
      break;
      
    case UP_ARROW_BTN:
      Serial.print("Up Arrow");
      break;
      
    case FUNC_STOP_BTN:
      Serial.print("Function / Stop");
      break;
      
    case EQ_BTN:
      Serial.print("EQ");
      break;
      
    case ST_REPT_BTN:
      Serial.print("ST / Rept");
      break;
      
    case ZERO_BTN:
      Serial.print("0");
      break;
      
    case ONE_BTN:
      Serial.print("1");
      break;
      
    case TWO_BTN:
      Serial.print("2");
      break;
      
    case THREE_BTN:
      Serial.print("3");
      break;
      
    case FOUR_BTN:
      Serial.print("4");
      break;
      
    case FIVE_BTN:
      Serial.print("5");
      break;
       
    case SIX_BTN:
      Serial.print("6");
      break;
       
    case SEVEN_BTN:
      Serial.print("7");
      break;
       
    case EIGHT_BTN:
      Serial.print("8");
      break;
       
    case NINE_BTN:
      Serial.print("9");
      break;
  
    case REPEATED_BTN:
      Serial.print("Repeated btn");
      break;
    
    default:
      Serial.print("Unknown: ");
      Serial.print(irValue);
      break;
  }
}
