#include "ofMain.h"
#include "ofApp.h"

// for default console
//========================================================================
int main() {
	ofSetupOpenGL(640, 480, OF_WINDOW);			// 가로 640, 세로 480의 window창 생성
	
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new ofApp());
}
