var enabled = false;
let direction = true; // true = moving right
const initialUpdateInterval = 800;
const minimumUpdateInterval = 200;
let updateInterval = initialUpdateInterval;
const updateIntervalSpeed = 10;
const rowLength = 6;
let row = new Array(rowLength).fill(0);
row[0] = 1;
const hardHitValue = 50;
const softHitValue = 20;

function decreaseUpdateInterval(value) {
  updateInterval = Math.max(updateInterval - value, minimumUpdateInterval);
  //   console.log('updateInterval', updateInterval);
}

function pressLeft() {
  //   console.log('Left pressed');
  direction = true;
  if (row.indexOf(1) === 0) {
    decreaseUpdateInterval(hardHitValue);
    updateInterval = updateInterval - hardHitValue;
  } else if (row.indexOf(1) === 1) {
    decreaseUpdateInterval(softHitValue);
  } else {
    gameOver('Left');
  }
}

function pressRight() {
  //   console.log('Right pressed');
  direction = false;
  if (row.indexOf(1) === row.length - 1) {
    decreaseUpdateInterval(hardHitValue);
  } else if (row.indexOf(1) === row.length - 2) {
    decreaseUpdateInterval(softHitValue);
  } else {
    gameOver('Right');
  }
}

function setDecreasingInterval(update) {
  if (enabled) {
    update();
    setTimeout(function() {
      setDecreasingInterval(update);
    }, updateInterval);
  }
}

function update() {
  const indexOfBall = row.indexOf(1);
  if (direction) {
    if (indexOfBall === row.length - 1) {
      gameOver('Right');
    } else {
      row[indexOfBall] = 0;
      row[indexOfBall + 1] = 1;
    }
  } else {
    if (indexOfBall === 0) {
      gameOver('Left');
    } else {
      row[indexOfBall] = 0;
      row[indexOfBall - 1] = 1;
    }
  }
  if (isEnabled()) printRowToConsole();
}

function printRowToConsole() {
  process.stdout.clearLine();
  process.stdout.cursorTo(0);
  process.stdout.write(row.toString());
}

function gameOver(looser) {
  console.log(`\n${looser} loose`);
  reset();
}

function reset() {
  enabled = false;
  direction = Math.random() >= 0.5;
  updateInterval = initialUpdateInterval;
  row = new Array(rowLength).fill(0);
  if (direction) {
    row[0] = 1;
  } else {
    row[row.length - 1] = 1;
  }
}

async function playPong() {
  enabled = true;
  setDecreasingInterval(update);
}

function isEnabled() {
  return enabled;
}

module.exports = {
  playPong,
  pressLeft,
  pressRight,
  isEnabled
};
