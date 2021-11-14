// import * as std from "std";

let counter = 0;

function setup() {}
function update() {
  counter++;
  // a();
  // b();
  // log();
}
function draw() {}
function getCounter() {
  return counter;
}

function log() {
  console.log(counter);
  console.warn("this is a warning", counter);
  console.error("this is an error", counter);
}
