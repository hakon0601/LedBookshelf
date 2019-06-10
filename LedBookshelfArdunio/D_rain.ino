

bool shoudDecreaseUpdateIntervalRain = false;
bool shouldRandomizeColors = false;

int rainMatrix[5][5][3];
long lastRainTime = 0;
int initialUpdateIntervalRain = 800;
int minimumUpdateIntervalRain = 50;
int updateIntervalRain = initialUpdateIntervalRain;
int rainColor[3] = {40, 20, 210};
int blankColor[3] = {0, 0, 0};

void decreaseUpdateIntervalRain(int value) {
  if (updateIntervalRain - value < minimumUpdateIntervalRain) {
    updateIntervalRain = minimumUpdateIntervalRain;
  } else {
    updateIntervalRain = updateIntervalRain - value;
  }
}

void resetRainMatrix() {
  for (int i = 0 ; i < 5 ; i++) {
    for (int j = 0 ; j < 5 ; j++) {
      for (int k = 0 ; k < 3 ; k++) {
        rainMatrix[i][j][k] = blankColor[k];
      }
    }
  }
}

void updateRain() {
  // Move row 0-3 to 1-4
  //Serial.println("before");
  //printRain();
  for (int i = height - 1 ; i > 0 ; i--) {
    for (int j = 0 ; j < width ; j++) {
      for (int k = 0 ; k < 3 ; k++) {
        rainMatrix[i][j][k] = rainMatrix[i - 1][j][k];
      }
    }
  }
  
  // zeros in row 0
  for (int l = 0 ; l < width ; l++) {
    for (int m = 0 ; m < 3 ; m++) {
      rainMatrix[0][l][m] = blankColor[m];
    }
  }
  if (shoudDecreaseUpdateIntervalRain) {
    decreaseUpdateIntervalRain(20);
  }
  //int shouldRain = random(2);
  int shouldRain = 1;
  if (shouldRain == 1) {
    int rainAt = random(width);
    for (int p = 0 ; p < 3 ; p++) {
      if (shouldRandomizeColors) {
        rainMatrix[0][rainAt][p] = random(256);
      } else {
        rainMatrix[0][rainAt][p] = rainColor[p];
      }
    }

    printRain();
    printLedRain();
  }
}

void playRain() {
  long timeSinceLastUpdate = millis() - lastRainTime;
  if (timeSinceLastUpdate > updateIntervalRain) {
    lastRainTime = millis();
    updateRain();
  }
}

void printRain() {
  for (int i = 0; i < height ; i++) {
    for (int j = 0; j < width ; j++) {
      String s = "X";
      for (int k = 0 ; k < 3 ; k++) {
        if (rainMatrix[i][j][k] != blankColor[k]) {
          s = "r";
        }
      }
      Serial.print(s);
    }
    Serial.println("");
  }
  Serial.println("");
}

void printLedRain() {
  for (int i = 0 ; i < height ; i++) {
    for (int j = 0 ; j < width ; j++) {
      drawSquare(j, i, rainMatrix[i][j][0], rainMatrix[i][j][1], rainMatrix[i][j][2]);
      /*
        if (rainMatrix[i][j] == 1) {
        drawSquare(j, i, 255, 0, 0);
        } else {
        drawSquare(j, i, 0, 0, 255);
        }
      */

    }
  }
}
