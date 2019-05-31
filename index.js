var stdin = process.stdin;

const pong = require('./pong');
const snake = require('./snake');

function playSnake() {
  console.log('Starting snake');
}

async function handleInput() {
  stdin.setRawMode(true);
  stdin.resume();
  stdin.setEncoding('utf8');
  stdin.on('data', function(key) {
    if (pong.isEnabled()) {
      if (key == '\u001B\u005B\u0043') {
        pong.pressRight();
      } else if (key == '\u001B\u005B\u0044') {
        pong.pressLeft();
      }
    } else if (snake.isEnabled()) {
      if (key == '\u001B\u005B\u0043') {
        snake.pressRight();
      } else if (key == '\u001B\u005B\u0044') {
        snake.pressLeft();
      }
    } else if (key === '1') {
      pong.playPong();
    } else if (key === '2') {
      snake.playSnake();
    }
    if (key == '\u0003') {
      process.exit();
    } // ctrl-c
  });
}

async function startLedBookshelf() {
  console.log(`Select a game\nPong: [1]\nSnake: [2] `);
  handleInput();
}

startLedBookshelf();
