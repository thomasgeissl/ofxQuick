#include "ofApp.h"

void ofApp::setup()
{
	ofSetFrameRate(120);
	ofSetLogLevel(OF_LOG_VERBOSE);

	_js.addListener(this);
	_js.setup(ofToDataPath("test.js"));
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

void ofApp::dragEvent(ofDragInfo dragInfo)
{
}

void ofApp::gotMessage(ofMessage msg)
{
}

void ofApp::onRegisterCustomBindings(){
	_js.registerMemberFunction("a", this, &ofApp::js_a);
	_js.registerMemberFunction("b", this, &ofApp::js_b);
}