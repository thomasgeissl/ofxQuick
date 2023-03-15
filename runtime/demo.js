// import * as std from "std";

let x = 0;
let y = 0;
let width = 200;
let height = 200;
let mousePressed = false;
function setup() {
  console.log("js -> setup");
  of.setWindowTitle("demo");
  of.setClipboardString("js -> setup");
  of.setFrameRate(60);
  of.background(32, 32, 32);
}

function update() {
//   console.log("js -> update");
  // console.log(of.getFrameRate());
//   x = (x + 1) % of.getWidth();
//   y = (y + 1) % of.getHeight();
}

function draw() {
//   console.log("js -> draw");
  const frameNum = of.getFrameNum();
//   of.setColor(255, 255, 0);
  of.setColor(255-frameNum%255, 255, frameNum%255);
//   console.log(of.getWidth());
  of.drawRectangle(
    of.getWidth() / 2 - height / 2,
    of.getHeight() / 2 - height / 2,
    height,
    height
  );
}
function exit() {
  console.log("js -> exit");
}

function keyPressed(key) {
  console.log(`js -> key pressed - ${key}`);
}

function keyReleased(key) {
  console.log(`js -> key released - ${key}`);
  switch (key) {
    case "f": {
      of.toggleFullscreen();
      break;
    }
    // case "t": {
    //   // TODO: fix timeout, or implement it in js.h
    //   std.setTimeout(() => {
    //     console.log("timeout after 5s");
    //   }, 5000);
    //   break;
    // }
  }
  testInt++;
}

function mouseMoved(x, y) {
  // console.log(`js -> mouse moved - (${x}, ${y})`);
}

function mouseDragged(x, y) {
  console.log(`js -> mouse dragged - (${x}, ${y})`);
}

function mousePressed(x, y, button) {
  // console.log(`js -> mouse pressed - ((${x}, ${y}), ${button})`);
  mousePressed = true;
  height = 100;
  width = 100;
}

function mouseReleased(x, y, button) {
  // console.log(`js -> mouse released - ((${x}, ${y}), ${button})`);
  mousePressed = false;
  height = 200;
  width = 200;
}

function mouseEntered(x, y) {
  console.log(`js -> mouse entered - (${x}, ${y})`);
}

function mouseExited(x, y) {
  console.log(`js -> mouse exited - (${x}, ${y})`);
}

function windowResized(width, height) {
  console.log(`js -> windowResized (${width}, ${height})`);
}

function dragEvent(x, y, files) {
  console.log(`js -> dragEvent (${x}, ${y})`);
  files.forEach((file) => {
    console.log(file);
  });
}
