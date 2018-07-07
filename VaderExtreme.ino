#ifdef VADER_EXTREME

#define JUMP_FRONT_REAR 3
#define POT_BRIGHT A6

CRGB leds[NUM_LEDS];

void led_setup() {
  pinMode(JUMP_FRONT_REAR, INPUT);
  pinMode(POT_BRIGHT, INPUT);
  
  FastLED.addLeds<WS2812, 1, GRB>(leds, NUM_LEDS);
}

CRGB primary_color() {
  if (digitalRead(JUMP_FRONT_REAR)) {
    return frontPrimaryColor;
  } else {
    return rearPrimaryColor;
  }
}

CRGB secondary_color() {
  if (digitalRead(JUMP_FRONT_REAR)) {
    return frontSecondaryColor;
  } else {
    return rearSecondaryColor;
  }
}

CRGB secondary_off_color() {
  if (digitalRead(JUMP_FRONT_REAR)) {
    return frontSecondaryOffColor;
  } else {
    return rearSecondaryOffColor;
  }
}

uint8_t brightness() {
  return map(analogRead(POT_BRIGHT), 0, 1024, 0, 255);
}


#endif
