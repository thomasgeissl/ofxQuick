# ofxQuick

ofxQuick wraps quickjs, a light-weight, embeddable java script engine.

* ofxQuick::js is the js engine. it loads and evaluate js code, and provides
    * an interface to expose custom functions and variables to the js side
    * an interface to read javascript variables or call functions from the c++ side. 
* ofxQuick::gameObject listens to oF events and calls the handler functions implemented in js. 

## status
is is only a first test and far from being stable, expect the api to change quite a bit.

## TODOs
* oF core bindings with classes, e.g. new of.fbo()
* ofxAddon binding as js modules
* free pointers and clean up the api
* fix addon structure, move implementations to cpp files

