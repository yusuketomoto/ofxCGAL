//
//  ofSkinSurfaceApp.h
//  Created by Lukasz Karluk on 13/12/13.
//

#pragma once

#include "ofMain.h"
#include "ofxCGALSkinSurface.h"

class ofSkinSurfaceApp : public ofBaseApp {
public:
    
    void setup() {
        ofSetFrameRate(30);
        ofSetSphereResolution(10);
        
        bDrawMesh = true;
        bReset = true;
        bSubdiv = false;
        shrinkFactor = 0.5;
    }
    
    void update() {
        if(bReset == false) {
            return;
        }
        bReset = false;
        
        skinSurface.setSubdivEnable(bSubdiv);
        skinSurface.setShrinkFactor(shrinkFactor);
        skinSurface.clearPoints();
        
        int numOfPoints = 20;
        for(int i=0; i<numOfPoints; i++) {
            
            ofVec3f point;
            point.x = ofRandom(-200, 200);
            point.y = ofRandom(-200, 200);
            point.z = ofRandom(-200, 200);
            
            float radius = ofRandom(10, 100);

            skinSurface.addPoint(point, radius);
        }
        
        skinSurface.makeSkinSurfaceMesh();
    }
    
    void draw() {
        ofEnableDepthTest();
        
        cam.begin();
        
#ifdef TARGET_OSX
        glEnable(GL_POLYGON_OFFSET_FILL);
        glPolygonOffset(1.0, 1.0);
#endif
        
        if(bDrawMesh == true) {
            
            ofSetColor(ofColor::red);
            skinSurface.drawSkinSurfaceFaces();
            
            ofSetColor(ofColor::white);
            skinSurface.drawSkinSurfaceWireframe();
            
        } else {
            
            ofFill();
            ofSetColor(ofColor::red);
            skinSurface.drawPoints();
            
            ofNoFill();
            ofSetColor(ofColor::white);
            skinSurface.drawPoints();
        }
        
#ifdef TARGET_OSX
        glDisable(GL_POLYGON_OFFSET_FILL);
#endif
        
        cam.end();
        
        int x = 20;
        int y = 20;
        ofDrawBitmapString(ofToString(ofGetFrameRate()) + " fps", x, y);
        ofDrawBitmapString("Press 't' to toggle mesh", x, y+=40);
        ofDrawBitmapString("Press 'r' to reset points", x, y+=20);
        ofDrawBitmapString("Press 's' to toggle subdivision", x, y+=20);
        ofDrawBitmapString("Press '<' and '>' to change shrink factor = " + ofToString(shrinkFactor), x, y+=20);
    }
    
    void keyPressed(int key) {
        if(key == 't' || key == 'T') {
            bDrawMesh = !bDrawMesh;
        }
        if(key == 'r' || key == 'R') {
            bReset = true;
        }
        if(key == 's' || key == 'S') {
            skinSurface.setSubdivEnable((bSubdiv = !bSubdiv));
            skinSurface.makeSkinSurfaceMesh();
        }
        if(key == ',' || key == '<') {
            shrinkFactor = ofClamp(shrinkFactor - 0.1, 0.01, 0.99);
            skinSurface.setShrinkFactor(shrinkFactor);
            skinSurface.makeSkinSurfaceMesh();
        }
        if(key == '.' || key == '>') {
            shrinkFactor = ofClamp(shrinkFactor + 0.1, 0.01, 0.99);
            skinSurface.setShrinkFactor(shrinkFactor);
            skinSurface.makeSkinSurfaceMesh();
        }
    }
    
protected:
    
    ofEasyCam cam;
    
    ofxCGALSkinSurface skinSurface;
    
    bool bDrawMesh;
    bool bReset;
    bool bSubdiv;
    float shrinkFactor;
};
