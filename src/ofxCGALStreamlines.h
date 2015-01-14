//
//  ofxCGALStreamlines.h
//  example
//
//  Created by Lukasz Karluk on 12/01/2015.
//
//

#pragma once

#include "ofMain.h"

//-------------------------------------------------------------
class ofxCGALVectorField {
    
public:
    
    ofxCGALVectorField() {
        setup(0, 0);
    }
    
    void setup(int resX, int resY) {
        width = resX;
        height = resY;
        values.clear();
        values.resize(width * height, ofVec2f());
    }
    
    unsigned int getWidth() const {
        return width;
    }
    
    unsigned int getHeight() const {
        return height;
    }

    void setValueAt(int x, int y, const ofVec2f & value) {
        if(width == 0 || height == 0) {
            return;
        }
        int i = y * width + x;
        if(i > values.size()-1) {
            return;
        }
        values[i].set(value);
    }
    
    const ofVec2f & getValueAt(int x, int y) const {
        int i = y * width + x;
        if(i > values.size()-1) {
            return;
        }
        return values[i];
    }
    
    int width;
    int height;
    vector<ofVec2f> values;
};

//-------------------------------------------------------------
class ofxCGALStreamlines {
    
public:
    ofxCGALStreamlines();
    ~ofxCGALStreamlines();
    
    void setSeparationDistance(float value);
    float getSeparationDistance();
    
    void setSaturationRatio(float value);
    float getSaturationRatio();
    
    const vector<ofPolyline> & getPolys();
    
    void calc(const ofxCGALVectorField & vectorField);
    
    void draw();
    void drawBorder();
    void drawStreamlines();
    
    int width;
    int height;
    double separatingDistance;
    double saturationRatio;
    vector<ofPolyline> streamlines;
};