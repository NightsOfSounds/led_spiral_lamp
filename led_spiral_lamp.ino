#include <FastLED.h>
#define DATA_PIN 2
#define NUM_LEDS 170
#define BUTTON_PORT 3
CRGB leds[NUM_LEDS];

int mode = 0;
int buttonState = 0;

/**
 * @brief sets up lamp
 */
void setup() {
  Serial.begin(9600); //debug
  // init leds
  FastLED.addLeds<NEOPIXEL, 2>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  for(int i = 0; i<NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.setBrightness(255);
  FastLED.show();

  // init button
  pinMode(BUTTON_PORT, INPUT_PULLUP);
}

/**
 * @brief runs animation
 */
void loop() {
  // button click and debounce
  int newState = digitalRead(BUTTON_PORT); //LOW -> Pressed
  if(newState == LOW && buttonState == HIGH) {
    mode = (mode + 1) % 12;
  }
  buttonState = newState;

  // led show
  showMode(mode, millis());
  FastLED.show();
}

/**
 * @brief shows the selected led mode
 * 
 * @param mode mode to show (0 - 11)
 * @param millis timestamp to show
 */
void showMode(int mode, long millis) {
  switch(mode) {
    case 0:
      rainbow(millis);
      break;
    case 1:
      layerBottomToTop(millis);
      break;
    case 2:
      perlinColor(millis);
      break;
    case 3:
      rainbowRoated(millis);
      break;
    case 4:
      toCenter(millis);
      break;
    case 5:
      circleInToOut(millis);
      break;
    case 6:
      solidRed(millis);
      break;
    case 7:
      solidOrange(millis);
      break;
    case 8:
      solidGreen(millis);
      break;
    case 9:
      solidCyan(millis);
      break;
    case 10:
      solidBlue(millis);
      break;
    case 11:
      solidMagenta(millis);
      break;
  }
}

/**
 * @brief Rainbow from top to bottom
 * 
 * @param millis timestamp to show animation to
 */
void rainbow(long millis) {
  for(int y = 0; y < NUM_LEDS; y++) {
    int inverseY = NUM_LEDS - y - 1;
    int hue = inverseY * ( 255.0 / NUM_LEDS ) + (millis / 100);
    leds[y]= CHSV(hue, 255, 255);
  }
}

/**
 * @brief color change from bottom to top of the spiral
 * 
 * @param millis timestamp to show animation to
 */
void layerBottomToTop(long millis) {

  int h2 = millis / 6000 * 40;
  int h1 = h2 + 40;
  
  int pos = (int)(millis % 6000);
  for(int i = 0; i<NUM_LEDS; i++) {

    double hc1 = max(min(pos - (i*1000) - 1000 / -10.0, 100),0) / 100.0;
    double hc2 = min(1 - hc1, 1);
    
    leds[i] = CHSV(h1 * hc1 + h2 * hc2, 255, 255);
  }
}

/**
 * @brief displays random colors on each pixel (simplex noise)
 * 
 * @param millis timestamp to show animation to
 */
void perlinColor(long millis) {
  for(int i = 0; i < NUM_LEDS; i++) {
    int hue = inoise8(i, millis);
    leds[i] = CHSV(hue, 255, 255);
  }
}

/**
 * @brief Show rotating rainbow, same colors on y-axis (vertical)
 * 
 * @param millis timestamp to show animation to
 */
void rainbowRoated(long millis) {
    //TODO
}

/**
 * @brief shows two lines from top and bottom to center
 * 
 * @param millis timestamp to show animation to
 */
void toCenter(long millis) {
    //TODO
}

/**
 * @brief Shows a circle from inside to outside changing to color
 * 
 * @param millis timestamp to show animation to
 */
void circleInToOut(long millis) {
  //TODO
}

/**
 * @brief solid red color
 * 
 * @param millis timestamp to show animation to
 */
void solidRed(long millis) {
  for(int i = 0; i<NUM_LEDS; i++) {
    leds[i] = CRGB(inoise8(i, millis), 0, 0);
  }
}

/**
 * @brief solid orange color
 * 
 * @param millis timestamp to show animation to
 */
void solidOrange(long millis) {
  for(int i = 0; i<NUM_LEDS; i++) {
    leds[i] = CRGB(inoise8(i, millis), inoise8(i, millis) * (153 / 255.0), 0);
  }
}

/**
 * @brief solid green color
 * 
 * @param millis timestamp to show animation to
 */
void solidGreen(long millis) {
  for(int i = 0; i<NUM_LEDS; i++) {
    leds[i] = CRGB(0, inoise8(i, millis), 0);
  }
}

/**
 * @brief solid cyan color
 * 
 * @param millis timestamp to show animation to
 */
void solidCyan(long millis) {
  for(int i = 0; i<NUM_LEDS; i++) {
    leds[i] = CRGB(0, inoise8(i, millis) * (204.0 / 255), inoise8(i, millis));
  }
}

/**
 * @brief solid blue color
 * 
 * @param millis timestamp to show animation to
 */
void solidBlue(long millis) {
  for(int i = 0; i<NUM_LEDS; i++) {
    leds[i] = CRGB(0, 0, inoise8(i, millis));
  }
}

/**
 * @brief solid magenta color
 * 
 * @param millis timestamp to show animation to
 */
void solidMagenta(long millis) {
   for(int i = 0; i<NUM_LEDS; i++) {
    leds[i] = CRGB(inoise8(i, millis), 0, inoise8(i, millis));
  }
}