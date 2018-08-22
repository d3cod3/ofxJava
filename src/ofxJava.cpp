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

    compiled            = true;
    sys_status          = -1;
}

//--------------------------------------------------------------
ofxJava::~ofxJava(){

}

//--------------------------------------------------------------
void ofxJava::loadScript(string filepath){
    currentFilePath = filepath;
    compileScript(currentFilePath);
}

//--------------------------------------------------------------
void ofxJava::compileScript(string filepath){
    ofFile file (filepath);
    if (file.exists()){
        string fileExtension = ofToUpper(file.getExtension());
        if(fileExtension == "JAVA") {
            string libpath = "'.:"+file.getEnclosingDirectory()+"core.jar' ";
            string cmd = "javac -cp "+libpath+currentFilePath;
            compiled = false;
            sys_status = system(cmd.c_str());
        }
    }
}

//--------------------------------------------------------------
void ofxJava::setup(){
    ofFile file (currentFilePath);

    string className = file.getFileName();
    string cmd = "cd "+file.getEnclosingDirectory()+" && java -cp core.jar:. "+className.substr(0,className.size()-5)+" &";
    //ofLog(OF_LOG_NOTICE,"%s",cmd.c_str());
    system(cmd.c_str());
}
