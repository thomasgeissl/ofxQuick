#include "ofApp.h"

void ofApp::setup()
{
	ofSetFrameRate(120);
	ofSetLogLevel(OF_LOG_VERBOSE);
	ofxQuick::ofBindings::setup(_go._js._ctx);
	_go._js.setInt("testInt", 1);
	_go._js.setFloat("testFloat", 0.1);
	_go._js.setString("testString", "string value");
	_go.setup(ofToDataPath("go.js"));
}

void ofApp::exit()
{
}

void ofApp::update()
{
}

void ofApp::draw()
{
}

void ofApp::keyPressed(int key)
{
}

void ofApp::keyReleased(int key)
{
	switch(key){
		case ' ': {
			ofLogNotice() << _go._js.getInt("testInt");
			break;
		}
	}
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