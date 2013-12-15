//
//  ofBooleanUnionApp.h
//  Created by Lukasz Karluk on 13/12/13.
//

#include "ofMain.h"
#include "ofxCGAL.h"

using namespace ofxCGAL;

class ofBooleanUnionApp : public ofBaseApp {
public:
    
    void setup() {
        ofSetFrameRate(30);
        ofSetSphereResolution(10);
        
        float radius = 200;
        mesh1 = mesh2 = ofMesh::sphere(radius, 10, OF_PRIMITIVE_TRIANGLE_STRIP);
        
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
        
        ofSetColor(ofColor::red);
        mesh1.drawWireframe();
        mesh2.drawWireframe();
        ofSetColor(ofColor::white);
        
        cam.end();
        
        ofDrawBitmapString(ofToString(ofGetFrameRate()) + " fps", 20, 20);
    }
    
    void keyPressed(int key) {
        //
    }
    
protected:
    
    ofEasyCam cam;
    ofMesh mesh1;
    ofMesh mesh2;
    ofMesh meshUnion;
};
