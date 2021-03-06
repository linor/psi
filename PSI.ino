/**
 * PSI sketch by Linor
 * 
 * No changes need to be made in this file. Please see the 'Config' tab
 * for any options that you can change.
 * 
 * This sketch currently supports plain 31 led boards as well as the
 * Vader Extreme series PSI's by Selgus.
 * 
 */
#include <FastLED.h>
#include "config.h"

//#define DEBUG
#ifdef DEBUG
  #define DEBUG_OUT(msg)  Serial.println(msg)
#else
  #define DEBUG_OUT(msg) 
#endif
extern CRGB leds[];

enum state {
  Primary,
  PrimaryToSecondary,
  Secondary,
  SecondaryToPrimary
};

state ledState = Primary;
uint8_t visibleSecondaryColumns = 0;
unsigned long nextEvent = 0;
unsigned long swipeDelay = 0;
unsigned long lastLedUpdate = 0;
CRGB overlayColors[COLUMNS];

void setup() {
  led_setup();

  CRGB startColor = primary_color();
  for(int i = 0; i < 31; i++) {
    leds[i] = startColor;
  }
  FastLED.show(brightness());

  nextEvent = millis() + random(PRIMARY_COLOR_DURATION_MINIMUM, PRIMARY_COLOR_DURATION_MAXIMUM);
  
#ifdef DEBUG
  Serial.begin(9600);
#endif
  DEBUG_OUT("PSI Sketch by Linor - Ready");
}

void fill_column(uint8_t column, CRGB color) {
  uint8_t reverseColumn = COLUMNS - 1 - column;
  for(int i = 0; i < LEDS_PER_COLUMN; i++) {
    int8_t ledIndex = ledMatrix[column][i];
    if (ledIndex != -1) leds[ledIndex] = color;
  }
}

void loop() {
  int updateLed = 0;
  
  if (millis() >= nextEvent) {
    switch(ledState) {
      case Primary: {
        ledState = PrimaryToSecondary;
        swipeDelay = random(SWIPE_DELAY_MINIMUM, SWIPE_DELAY_MAXIMUM);
        DEBUG_OUT("Switching to secondary color");

        
        int totalChance = CHANCE_SECONDARY_FULL + CHANCE_SECONDARY_PARTIAL + CHANCE_SECONDARY_PARTIAL_OFF;
        int selection = random(totalChance);
        if (selection < CHANCE_SECONDARY_FULL) {
          DEBUG_OUT("Selected full color");
          for(int i = 0; i < COLUMNS; i++) {
            overlayColors[i] = secondary_color();
          }
        } else if (selection < CHANCE_SECONDARY_FULL + CHANCE_SECONDARY_PARTIAL) {
          DEBUG_OUT("Selected partial secondary, with rest primary");
          for(int i = 0; i < COLUMNS; i++) {
            overlayColors[i] = i > COLUMNS - SECONDARY_PARTIAL_OFF_LINES - 1 ? secondary_color() : primary_color();
          }
        } else {
          DEBUG_OUT("Selected partial secondary, rest off");
          for(int i = 0; i < COLUMNS; i++) {
            overlayColors[i] = i > COLUMNS - SECONDARY_PARTIAL_OFF_LINES - 1 ? secondary_color() : secondary_off_color();
          }
        }

        // Intentional fall through 
      }
      case PrimaryToSecondary:
        visibleSecondaryColumns++;
        if (visibleSecondaryColumns >= COLUMNS) {
          DEBUG_OUT("On secondary color");
          ledState = Secondary;
          nextEvent = millis() + random(SECONDARY_COLOR_DURATION_MINIMUM, SECONDARY_COLOR_DURATION_MAXIMUM);
        } else {
          nextEvent = millis() + swipeDelay;
        }
        break;
      case Secondary: {
        ledState = SecondaryToPrimary;
        swipeDelay = random(SWIPE_DELAY_MINIMUM, SWIPE_DELAY_MAXIMUM);
        DEBUG_OUT("Switching to primary color");
        // Intentional fall through
      }
      case SecondaryToPrimary:
        visibleSecondaryColumns--;
        if (visibleSecondaryColumns == 0) {
          DEBUG_OUT("On primary color");
          ledState = Primary;
          nextEvent = millis() + random(PRIMARY_COLOR_DURATION_MINIMUM, PRIMARY_COLOR_DURATION_MAXIMUM);
        } else {
          nextEvent = millis() + swipeDelay;
        }
        break;
    }

    updateLed = 1;
  }

  if (updateLed || ((millis() - lastLedUpdate) > 100)) {
    lastLedUpdate = millis();
    
    CRGB primaryColor = primary_color();
    uint8_t switchPoint = COLUMNS - visibleSecondaryColumns;

    for(int i = 0; i < COLUMNS; i++) {
      CRGB columnColor = primaryColor;
      if (i >= switchPoint) {
        columnColor = overlayColors[i - switchPoint];
      }
      fill_column(i, columnColor);
    }

    FastLED.show(brightness());
  }
}
