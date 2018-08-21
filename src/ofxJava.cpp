/*==============================================================================

    ofxJava: a java scripting interface & bindings for openFrameworks

    Copyright (c) 2018 Emanuele Mazza aka n3m3da <emanuelemazza@d3cod3.org>

    ofxJava is distributed under the MIT License.
    This gives everyone the freedoms to use ofxJava in any context:
    commercial or non-commercial, public or private, open or closed source.

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
    OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.

    See https://github.com/d3cod3/ofxJava for documentation

==============================================================================*/

#include "ofxJava.h"

//--------------------------------------------------------------
ofxJava::ofxJava(){
    mainFilePath        = ofToDataPath("");
    currentFilePath     = "";
}

//--------------------------------------------------------------
ofxJava::~ofxJava(){

}

//--------------------------------------------------------------
void ofxJava::loadJVM(){
    JavaVMInitArgs vm_args;
    JavaVMOption* options = new JavaVMOption[1];
    char start[100] = "-Djava.class.path=";
    options[0].optionString = strcat(start,mainFilePath.c_str());
    vm_args.version = JNI_VERSION_1_6;
    vm_args.nOptions = 1;
    vm_args.options = options;
    vm_args.ignoreUnrecognized = false;

    jint rc = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);
    if (rc != JNI_OK) {
        ofLog(OF_LOG_ERROR,"JVM INIT ERROR!");
    }else{
        ofLog(OF_LOG_NOTICE,"JVM load succeeded: Version %i",env->GetVersion());
    }
}

//--------------------------------------------------------------
void ofxJava::closeJVM(){
    jvm->DestroyJavaVM();
}

//--------------------------------------------------------------
void ofxJava::loadScript(string filepath){
    currentFilePath = filepath;
    compileScript(currentFilePath);

    setup();
}

//--------------------------------------------------------------
void ofxJava::compileScript(string filepath){
    ofFile file (filepath);
    if (file.exists()){
        string fileExtension = ofToUpper(file.getExtension());
        if(fileExtension == "JAVA") {
            string cmd = "javac "+currentFilePath;
            system(cmd.c_str());
        }
    }
}

//--------------------------------------------------------------
void ofxJava::setup(){

    jclass cls2 = env->FindClass("MosaicJavaClass");  // try to find the class

    if(cls2 == nullptr) {
        ofLog(OF_LOG_ERROR,"ERROR: class not found !");
    }else{
        //ofLog(OF_LOG_NOTICE,"Class MosaicJavaClass found");

        jmethodID constructor = env->GetMethodID(cls2, "<init>", "()V"); //this is for defaul c-tor
        jobject object = env->NewObject(cls2, constructor);

        jmethodID sid = env->GetMethodID(cls2, "setup", "()V"); // find method
        if(sid == nullptr){
            ofLog(OF_LOG_ERROR,"ERROR: method void setup() not found !");
        }else{
            //ofLog(OF_LOG_NOTICE,"setup() inited!");
            env->CallVoidMethod(object, sid); // call method
        }
    }
}

//--------------------------------------------------------------
void ofxJava::update(){

}

//--------------------------------------------------------------
void ofxJava::draw(){

}
