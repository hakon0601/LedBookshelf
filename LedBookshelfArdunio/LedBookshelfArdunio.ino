
#include <FastLED.h>

#define NUM_LEDS 250
#define DATA_PIN 5
CRGB leds[NUM_LEDS];

int rightButtonPin = D6;
int leftButtonPin = D7;

boolean pongEnabled = false;
boolean snakeEnabled = false;
boolean rainEnabled = false;
boolean randomEnabled = false;
boolean randomFrequenciesEnabled = false;
boolean buttonTestEnabled = false;

int width = 5;
int height = 5;
int ledsInEachSquare = 10;
boolean rightEnabled = true;
boolean leftEnabled = true;
int initialUpdateInterval = 800;
int minimumUpdateInterval = 200;
int updateInterval = initialUpdateInterval;


void setup() {
  pinMode(rightButtonPin, INPUT);
  pinMode(leftButtonPin, INPUT);
  Serial.begin(115200);
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  //setupWifi();
  Serial.println("What do you want to play?\n[Left]: Pong\n[Right]: Snake");
  
  setRandomPongSpeed();
  setInitialPongX();
  setInitialSnakeSpeed();
  setInitialSnake();
  setRandomApple();
  resetRainMatrix();
  setupRandomFrequencies();
  
  allOff();
  //blinkColorsAndSquares();
  //blinkSpiral();
}

void decreaseUpdateInterval(int value) {
  if (updateInterval - value < minimumUpdateInterval) {
    updateInterval = minimumUpdateInterval;
  } else {
    updateInterval = updateInterval - value;
  }
}

boolean readRight() {
  if (rightEnabled && digitalRead(rightButtonPin)) {
    leftEnabled = false;
    rightEnabled = false;
    return true;
  } else {
    return false;
  }
}

boolean readLeft() {
  if (leftEnabled && digitalRead(leftButtonPin)) {
    leftEnabled = false;
    rightEnabled = false;
    return true;
  } else {
    return false;
  }
}

void testButtons() {
  if (digitalRead(rightButtonPin)) {
      drawSquare(4, 2, 0, 255, 0);
      FastLED.show();
      delay(50);
    } else {
      drawSquare(4, 2, 0, 0, 0);
    }
    if (digitalRead(leftButtonPin)) {
      drawSquare(0, 2, 255, 255, 0);
      FastLED.show();
      delay(50);
    } else {
      drawSquare(0, 2, 0, 0, 0);
    }
}

int count = 0;
float sum = 0;
int ran = 0;

void loop() {
  
  boolean rightRead = readRight();
  boolean leftRead = readLeft();
  if (buttonTestEnabled) {
    testButtons();
  }
  //blinkSpiral();
  //handleServer();
  if (pongEnabled) {
    playPong(leftRead, rightRead);
  } else if (snakeEnabled) {
    playSnake(leftRead, rightRead);
  } else if (rainEnabled) {
    playRain();
  } else if (randomEnabled) {
    playRandom();
  } else if (randomFrequenciesEnabled) {
    playRandomFrequencies();
  } else if (leftRead) {
    pongEnabled = true;
    leftEnabled = true;
    rightEnabled = true;
    Serial.println("Starting Pong");
    delay(300);
  } else if(rightRead) {
    snakeEnabled = true;
    leftEnabled = true;
    rightEnabled = true;
    Serial.println("Starting Snake");
    delay(300);
  }
  
}
