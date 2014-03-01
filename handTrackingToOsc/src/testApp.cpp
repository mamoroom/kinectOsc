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
    
    // setup the hand generator
    kinect.addHandsGenerator();
    
    // add all focus gestures (ie., wave, click, raise arm)
    kinect.addAllHandFocusGestures();
    
    // or you can add them one at a time
    //vector<string> gestureNames = kinect.getAvailableGestures(); // you can use this to get a list of gestures
    // prints to console and/or you can use the returned vector
    //kinect.addHandFocusGesture("Wave");
    
    kinect.setMaxNumHands(4);
    
    //osc
    oscSender.setup(HOST, PORT);
    
    // font
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
    int numHands = 0;
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
    if(kinect.isUserOn()) kinect.drawSkeletons();
    ofTranslate(kinect.getWidth(), 0.0f);
    //if(kinect.isImageOn() || kinect.isInfraOn()) drawImage();
    if(kinect.isUserOn()){
        //if(g_bIsImageOn || g_bIsInfraOn) ofTranslate(-getWidth(), 0.0f);
        for (int i = 0; i < kinect.getNumTrackedUsers(); i++) {
            // get number of current hands
            if(kinect.isHandsOn()) {
                kinect.drawHands();
                numHands = kinect.getNumTrackedHands();
            }
    
            ofxOpenNIUser & user = kinect.getTrackedUser(i);
            user.drawMask();
            user.drawSkeleton();
            ofSetColor(255, 255, 0);
            ofDrawBitmapString(user.getDebugInfo(), -kinect.getWidth(), kinect.getHeight() + (i+1) * 10);
        }
    }
    // circle
    ofSetColor(255, 255, 0);
    int radius = 250;
    ofNoFill();
    ofCircle(kinect.getWidth()/2, kinect.getHeight()/2, radius);
    
    ofPopMatrix();
    
    ofPushMatrix();
    
    // square
    int w_square = 100;
    int h_square = 100;
    int x_left_square = kinect.getWidth()*3/2 - ((radius / sqrt(2)) + w_square/2);
    int x_right_square = kinect.getWidth()*3/2 + ((radius / sqrt(2)) - w_square/2);
    int y_square = kinect.getHeight()/2 - ((radius / sqrt(2)) + h_square/2);
    int hit_left = 0;
    int hit_right = 0;
    
    if(kinect.isHandsOn()) {
        // iterate through users
        for (int i = 0; i < numHands; i++){
        
            // get a reference to this user
            ofxOpenNIHand & hand = kinect.getTrackedHand(i);
        
            // get hand position
            ofPoint & handPosition = hand.getPosition();
            // do something with the positions like:
        
            // draw a rect at the position (don't confuse this with the debug draw which shows circles!!)
            ofSetColor(255,0,0);
            ofRect(handPosition.x, handPosition.y, 10, 10);
            
            // fill square
            if (handPosition.x <= x_left_square - kinect.getWidth() + w_square && handPosition.y <= y_square + h_square) {
                //hitFlag[i][0] = 1;
                hit_left++;
            } else {
                //hitFlag[i][0] = 0;
            }
            
            if (handPosition.x >= x_right_square - kinect.getWidth() && handPosition.y <= y_square + h_square) {
                //hitFlag[0][i] = 1;
                hit_right++;
            } else {
                //hitFlag[0][i] = 0;
            }
        }
    }
    
    // square draw
    int left_rgb[3] = {30, 30, 130};
    setSquareColor(hit_left, hit_right, left_rgb);
    ofSetColor(left_rgb[0], left_rgb[1], left_rgb[2]);
    if (hit_left > 0) {
        ofFill();
        oscSend(oscLeftHandTrackAddr);
    } else {
        ofSetColor(255, 255, 0);
        ofNoFill();
    }
    ofRect(x_left_square, y_square, w_square, h_square);
    
    int right_rgb[3] = {40, 100, 40};
    setSquareColor(hit_left, hit_right, right_rgb);
    ofSetColor(right_rgb[0], right_rgb[1], right_rgb[2]);
    if (hit_right > 0) {
        ofFill();
        oscSend(oscRightHandTrackAddr);
    } else {
        ofSetColor(255, 255, 0);
        ofNoFill();
    }
    ofRect(x_right_square, y_square, w_square, h_square);
    if (is_both_hands_tracked) {
        oscSend(oscBothHandsTrackAddr);
    }
    ofPopMatrix();
    
    ofPopStyle();
}

void testApp::setSquareColor(int hit_left, int hit_right, int* rgb) {
    if (hit_left && hit_right) {
        *rgb = 255;
        *(rgb+1) = 0;
        *(rgb+2) = 0;
        is_both_hands_tracked = true;
    } else {
        is_both_hands_tracked = false;
    }
}
//--------------------------------------------------------------
void testApp::oscSend(string addr){
    ofxOscMessage m;
    
    m.setAddress(addr);
    oscSender.sendMessage(m);
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