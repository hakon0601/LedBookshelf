async function handleInput(onLeft, onRight) {
  var stdin = process.stdin;
  stdin.setRawMode(true);
  stdin.resume();
  stdin.setEncoding('utf8');

  stdin.on('data', function(key) {
    if (key == '\u001B\u005B\u0041') {
      process.stdout.write('up');
    }
    if (key == '\u001B\u005B\u0043') {
      onRight();
    }
    if (key == '\u001B\u005B\u0042') {
      process.stdout.write('down');
    }
    if (key == '\u001B\u005B\u0044') {
      onLeft();
    }

    if (key == '\u0003') {
      process.exit();
    } // ctrl-c
  });
}

function onLeft() {
  console.log('Left pressed');
  direction = true;
  if (row.indexOf(1) === 0) {
    updateInterval = updateInterval - hardHitValue;
  } else if (row.indexOf(1) === 1) {
    updateInterval = updateInterval - softHitValue;
  } else {
    gameOver('Right');
  }
}

function onRight() {
  console.log('Right pressed');
  direction = false;
  if (row.indexOf(1) === 4) {
    updateInterval = updateInterval - hardHitValue;
  } else if (row.indexOf(1) === 3) {
    updateInterval = updateInterval - softHitValue;
  } else {
    gameOver('Left');
  }
}

function setDecreasingInterval(update) {
  setTimeout(function() {
    update();
    // updateInterval = Math.max(
    //   updateInterval - updateIntervalSpeed,
    //   minimumUpdateInterval
    // );
    setDecreasingInterval(update);
  }, updateInterval);
}

function update() {
  const indexOfBall = row.indexOf(1);
  if (direction) {
    if (indexOfBall === 4) {
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
  console.log(row, updateInterval);
}

function gameOver(winner) {
  console.log(`${winner} loose`);
  reset();
}

function reset() {
  direction = true;
  updateInterval = initialUpdateInterval;
  row = [1, 0, 0, 0, 0];
  console.log('reset');
}

let direction = true; // true = moving right
const initialUpdateInterval = 800;
const minimumUpdateInterval = 300;
let updateInterval = initialUpdateInterval;
const updateIntervalSpeed = 10;
let row = [1, 0, 0, 0, 0];
const hardHitValue = 50;
const softHitValue = 20;

function playPong() {
  handleInput(onLeft, onRight);
  setDecreasingInterval(update);
}

playPong();
