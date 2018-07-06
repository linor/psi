#ifndef VADER_EXTREME


CRGB leds[NUM_LEDS];

void led_setup() {
  FastLED.addLeds<SK6812, LED_PIN, GRB>(leds, NUM_LEDS);
}

#ifdef FRONT
  CRGB primary_color() {
    return frontPrimaryColor;
  }
  
  CRGB secondary_color() {
    return frontSecondaryColor;
  }

  CRGB secondary_off_color() {
    return frontSecondaryOffColor;
  }
#else
  CRGB primary_color() {
    return rearPrimaryColor;
  }
  
  CRGB secondary_color() {
    return rearSecondaryColor;
  }

  CRGB secondary_off_color() {
    return rearSecondaryOffColor;
  }
  
#endif

uint8_t brightness() {
  return BRIGHTNESS;
}

#endif
