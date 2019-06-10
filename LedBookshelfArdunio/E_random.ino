


int randColor = random(25);
long lastRandomTime = 0;
int initialUpdateIntervalRandom = 3000;
int minimumUpdateIntervalRandom = 50;
int updateIntervalRandom = initialUpdateIntervalRandom;

void playRandom() {
  long timeSinceLastUpdate = millis() - lastRandomTime;
  if (timeSinceLastUpdate > random(2000, 5000)) {
    lastRandomTime = millis();
    updateRandom();
  }
}

void updateRandom() {
  int howMany = random(25);
  for (int i = 0 ; i < howMany ; i++) {
    int randX = random(5);
    int randY = random(5);
    drawSquare(randX, randY, colors[randColor][0], colors[randColor][1], colors[randColor][2]);
  }
  randColor = random(25);
}
