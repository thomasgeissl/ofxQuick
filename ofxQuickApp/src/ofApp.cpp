#include "ofApp.h"

ofApp::ofApp(){}
ofApp::ofApp(std::string path) : _jsFilePath(path){
}
void ofApp::setup()
{
	ofSetLogLevel(OF_LOG_VERBOSE);
	if(!_jsFilePath.empty()){
		_go.setup(_jsFilePath);
	}
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