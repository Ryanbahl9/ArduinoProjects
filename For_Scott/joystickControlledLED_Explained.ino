// This includes the FastLED header file.
// The header file contains all the FastLED functions, vlaues, and custome data types
#include <FastLED.h>

// Here we are just defining the variable "NUM_LEDS" to be equal to 240
// It turns out all we do actualy have 240 LEDs. So the reason only the first
// few leds were lighting up wasn't because we fried the rest, its because we
// only set the first 60 to light up
#define NUM_LEDS 240

// All we are doing here is defining the variable "LED_DATA_PIN" to be 6
// This doesn't actualy tell the computer anything. It's just defined here
// to be used later in the program.
const int LED_DATA_PIN = 6;

// This is the same thing as LED_DATA_PIN, just for the x-axis of the joy stick
const int X_PIN = 0;


// This is an array of leds. One item for each led in your strip.
// CRGB is a custome data type defined somewhere in FastLed.h. It's just like int, char, and bool except it represents an LED
// "leds" is the name of the array
// [NUM_LEDS] tell the program how large to make the array. Since we defined NUM_LEDS above, this is the samething as putting [240]
CRGB leds[NUM_LEDS];

// whiteLed is a variable that we will use to store which LED is currently on. 
// since all this program does is light one LED at a time, we only need one variable.
int whiteLed = 0;

// currXval is where we will store the X-axis value coming out of the joystick.
// just for reference, this will be the value read out of the pin labled "VRx" on the joy stick
// the value is always from 0-1000 with 500 being at rest in the center.
int currXval;


// setup() is a function that just runs once at the start of the program,
// which is basicly as soon at you turn on the arduino or finish uploading new code from the computer 
void setup() {
  
  // this line is definatly the most complicated line in here, but all you need to know is that we give it five things:
  //    1) WS2812B: the name IC chip that controls the LEDs
  //    2) LED_DATA_PIN: where we pluged the LED data pin in to the board (This is the green middle wire coming out of the LED strip)
  //    3) RGB: just tells FastLED that LEDs have three colors RGB
  //    4) leds: this is the array we made above. before this line, "leds" was just an empty array with 240 emtpy slots. the FastLED.addLeds() function will fill it with data that corresponds to physical LEDs on our strip.
  //    5) NUM_LEDS: the number of LEDs on the strip
  // 
  FastLED.addLeds<WS2812B, LED_DATA_PIN, RGB>(leds, NUM_LEDS);


  // This tells the program that we will be using the serial port (the blue usb wire) later on in the program. 115200 is the baud rate, aka the number of bits per second
  // Tool->Serial Moniter just displays the text coming through the usb port. but we have to make sure to set the serial moniter to a baud rate of 115200 or it will come through as gibberish
  Serial.begin(115200);
}


// loop() is just the main code that loop in the program
void loop() {

  // since X_PIN is set to 0, this sets the variable "currXval" equil to the value of the analog pin 0 on the board. its labeled "A0" on the board
  currXval = analogRead(X_PIN);

  // leds[whiteLed] just accesses a specific element in the "leds" array. so if whiteLed is 5, is will accesses the 4th element in "leds". 
  // CRGB::Black is a value defined defined in FastLED.h
  // so this line just tells the the current led to turn off.
    // Side Note: Remember how "leds" is an array filled with the custom data type CRGB? well CRGB::Black is a value that fits that data type.
    //            So just like the number '2' is a value that fits the 'int' data type, the value 'CRGB::Black' is a value that fits the 'CRGB'
    //            data type
  leds[whiteLed] = CRGB::Black;


  // This block of code either add one to whiteLed if the joy stick value is above the midpoint or subtracts one if the joy stick value is less than the mid point.
  // even though 500 is technically the value of the joy stick when it is strait up, the readings aren't perfect, so I used 550 and 450 so you have to push the joystick past a certain pint before the light starts moving.
  if (currXval > 550) {
    whiteLed = 1 + whiteLed;
  }
  else if (currXval < 450) {
    whiteLed = whiteLed - 1;
  }


  // this block of code makes it wrap around the other side of the strip.
  // it checks to see if the whiteLed value is beond the range of our led strip.
  // so if whiteLed is -1, it'll wrap around to 239
  if (whiteLed > NUM_LEDS-1){
    whiteLed = whiteLed - NUM_LEDS;
  }
  else if (whiteLed < 0) {
    whiteLed = whiteLed + NUM_LEDS;
  }

  // now that we have that correct whiteLed value, which is either to the left or the right of the previous one, we have to tell that new led to turn on.
  // this is just like the "leds[whiteLed] = CRGB::Black;" line, but telling a new led to turn on.
  leds[whiteLed] = CRGB::White;

  // This is the final FastLED function and it is the only one that actualy changes the lights on and off.
  // Previously all we have done is change the values in the 'leds' array. Basicly, this function tells FastLED to look back at the array and actual make all the changes to the strip that we defined in these lines:
  //   - leds[whiteLed] = CRGB::White;
  //   - leds[whiteLed] = CRGB::Black;
  FastLED.show();


  // This block of code prints out the x value of the joystick and the value of white led
  // These lines won't work work without the 'Serial.begin(115200);' line we had in the setup() function.
  Serial.print("X-axis: ");
  Serial.print(currXval);
  Serial.print("\nwhiteLed: ");
  Serial.print(whiteLed);
  Serial.print("\n\n");

  // pauses the program for 50 ms
  // change this if you want it to move faster or slower
  delay(50);
}
