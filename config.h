// Vader Extreme configuration
// #define VADER_EXTREME

// Led board only configuration
#define FRONT
#define LED_PIN 6
#define BRIGHTNESS 15

// Number of milliseconds before switching to the secondary
// color.
// A random value between MINIMUM and MAXIMUM will be used.
#define PRIMARY_COLOR_DURATION_MINIMUM 1000
#define PRIMARY_COLOR_DURATION_MAXIMUM 2000

// Number of milliseconds that the secondary color will be
// visible before switching back to the primary color.
// A random value between MINIMUM and MAXIMUM will be used.
#define SECONDARY_COLOR_DURATION_MINIMUM 1000
#define SECONDARY_COLOR_DURATION_MAXIMUM 2000

// Delay for the swipe animation. 
#define SWIPE_DELAY_MINIMUM 30
#define SWIPE_DELAY_MAXIMUM 50

// Defines the chances between the various options for
// the secondary color. If the chance for an option is 
// set to 0, it will not be selected.
#define CHANCE_SECONDARY_FULL 2
#define CHANCE_SECONDARY_PARTIAL 2
#define CHANCE_SECONDARY_PARTIAL_OFF 2

// How many columns to convert to the secondary color,
// the remainder of the columns will be converted to 
// the secondary off color.
#define SECONDARY_PARTIAL_LINES 3
#define SECONDARY_PARTIAL_OFF_LINES 3

// Colors for the front PSI, note that the off color is only used
// when the nr of secondary lines is less than the total number of
// columns
CRGB frontPrimaryColor = CRGB(0, 0, 255);  // Blue
CRGB frontSecondaryColor = CRGB(255, 0, 0); // Red
CRGB frontSecondaryOffColor = CRGB::Black; // Off

// Colors for the rear PSI
CRGB rearPrimaryColor = CRGB(0, 255, 0);      // Green
CRGB rearSecondaryColor = CRGB(200, 170, 0);  // Yellow
CRGB rearSecondaryOffColor = CRGB::Black; // Off


//
// CHANGED BEYOND THESE LINES SHOULD NOT BE NECESSARY
// 

  #define NUM_LEDS 31
  #define LEDS_PER_COLUMN 5
  #define COLUMNS 7
  
  int8_t ledMatrix[COLUMNS][LEDS_PER_COLUMN] = {
    { 0, 1, 2, -1, -1 }, 
    { 3, 4, 5, 6, 7 }, 
    { 8, 9, 10, 11, 12 },
    { 13, 14, 15, 16, 17 }, 
    { 18, 19, 20, 21, 22 }, 
    { 23, 24, 25, 26, 27 },
    { 28, 29, 30, -1, -1 } 
  };

