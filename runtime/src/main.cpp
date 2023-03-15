#include "ofMain.h"
#include "ofApp.h"

int main(int argc, char *argv[]){
	ofSetupOpenGL(1024, 768, OF_WINDOW);
	if(argc > 1){
		ofRunApp(new ofApp(argv[1]));
	}else{
		ofLogError() << "please provide an absolute path to the js file you want to run. \n\nruntime /path/to/file\n\n thanks. bye.";
		return -1;
	}
	return 0;
}
