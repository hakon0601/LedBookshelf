

long frequencies[25];
long lastBlinked[25];
int blinkColors[25][3];
long blinkDurations[25];
long lastRandomFrequenciesTime = 0;

long updateIntervalRandomFrequencies = 60000 * 5;

void updateBlinkDurations() {
  for (int i = 0 ; i < 25 ; i++) {
    blinkDurations[i] = random(1000, 4000);
  }
}

void setupRandomFrequencies() {
  updateRandomFrequencies();
  clearLastBlinked();
  setRandomBlinkColors();
  updateBlinkDurations();
}

void updateRandomFrequencies() {
  for (int i = 0 ; i < 25 ; i++) {
    frequencies[i] = random(400, 1000);
  }
}

void clearLastBlinked() {
  long now = millis();
  for (int i = 0 ; i < 25 ; i++) {
    lastBlinked[i] = now;
  }
}

void setRandomBlinkColors() {
  for (int i = 0 ; i < 25 ; i++) {
    int colorIndex = random(25);
    for (int j = 0 ; j < 3 ; j++) {
      blinkColors[i][j] = colors[colorIndex][j];
    }
  }
}

void setFrequency(int i, int x, int y) {
  long now = millis();
  // Turn on
  if (now - lastBlinked[i] > frequencies[i] + blinkDurations[i]) {
    lastBlinked[i] = millis();
  }

  if (now - lastBlinked[i] < frequencies[i]) {
    drawSquare(x, y, 0, 0, 0);
  } else {
    drawSquare(x, y, blinkColors[i][0], blinkColors[i][1], blinkColors[i][2]);
  }
}


void playRandomFrequencies() {
  if (millis() - lastRandomFrequenciesTime > updateIntervalRandomFrequencies) {
    lastRandomFrequenciesTime = millis();
    updateRandomFrequencies();
    clearLastBlinked();
  }
  for (int i = 0 ; i < 5 ; i++) {
    for (int j = 0 ; j < 5 ; j++) {
      setFrequency(i * 5 + j, i, j);
    }
  }
}
