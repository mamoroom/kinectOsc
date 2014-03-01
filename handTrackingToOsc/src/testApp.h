#pragma once

#include "ofxOpenNI.h"
#include "ofMain.h"
#include "ofxOsc.h"

#define HOST "localhost"
#define PORT 3000

class testApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
        void exit();
        void _draw(float x, float y, float w, float h);
        void oscSend(string addr);
        void setSquareColor(int hit_left, int hit_right, int* rgb);
    
        ofxOpenNI kinect;
        ofxOscSender oscSender;
        ofTrueTypeFont verdana;
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    private:
        const string oscLeftHandTrackAddr = "/handTrack/left";
        const string oscRightHandTrackAddr = "/handTrack/right";
        const string oscBothHandsTrackAddr = "/handTrack/both";
        bool  is_both_hands_tracked;
};
