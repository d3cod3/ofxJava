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

    loadedTxtInfo       = false;

    compiled            = true;
    sys_status          = -1;
}

//--------------------------------------------------------------
ofxJava::~ofxJava(){

}

//--------------------------------------------------------------
void ofxJava::loadScript(string filepath){
    currentFilePath = filepath;

    ofFile file (currentFilePath);
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
void ofxJava::closeJVM(){
    string killCmd = "kill -9 "+ofToString(pid);
    system(killCmd.c_str());
}

//--------------------------------------------------------------
void ofxJava::reload(){
    closeJVM();
    sys_status          = -1;
    loadScript(currentFilePath);
}

//--------------------------------------------------------------
void ofxJava::setup(){
    currentFile.open(currentFilePath);

    string className = currentFile.getFileName();
    string cmd = "cd "+currentFile.getEnclosingDirectory()+" && java -cp core.jar:. "+className.substr(0,className.size()-5)+" &";
    sys_status = system(cmd.c_str());

    string getPidCmd = "ps aux | grep '"+className.substr(0,className.size()-5)+"' | head -n 2 | tail -1 | awk '{print $2}'";
    string lastPID = execCmd(getPidCmd.c_str());

    pid = ofToInt(lastPID);

    compiled = true;

}

//--------------------------------------------------------------
void ofxJava::update(){
    string absolutePath = currentFile.getAbsolutePath();
    string className = currentFile.getFileName();
    string binaryData = className.substr(0,className.size()-5)+".dat";
    bufferFile.open(binaryData);

    if(!loadedTxtInfo){
        loadedTxtInfo = true;
        renderReference.load(absolutePath.substr(0,absolutePath.size()-5)+".png");
    }

    if(bufferFile.exists() && bufferFile.canRead() && loadedTxtInfo){
        ofBuffer buffer = bufferFile.readToBuffer();
        if(buffer.getData() != nullptr){
            renderTexture.loadData((uint8_t*)buffer.getData(),static_cast<int>(renderReference.getWidth()),static_cast<int>(renderReference.getHeight()),GL_RGB);
        }
    }
}

//--------------------------------------------------------------
void ofxJava::draw(){
    ofSetColor(255);
    if(renderTexture.isAllocated()){
        renderTexture.draw(0,0);
    }
}

//--------------------------------------------------------------
string  ofxJava::execCmd(const char* cmd){
    char buffer[128];
    string result = "";
#ifdef TARGET_LINUX
    FILE* pipe = popen(cmd, "r");
#elif defined(TARGET_OSX)
    FILE* pipe = popen(cmd, "r");
#elif defined(TARGET_WIN32)
    FILE* pipe = _popen(cmd, "r");
#endif

    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (!feof(pipe)) {
            if (fgets(buffer, 128, pipe) != NULL)
                result += buffer;
        }
    } catch (...) {
#ifdef TARGET_LINUX
        pclose(pipe);
#elif defined(TARGET_OSX)
        pclose(pipe);
#elif defined(TARGET_WIN32)
        _pclose(pipe);
#endif
        throw;
    }
#ifdef TARGET_LINUX
    pclose(pipe);
#elif defined(TARGET_OSX)
    pclose(pipe);
#elif defined(TARGET_WIN32)
    _pclose(pipe);
#endif
    return result;
}
