//
//  ofxCGALSkinSurface.h
//  Created by Lukasz Karluk on 17/12/2013.
//

#pragma once

#include "ofMain.h"

struct ofxCGALSkinSurfacePoint {
    ofxCGALSkinSurfacePoint(ofVec3f & p, float r) {
        point = p;
        radius = r;
    }
    ofVec3f point;
    float radius;
};

class ofxCGALSkinSurface {
    
public:
    ofxCGALSkinSurface();
    ~ofxCGALSkinSurface();
    
    void setSubdivEnable(bool enable);
    bool getSubdivEnable();
    void setShrinkFactor(float value);
    float getShrinkFactor();

    void clearPoints();
    void addPoint(ofVec3f & point, float radius);
    void addPoints(vector<ofxCGALSkinSurfacePoint> & points);
    ofMesh & makeSkinSurfaceMesh();
    
    void drawPoints();
    void drawSkinSurfaceFaces();
    void drawSkinSurfaceWireframe();
    
    vector<ofxCGALSkinSurfacePoint> points;
    ofMesh mesh;
    float shrinkFactor;
    bool bSubdiv;
};