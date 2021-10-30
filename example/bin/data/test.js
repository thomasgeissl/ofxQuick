let counter = 0;
function setup() {}
function update() {
  counter++;
  console.log(counter);
  console.warn("this is a warning", counter);
  console.error("this is an error", counter);
}
function draw() {}
function foo(x, y) {
  return x + y;
}
function getCounter() {
  return counter;
}
