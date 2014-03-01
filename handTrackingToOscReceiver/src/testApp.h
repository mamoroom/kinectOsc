#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

#define PORT 3000

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        ofxOscReceiver oscReceiver;
    
    private:
        const string oscLeftHandTrackAddr = "/handTrack/left";
        const string oscRightHandTrackAddr = "/handTrack/right";
        const string oscBothHandsTrackAddr = "/handTrack/both";
        int is_left_received;
        int is_right_received;
        int is_both_received;
		
};
