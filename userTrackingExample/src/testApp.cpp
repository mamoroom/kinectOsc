#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    kinect.setup();
    kinect.addImageGenerator();
    kinect.addDepthGenerator();
    kinect.setRegister(true);
    kinect.setMirror(true);
    kinect.addUserGenerator();
    kinect.start();
    
    // set properties for all user masks and point clouds
    kinect.setUseMaskTextureAllUsers(true); // this turns on mask pixels internally AND creates mask textures efficiently
    verdana.loadFont(ofToDataPath("verdana.ttf"), 24);

}

//--------------------------------------------------------------
void testApp::update(){
    kinect.update();
}

//--------------------------------------------------------------
void testApp::draw(){
    // white
    ofSetColor(255, 255, 255);
    
    // draw depth, skeleton
    ofPushMatrix();
    _draw(0.0f, 0.0f, -1.0f, -1.0f);
    ofPopMatrix();
    
    // draw info of camera
    ofSetColor(0, 255, 0);
	string msg = " MILLIS: " + ofToString(ofGetElapsedTimeMillis()) + " FPS: " + ofToString(ofGetFrameRate());
	verdana.drawString(msg, 20, ofGetHeight() - 26);
}

void testApp::_draw(float x, float y, float w, float h) {
    //ofxOpenNIScopedLock scopedLock(bIsThreaded, mutex);
	//if(!bIsContextReady) return;
    
    int generatorCount = kinect.isDepthOn() + kinect.isImageOn() + kinect.isInfraOn();
    float fullWidth = kinect.getWidth() * generatorCount;
    float fullHeight = kinect.getHeight();
    
    if(w == -1.0f && h == -1.0f){
       w = fullWidth;
       h = fullHeight;
    }
    
    ofPushStyle();
    
    ofPushMatrix();
    ofTranslate(x, y);
    ofScale(w / (kinect.getWidth() * generatorCount), h / kinect.getHeight());
    //ofTranslate(ofGetWidth()/2-kinect.getWidth()/2, ofGetHeight()/2-kinect.getHeight()/2, 0);
    
    if(kinect.isDepthOn()) kinect.drawDepth();
    if(kinect.isHandsOn()) kinect.drawHands();
    if(kinect.isUserOn()) kinect.drawSkeletons();
    ofTranslate(kinect.getWidth(), 0.0f);
    //if(kinect.isImageOn() || kinect.isInfraOn()) drawImage();
    if(kinect.isUserOn()){
        //if(g_bIsImageOn || g_bIsInfraOn) ofTranslate(-getWidth(), 0.0f);
        for (int i = 0; i < kinect.getNumTrackedUsers(); i++) {
            ofxOpenNIUser & user = kinect.getTrackedUser(i);
            user.drawMask();
            user.drawSkeleton();
            ofSetColor(255, 255, 0);
            ofDrawBitmapString(user.getDebugInfo(), -kinect.getWidth(), kinect.getHeight() + (i+1) * 10);
        }
    }
    ofPopMatrix();
    ofPopStyle();
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