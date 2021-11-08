// import * as std from "std";

function setup() {
  console.log("js -> setup");
}

function update() {
  // console.log("js -> update");
}

function draw() {
  // console.log("js -> draw");
}
function exit() {
  console.log("js -> exit");
}

function keyPressed(key) {
  console.log(`js -> key pressed - ${key}`);
}

function keyReleased(key) {
  console.log(`js -> key released - ${key}`);
}

function mouseMoved(x, y) {
  // console.log(`js -> mouse moved - (${x}, ${y})`);
}

function mouseDragged(x, y) {
  console.log(`js -> mouse dragged - (${x}, ${y})`);
}

function mousePressed(x, y, button) {
  console.log(`js -> mouse pressed - ((${x}, ${y}), ${button})`);
}

function mouseReleased(x, y, button) {
  console.log(`js -> mouse released - ((${x}, ${y}), ${button})`);
}

function mouseEntered(x, y) {
  console.log(`js -> mouse entered - (${x}, ${y})`);
}

function mouseEntered(x, y) {
  console.log(`js -> mouse exited - (${x}, ${y})`);
}

function windowResized(width, height) {
  console.log(`js -> windowResized (${width}, ${height})`);
}
