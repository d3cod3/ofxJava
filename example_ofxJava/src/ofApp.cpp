#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(30);
    ofSetVerticalSync(true);
    ofSetWindowTitle("OF Render");

    jvm = new ofxJava();
    jvm->loadScript(ofToDataPath("MosaicProcessingClass.java"));
}

//--------------------------------------------------------------
void ofApp::update(){
    if(jvm->sys_status == 0 && !jvm->compiled){
        jvm->setup();
    }

    if(jvm->compiled){
        jvm->update();
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    if(jvm->compiled){
        jvm->draw();
    }
}

//--------------------------------------------------------------
void ofApp::exit(){
    jvm->closeJVM();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'r'){
        jvm->reload();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
