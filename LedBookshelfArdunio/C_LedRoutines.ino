

int red[3] = {255, 0, 0};
int colors[3][3] = {{225 , 228 , 235}, {22 , 103 , 248}, {39 , 136 , 248}};

//int colors[25][3] = {{225 , 228 , 235}, {22 , 103 , 248}, {39 , 136 , 248}, {59 , 172 , 249}, {92 , 215 , 251}}, {108 , 242 , 249}, {92 , 252 , 253}, {100 , 252 , 228}, {99 , 251 , 191}, {101 , 251 , 163, {102 , 251 , 148}, {103 , 251 , 97}, {104 , 250 , 72}, {110 , 250 , 71}, {155 , 251 , 72}, {187 , 252 , 76}, {217 , 252 , 77}, {242 , 253 , 79}, {255 , 253 , 80}, {254 , 229 , 77}, {245 , 117 , 54}, {243 , 52 , 48}, {242 , 56 , 128, , 228 , 55 , 168}, {107 , 47 , 247}};



void allOn(int r, int g, int b) {
  for (int i = 0; i < NUM_LEDS ; i++) {
    leds[i] = CRGB(r, g, b);
  }
  FastLED.show();
}

void allOff() {
  for (int i = 0; i < NUM_LEDS ; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
}

void runRight() {
  for (int i = 0; i < NUM_LEDS ; i++) {
    leds[i] = CRGB::Green;
    FastLED.show();
    delay(1);
    leds[i] = CRGB::Black;
    FastLED.show();
  }
}

void runLeft() {
  for (int i = NUM_LEDS - 1; i >= 0 ; i--) {
    leds[i] = CRGB::Green;
    FastLED.show();
    delay(1);
    leds[i] = CRGB::Black;
    FastLED.show();
  }
}

void blinkColorsAndSquares() {
  for (int i = 0; i < 5 ; i++) {
    for (int j = 0; j < 5 ; j++) {
      drawSquare(j, i, colors[i * 5 + j][0], colors[i * 5 + j][1], colors[i * 5 + j][2]);
      delay(40);
    }
  }
  allOff();
}

void blinkSpiral() {
  int interval = 80;
  int path[25][2] = {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {4, 1}, {4, 2}, {4, 3}, {4, 4}, {3, 4}, {2, 4}, {1, 4}, {0, 4}, {0, 3}, {0, 2}, {0, 1}, {1, 1}, {2, 1}, {3, 1}, {3, 2}, {3, 3}, {2, 3}, {1, 3}, {1, 2}, {2, 2}};  
  blinkPath(path, false, interval);
}

void blinkPath(int path[25][2], boolean reverse, int interval) {
  for (int i = 0 ; i < 25 ; i++) {
    int index = i;
    if (reverse) {
      index = 25 - 1 - i;
    }
    drawSquare(path[index][0], path[index][1], colors[index][0], colors[index][1], colors[index][2]);
    delay(interval);
  }
  allOff();
}



void drawSquare(int x, int y, int r, int g, int b) {
  int startIndex = 0;
  if (y % 2 == 0) {
    startIndex = x * ledsInEachSquare + y * height * ledsInEachSquare;
  } else {
    startIndex = (width - 1 - x)  * ledsInEachSquare + y * height * ledsInEachSquare;
  }
  for (int k = 0; k < ledsInEachSquare ; k++) {
    leds[startIndex + k] = CRGB(r, g, b);
  }
  FastLED.show();
}

void drawSquareNr(int i, int r, int g, int b) {
  drawSquare(i%width, i/height, r, g, b);
}

void blinkRGB() {
  int timeBetween = 200;
  allOn(255, 0, 0);
  delay(timeBetween);
  allOff();
  delay(timeBetween);
  allOn(0, 255, 0);
  delay(timeBetween);
  allOff();
  delay(timeBetween);
  allOn(0, 0, 255);
  delay(timeBetween);
  allOff();
}

void testAll() {
  allOn(255, 0, 0);
  delay(1000);
  allOn(0, 255, 0);
  delay(1000);
  allOn(0, 0, 255);
  delay(1000);
  allOff();
  delay(1000);
}
