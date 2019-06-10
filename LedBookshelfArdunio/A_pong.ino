

int pongSpeed; // 1 = moving right, -1 moving left
int pongX;
int hardHitValue = 50;
int softHitValue = 20;
long lastPongTime = 0;

void setRandomPongSpeed() {
  long ran = random(2);
  if (ran == 0) {
    pongSpeed = -1;
  }
  pongSpeed = 1;
}

void setInitialPongX() {
  if (pongSpeed == 1) {
    pongX = 0;
  } else {
    pongX = width - 1;
  }
}

boolean pongIsEnabled() {
  return pongEnabled;
}

void pressLeftPong() {
  Serial.println("left");
  pongSpeed = 1;
  if (pongX == 0) {
    decreaseUpdateInterval(hardHitValue);
  } else if (pongX == 1) {
    decreaseUpdateInterval(softHitValue);
  } else {
    pongGameOver("Left");
  }

}

void pressRightPong() {
  Serial.println("right");
  pongSpeed = -1;
  if (pongX == width - 1) {
    decreaseUpdateInterval(hardHitValue);
  } else if (pongX == width - 2) {
    decreaseUpdateInterval(softHitValue);
  } else {
    pongGameOver("Right");
  }
}

void updatePong() {
  if (pongSpeed == 1) {
    if (pongX == width - 1) {
      pongGameOver("Right");
      return;
    } else {
      pongX = pongX + 1;
    }
  } else {
    if (pongX == 0) {
      pongGameOver("Left");
      return;
    } else {
      pongX = pongX - 1;
    }
  }
  if (pongEnabled) {
    printPong();
    printLedPong();
    leftEnabled = true;
    rightEnabled = true;
  }
}

void playPong(boolean leftPress, boolean rightPress) {
  if (leftPress) {
    pressLeftPong();
  }
  if (rightPress) {
    pressRightPong();
  }
  long timeSinceLastUpdate = millis() - lastPongTime;
  if (timeSinceLastUpdate > updateInterval) {
    lastPongTime = millis();
    updatePong();
  }
}

void pongGameOver(String looser) {
  Serial.print(looser);
  Serial.println(" loose");
  //allOff();
  int victorX;
  if (looser == "Left") {
    victorX = 4;
  } else {
    victorX = 0;
  }
  drawSquare(victorX, 0, 255, 0, 0);
  delay(200);
  drawSquare(victorX, 0, 0, 255, 0);
  delay(200);
  drawSquare(victorX, 0, 0, 0, 255);
  delay(200);
  drawSquare(victorX, 0, 0, 0, 0);
  resetPong();
}

void resetPong() {
  pongEnabled = false;
  leftEnabled = true;
  rightEnabled = true;
  setRandomPongSpeed();
  setInitialPongX();
  updateInterval = initialUpdateInterval;
  allOff();
  Serial.println("What do you want to play?\n[Left]: Pong\n[Right]: Snake");
}

void printPong() {
  for (int i = 0; i < width ; i++) {
    if (pongX == i) {
      Serial.print("0");
    } else {
      Serial.print("X");
    }
  }
  Serial.println("");
}

void printLedPong() {
  for (int i = 0 ; i < width ; i++) {
    for (int j = 0 ; j < ledsInEachSquare ; j++) {
      if (i == pongX) {
        leds[(i * ledsInEachSquare) + j] = CRGB(255, 0, 0);
      } else {
        leds[(i * ledsInEachSquare) + j] = CRGB(0, 0, 0);
      }
    }
  }
  FastLED.show();
}
