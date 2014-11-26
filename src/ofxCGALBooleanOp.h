//
//  ofxCGALBooleanOp.h
//  example
//
//  Created by Lukasz Karluk on 16/12/2013.
//
//

#pragma once

#include "ofMain.h"

enum ofBoolOpType {
    OF_BOOLEAN_OPERATOR_UNION = 0,
    OF_BOOLEAN_OPERATOR_DIFFERENCE = 1,
    OF_BOOLEAN_OPERATOR_INTERSECTION = 2,
    OF_BOOLEAN_OPERATOR_COMPLEMENT = 3,
    OF_BOOLEAN_OPERATOR_SYMMETRIC_DIFFERENCE = 4
};

class ofxCGALBooleanOp {
    
public:
    ofxCGALBooleanOp();
    ~ofxCGALBooleanOp();
    
    static ofMesh & runOp(ofMesh & mesh1, ofMesh & mesh2, ofBoolOpType boolOpType);
    static ofMesh & runOp(vector<ofMesh *> meshes, ofBoolOpType boolOpType);
};