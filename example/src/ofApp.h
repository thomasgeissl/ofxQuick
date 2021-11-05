#pragma once

#include "ofMain.h"
#include "ofxQuickJs.h"

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

	int _magic;
	static JSValue js_memmberfunction_wrapper_magic(JSContext *ctx, JSValueConst jsThis, int argc, JSValueConst *argv, int magic){
		ofLogNotice() << "called wrapper function " << magic;
	}
    JSValue js_memberfunction(JSContext *ctx, JSValueConst jsThis, int argc, JSValueConst *argv)
    {
		ofLogNotice() << "js_memberfunction";
        return JS_UNDEFINED;
    }

private:
ofxQuickJs _js;
};