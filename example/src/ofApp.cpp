#include "ofApp.h"

void ofApp::setup()
{
	ofSetFrameRate(120);
	ofSetLogLevel(OF_LOG_VERBOSE);
	_js.setup("test.js");
	// _js.evaluate("function foo(x, y) { return x + y; }");
	_js.test();
	_js.call("setup");
}

void ofApp::exit()
{
}

void ofApp::update()
{
	_js.update();
	_js.call("update");
	// ofLogNotice() << _js.callInt("getCounter");
}

void ofApp::draw()
{
	_js.draw();
	_js.call("draw");
}

void ofApp::keyPressed(int key)
{
}

void ofApp::keyReleased(int key)
{
}

void ofApp::mouseMoved(int x, int y)
{
}

void ofApp::mouseDragged(int x, int y, int button)
{
}

void ofApp::mousePressed(int x, int y, int button)
{
}

void ofApp::mouseReleased(int x, int y, int button)
{
}

void ofApp::mouseEntered(int x, int y)
{
}

void ofApp::mouseExited(int x, int y)
{
}

void ofApp::windowResized(int w, int h)
{
}

void ofApp::gotMessage(ofMessage msg)
{
}

void ofApp::dragEvent(ofDragInfo dragInfo)
{
}
