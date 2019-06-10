

int snakeUpdateIntervalSpeed = 30;
int snakeSpeed[2];
int snakeMaxLength = height * width;
int snake[25][2];
int apple[2];
int snakePoints = 0;
long lastSnakeTime = 0;


void setInitialSnakeSpeed() {
  snakeSpeed[0] = 1;
  snakeSpeed[1] = 0;
}

void setInitialSnake() {
  for (int i = 0 ; i < height * width ; i++) {
    snake[i][0] = -1;
    snake[i][1] = -1;
  }
  snake[0][0] = 0;
  snake[0][1] = 0;
}

void setRandomApple() {
  while (true) {
    int newAppleX = random(width);
    int newAppleY = random(height);
    if (!isSnake(newAppleX, newAppleY)) {
      apple[0] = newAppleX;
      apple[1] = newAppleY;
      return;
    }
  }
}

boolean isSnake(int x, int y) {
  for (int i = 0 ; i < snakeMaxLength ; i++) {
    if (snake[i][0] == x && snake[i][1] == y) {
      return true;
    }
  }
  return false;
}

boolean isApple(int x, int y) {
  if (apple[0] == x && apple[1] == y) {
    return true;
  }
  return false;
}

void pressLeftSnake() {
  Serial.println("left");
  if (snakeSpeed[0] == 1) {
    snakeSpeed[0] = 0;
    snakeSpeed[1] = - 1;
  } else if (snakeSpeed[0] == -1) {
    snakeSpeed[0] = 0;
    snakeSpeed[1] = 1;
  } else if (snakeSpeed[1] == 1) {
    snakeSpeed[0] = 1;
    snakeSpeed[1] = 0;
  } else if (snakeSpeed[1] == -1) {
    snakeSpeed[0] = -1;
    snakeSpeed[1] = 0;
  }
}

void pressRightSnake() {
  Serial.println("right");
  rightEnabled = false;
  leftEnabled = true;
  if (snakeSpeed[0] == 1) {
    snakeSpeed[0] = 0;
    snakeSpeed[1] = 1;
  } else if (snakeSpeed[0] == -1) {
    snakeSpeed[0] = 0;
    snakeSpeed[1] = -1;
  } else if (snakeSpeed[1] == 1) {
    snakeSpeed[0] = -1;
    snakeSpeed[1] = 0;
  } else if (snakeSpeed[1] == -1) {
    snakeSpeed[0] = 1;
    snakeSpeed[1] = 0;
  }
}

void updateSnake() {
  int newHead[2] = {snake[snakePoints][0] + snakeSpeed[0], snake[snakePoints][1] + snakeSpeed[1]};
  if ((snakeSpeed[0] == 1 && snake[snakePoints][0] == width - 1) ||
      (snakeSpeed[0] == -1 && snake[snakePoints][0] == 0) ||
      (snakeSpeed[1] == 1 && snake[snakePoints][1] == height - 1) ||
      (snakeSpeed[1] == -1 && snake[snakePoints][1] == 0)) {
    Serial.println("here1");
    snakeGameOver();
  }
  // if crashing into something other than tail
  else if (isSnake(newHead[0], newHead[1]) && !(newHead[0] == snake[0][0] && newHead[1] == snake[0][1])) {
    snakeGameOver();
    Serial.println("here2");
  } else if (snake[snakePoints][0] + snakeSpeed[0] == apple[0] &&
             snake[snakePoints][1] + snakeSpeed[1] == apple[1]) {
    snakePoints = snakePoints + 1;
    Serial.println("got apple");
    snake[snakePoints][0] = snake[snakePoints - 1][0] + snakeSpeed[0];
    snake[snakePoints][1] = snake[snakePoints - 1][1] + snakeSpeed[1];
    setRandomApple();
    decreaseUpdateInterval(snakeUpdateIntervalSpeed);
  }
  else {
    Serial.println("update snake");
    for (int i = 0; i < snakePoints ; i++) {
      snake[i][0] = snake[i + 1][0];
      snake[i][1] = snake[i + 1][1];
    }
    snake[snakePoints][0] = snake[snakePoints][0] + snakeSpeed[0];
    snake[snakePoints][1] = snake[snakePoints][1] + snakeSpeed[1];
  }
  if (snakeEnabled) {
    //printSnakeSpeed();
    //printOnlySnake();
    //printSnake();
    //printApple();
    printLedSnake();
    printOnlySnake();
  }
  leftEnabled = true;
  rightEnabled = true;
}

void playSnake(boolean leftPress, boolean rightPress) {
  if (leftPress) {
    pressLeftSnake();
  }
  if (rightPress) {
    pressRightSnake();
  }
  long timeSinceLastUpdate = millis() - lastSnakeTime;
  if (timeSinceLastUpdate > updateInterval) {
    lastSnakeTime = millis();
    updateSnake();
  }
}


void printSnake() {
  for (int i = 0; i < height ; i++) {
    for (int j = 0; j < width ; j++) {
      if (isSnake(j, i)) {
        Serial.print("0");
      } else if (isApple(j, i)) {
        Serial.print("a");
      } else {
        Serial.print("X");
      }
    }
    Serial.println("");
  }
  Serial.println("");
}

void printOnlySnake() {
  for (int i = 0; i < snakeMaxLength ; i++) {
    Serial.print("[");
    Serial.print(snake[i][0]);
    Serial.print(", ");
    Serial.print(snake[i][1]);
    Serial.print("], ");
  }
  Serial.println("");
}

void printApple() {
  Serial.print(apple[0]);
  Serial.print(" : ");
  Serial.println(apple[1]);
  //drawSquare(apple[0], apple[1], 255, 0, 0);
}

void printSnakeSpeed() {
  Serial.print("Snake speed: [");
  Serial.print(snakeSpeed[0]);
  Serial.print(", ");
  Serial.print(snakeSpeed[1]);
  Serial.print("]");
  Serial.println("");
}



void printLedSnake() {
  for (int i = 0; i < height ; i++) {
    for (int j = 0; j < width ; j++) {
      if (isSnake(j, i)) {
        Serial.print("0");
        drawSquare(j, i, 0, 0, 255);
      } else if (isApple(j, i)) {
        Serial.print("a");
        drawSquare(j, i, 0, 255, 0);
      } else {
        Serial.print("X");
        drawSquare(j, i, 0, 0, 0);
      }
    }
    Serial.println("");
  }
  Serial.println("");

  /*
  // Draw empty board
  for (int i = 0 ; i < NUM_LEDS ; i++) {
    leds[i] = CRGB(0, 0, 0);
  }

  // Draw snake
  for (int j = 0; j < snakePoints + 1 ; j++) {
    drawSquare(snake[j][0], snake[j][1], 0, 0, 255);
  }
  // Draw apple
  drawSquare(apple[0], apple[1], 0, 255, 0);
  */
  /*
  int appleSquareNr = apple[1] * width + apple[0];
  for (int l = 0; l < ledsInEachSquare ; l++) {
    drawSquare(apple[0], apple[1], 0, 255, 0);
  }
  */
  FastLED.show();
}

void snakeGameOver() {
  Serial.println("You loose");
  blinkRGB();
  resetSnake();
}

void resetSnake() {
  snakeEnabled = false;
  snakePoints = 0;
  updateInterval = initialUpdateInterval;
  setInitialSnakeSpeed();
  setInitialSnake();
  setRandomApple();
  Serial.println("What do you want to play?\n[Left]: Pong\n[Right]: Snake");
}
