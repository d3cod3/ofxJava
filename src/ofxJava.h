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

#pragma once

#include "ofMain.h"

class ofxJava {
    
public:

    ofxJava();
    ~ofxJava();


    void    loadScript(string filepath);
    void    reload();
    void    closeJVM();

    void    setup();
    void    update(ofBuffer &dataIn, ofBuffer &dataOut);
    void    draw();

    string  execCmd(const char* cmd);

    bool                    compiled;
    bool                    loadedTxtInfo;
    int                     sys_status;
    ofFile                  currentFile;
    string                  mainFilePath;
    string                  currentFilePath;
    string                  actualClassName;

    ofFile                  bufferFile;
    ofImage                 *renderReference;
    ofTexture               *renderTexture;
    ofBuffer                renderBuffer;

    size_t                  resetTime;
    
private:
    
    FILE    *cmdf;
    pid_t   pid;
    
};
