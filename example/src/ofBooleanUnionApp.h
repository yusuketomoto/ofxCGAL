//
//  ofBooleanUnionApp.h
//  Created by Lukasz Karluk on 13/12/13.
//

#pragma once

#include "ofMain.h"
#include "ofxCGALBooleanOp.h"

class ofBooleanUnionApp : public ofBaseApp {
public:
    
    void setup() {
        ofSetFrameRate(30);
        ofSetSphereResolution(10);
        
        bShowResult = false;
        
        float radius = 200;
        mesh1.load("sphere.ply");
        mesh2.load("sphere.ply");
        
        ofMatrix4x4 mat1, mat2;
        mat1.makeTranslationMatrix(ofVec3f(-radius * 0.7, 0, 0));
        mat2.makeTranslationMatrix(ofVec3f( radius * 0.7, 0, 0));
        
        vector<ofVec3f> & verts1 = mesh1.getVertices();
        vector<ofVec3f> & verts2 = mesh2.getVertices();
        int numOfVertices = verts1.size();
        
        for(int i=0; i<numOfVertices; i++) {
            ofVec3f & vert1 = verts1[i];
            ofVec3f & vert2 = verts2[i];
            
            vert1.set(mat1.preMult(vert1));
            vert2.set(mat2.preMult(vert2));
        }
    }
    
    void update() {
        //
    }
    
    void draw() {
        cam.begin();
        
        if(bShowResult == true) {
            ofSetColor(ofColor::white);
            meshResult.drawWireframe();
        } else {
            ofSetColor(ofColor::red);
            mesh1.drawWireframe();
            mesh2.drawWireframe();
        }
        
        ofSetColor(ofColor::white);
        
        cam.end();
        
        int x = 20;
        int y = 20;
        ofDrawBitmapString("Press '1' for OF_BOOLEAN_OPERATOR_UNION", x, y);
        ofDrawBitmapString("Press '2' for OF_BOOLEAN_OPERATOR_DIFFERENCE", x, y+=20);
        ofDrawBitmapString("Press '3' for OF_BOOLEAN_OPERATOR_INTERSECTION", x, y+=20);
        ofDrawBitmapString("Press '4' for OF_BOOLEAN_OPERATOR_COMPLEMENT", x, y+=20);
        
        x = ofGetWidth() - 100;
        y = 20;
        ofDrawBitmapString(ofToString(ofGetFrameRate()) + " fps", x, y);
    }
    
    void keyPressed(int key) {
        
        bShowResult = true;
        
        if(key == '1') {
            meshResult = ofxCGALBooleanOp::runOp(mesh1, mesh2, OF_BOOLEAN_OPERATOR_UNION);
        } else if(key == '2') {
            meshResult = ofxCGALBooleanOp::runOp(mesh1, mesh2, OF_BOOLEAN_OPERATOR_DIFFERENCE);
        } else if(key == '3') {
            meshResult = ofxCGALBooleanOp::runOp(mesh1, mesh2, OF_BOOLEAN_OPERATOR_INTERSECTION);
        } else if(key == '4') {
            meshResult = ofxCGALBooleanOp::runOp(mesh1, mesh2, OF_BOOLEAN_OPERATOR_COMPLEMENT);
        } else {
            bShowResult = false;
        }
    }
    
protected:
    
    ofEasyCam cam;
    ofMesh mesh1;
    ofMesh mesh2;
    ofMesh meshResult;
    
    bool bShowResult;
};
