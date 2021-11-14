#pragma once

#include "ofMain.h"
#include "ofxQuick.h"

class ofApp : public ofBaseApp
{
public:
	void setup();
	void update();
	void draw();
	void exit();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	void onRegisterCustomBindings();

    JSValue js_a(JSContext *ctx, JSValueConst jsThis, int argc, JSValueConst *argv)
    {
		ofLogNotice() << "ofApp::js_a";
        return JS_UNDEFINED;
    }
    JSValue js_b(JSContext *ctx, JSValueConst jsThis, int argc, JSValueConst *argv)
    {
		ofLogNotice() << "ofApp::js_b";
        return JS_UNDEFINED;
    }

private:
ofxQuick::js _js;
};