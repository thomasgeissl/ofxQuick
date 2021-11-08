// import * as std from "std";

let counter = 0;

a();
b();

function setup() {}
function update() {
  counter++;
  //   log();
}
function draw() {}
function foo(x, y) {
  return x + y;
}
function getCounter() {
  return counter;
}

function log() {
  console.log(counter);
  console.warn("this is a warning", counter);
  console.error("this is an error", counter);
}
