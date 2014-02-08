#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    kinect.setup();
    
    kinect.addImageGenerator();
    kinect.addDepthGenerator();
    kinect.addUserGenerator();
    kinect.setMaxNumUsers(2);
    kinect.setUseMaskTextureAllUsers(true);
    
    kinect.start();

}

//--------------------------------------------------------------
void testApp::update(){
    kinect.update();
}

//--------------------------------------------------------------
void testApp::draw(){
    ofSetColor(255, 255, 255);
    kinect.drawDebug();
}

//--------------------------------------------------------------
void testApp::exit(){
    kinect.stop();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

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