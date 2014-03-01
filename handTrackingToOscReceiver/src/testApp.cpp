#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    oscReceiver.setup(PORT);
    ofBackground(250, 250, 250);

}

//--------------------------------------------------------------
void testApp::update(){
    
    while(oscReceiver.hasWaitingMessages()) {
        ofxOscMessage m;
        oscReceiver.getNextMessage(&m);
        
        is_left_received = ( m.getAddress() == oscLeftHandTrackAddr ) ? 1 : 0;
        is_right_received = ( m.getAddress() == oscRightHandTrackAddr ) ? 1 : 0;
        is_both_received = ( m.getAddress() == oscBothHandsTrackAddr ) ? 1 : 0;
        if (!is_left_received && !is_right_received && !is_both_received) {
            ofBackground(250, 250, 250);
        }
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    // draw color
    
    if (is_both_received) {
        ofBackground(255, 0, 0);
    } else if (is_left_received) {
        ofBackground(30, 30, 130);
    } else if (is_right_received) {
        ofBackground(40, 100, 40);
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
