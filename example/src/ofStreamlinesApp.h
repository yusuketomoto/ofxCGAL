//
//  ofStreamlinesApp.h
//  Created by Lukasz Karluk on 13/12/13.
//

#pragma once

#include "ofMain.h"
#include "ofxCGALStreamlines.h"

//--------------------------------------------------------------
class Particle {
public:
    Particle() {
        range = 1;
        strength = 1;
        charge = 1;
    }
    
    ofVec2f pos;
    ofVec2f vel;
    float range;
    float strength;
    int charge; // positive or negative (1 or -1)
};

//--------------------------------------------------------------
class ofStreamlinesApp : public ofBaseApp {
public:

    //----------------------------------------------------------
    void setup() {
        ofSetFrameRate(30);
        
        vecfieldSize = 512;
        vecfield.setup(vecfieldSize, vecfieldSize);
        
        int numOfParticles = 10;
        for(int i=0; i<numOfParticles; i++) {
            particles.push_back(Particle());
            
            float x = ofRandom(vecfieldSize);
            float y = ofRandom(vecfieldSize);
            float range = ofRandom(vecfieldSize * 0.2, vecfieldSize * 0.4);
            float stength = ofRandom(0.1, 1.0);
            int charge = ofRandom(0.5) < 0.5 ? -1 : 1;
            
            particles.back().pos.set(x, y);
            particles.back().vel.set(0, 0);
            particles.back().range = range;
            particles.back().strength = stength;
            particles.back().charge = charge;
        }
        
        int w = vecfieldSize;
        int h = vecfieldSize;

        for(int y=0; y<h; y++) {
            for(int x=0; x<w; x++) {
                ofVec2f pos(x, y);
                ofVec2f vec = getVectorAt(pos);
                vecfield.setValueAt(x, y, vec);
            }
        }
        
        streamlines.calc(vecfield);
    }
    
    //----------------------------------------------------------
    ofVec2f getVectorAt(const ofVec2f & pos) {
        
        int w = vecfieldSize;
        int h = vecfieldSize;
        
        ofVec2f vec;
        ofVec2f vecSum;
        
        for(int i=0; i<particles.size(); i++) {
            Particle & particle = particles[i];
            ofVec2f & particlePos = particle.pos;
            float range = particle.range;
            float strength = particle.strength;
            int charge = particle.charge;
            
            float d = ofDist(particlePos.x, particlePos.y, pos.x, pos.y);
            
            if(d > range) {
                continue;
            }
            
            float v = 1.0 - (d / range);
            float falloff = sin(PI * 0.5 * v);
            
            vec.set(particlePos);
            vec -= ofVec2f(pos.x, pos.y);
            vec.normalize();
            vec *= strength * falloff * charge;
            
            vecSum += vec;
        }
        
        vecSum.normalize();
        
        return vecSum;
    }
    
    //----------------------------------------------------------
    void update() {
        //
    }
    
    //----------------------------------------------------------
    void draw() {
        ofSetColor(0);
        streamlines.draw();
        ofSetColor(255);
    }
    
    //----------------------------------------------------------
    void keyPressed(int key) {
        //
    }
    
protected:
    
    int vecfieldSize;
    vector<Particle> particles;
    ofxCGALVectorField vecfield;
    ofxCGALStreamlines streamlines;
};
