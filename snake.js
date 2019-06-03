var enabled = false;
var stdin = process.stdin;
let direction = [1, 0]; // true = moving right
const initialUpdateInterval = 800;
const minimumUpdateInterval = 200;
let updateInterval = initialUpdateInterval;
const updateIntervalSpeed = 50;
const rowLength = 6;
const columnLength = 10;
let points = 0;
let matrix = createEmptyMatrix();
let snake = [[0, 0]];
let applePos = [3, 3];
let pressedButtonThisTurn = false;

function createEmptyMatrix() {
  var matrix = [];
  for (let i = 0; i < columnLength; i++) {
    matrix.push([]);
    for (let j = 0; j < rowLength; j++) {
      matrix[i].push('X');
    }
  }
  return matrix;
}

function decreaseUpdateInterval(value) {
  updateInterval = Math.max(updateInterval - value, minimumUpdateInterval);
  //   console.log('updateInterval', updateInterval);
}

function pressLeft() {
  if (!pressedButtonThisTurn) {
    if (direction[0] === 1) {
      direction = [0, -1];
    } else if (direction[0] === -1) {
      direction = [0, 1];
    } else if (direction[1] === 1) {
      direction = [1, 0];
    } else if (direction[1] === -1) {
      direction = [-1, 0];
    }
    pressedButtonThisTurn = true;
  }
}

function pressRight() {
  if (!pressedButtonThisTurn) {
    if (direction[0] === 1) {
      direction = [0, 1];
    } else if (direction[0] === -1) {
      direction = [0, -1];
    } else if (direction[1] === 1) {
      direction = [-1, 0];
    } else if (direction[1] === -1) {
      direction = [1, 0];
    }
    pressedButtonThisTurn = true;
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
  const headX = snake[snake.length - 1][0];
  const headY = snake[snake.length - 1][1];
  const newHeadX = headX + direction[0];
  const newHeadY = headY + direction[1];

  if (
    newHeadX === rowLength ||
    newHeadX === -1 ||
    newHeadY === columnLength ||
    newHeadY === -1 ||
    isPositionInSnake(newHeadX, newHeadY)
  ) {
    gameOver('You');
    return;
  } else if (applePos[0] === newHeadX && applePos[1] === newHeadY) {
    snake.push([newHeadX, newHeadY]);
    points = points + 1;
    applePos = createRandomApple();
    decreaseUpdateInterval(updateIntervalSpeed);
  } else {
    snake.push([newHeadX, newHeadY]);
    snake.shift();
  }
  matrix = createEmptyMatrix();
  snake.forEach(xy => {
    matrix[xy[1]][xy[0]] = 'o';
  });
  matrix[applePos[1]][applePos[0]] = 'a';
  pressedButtonThisTurn = false;
  printToConsole();
}

function getRandomInt(max) {
  return Math.floor(Math.random() * Math.floor(max));
}

function isPositionInSnake(x, y) {
  for (let i = 0; i < snake.length; i++) {
    if (snake[i][0] === x && snake[i][1] === y) {
      return true;
    }
  }
  return false;
}

function createRandomApple() {
  applePos = [getRandomInt(rowLength), getRandomInt(columnLength)];
  snake.forEach(xy => {
    if (xy[0] === applePos[0] && xy[1] === applePos[1]) {
      return createRandomApple();
    }
  });
  return applePos;
}

function printToConsole() {
  let outString = '';
  matrix.forEach(row => {
    row.forEach(pixel => {
      outString += pixel;
    });
    outString += '\n';
  });
  console.log(outString);
}

function gameOver(looser) {
  console.log(`\n${looser} loose`);
  console.log(`Select a game\nPong: [1]\nSnake: [2] `);
  reset();
}

function reset() {
  enabled = false;
  direction = [1, 0];
  updateInterval = initialUpdateInterval;
  matrix = createEmptyMatrix();
  snake = [[0, 0]];
  applePos = [3, 3];
  points = 0;
}

async function playSnake() {
  enabled = true;
  try {
    setDecreasingInterval(update);
  } catch (error) {
    console.error(error);
  }
}

function isEnabled() {
  return enabled;
}

module.exports = {
  playSnake,
  pressLeft,
  pressRight,
  isEnabled
};
