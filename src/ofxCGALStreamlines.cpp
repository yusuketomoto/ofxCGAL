//
//  ofxCGALStreamlines.cpp
//  example
//
//  Created by Lukasz Karluk on 12/01/2015.
//
//

#include "ofxCGALStreamlines.h"

#ifdef check
#undef check
#endif

// PI definition is conflicting with some CGAL internals
// so it needs to be undefined here, and defined again after the includes.
#undef PI

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Stream_lines_2.h>
#include <CGAL/Runge_kutta_integrator_2.h>
#include <CGAL/Regular_grid_2.h>

#define PI 3.14159265358979323846

typedef CGAL::Exact_predicates_inexact_constructions_kernel         K;
typedef CGAL::Regular_grid_2<K> Field;
typedef CGAL::Runge_kutta_integrator_2<Field> Runge_kutta_integrator;
typedef CGAL::Stream_lines_2<Field, Runge_kutta_integrator> Strl;
typedef Strl::Point_iterator_2 Point_iterator;
typedef Strl::Stream_line_iterator_2 Strl_iterator;
typedef Strl::Point_2 Point_2;
typedef Strl::Vector_2 Vector_2;

//-------------------------------------------------------------
ofxCGALStreamlines::ofxCGALStreamlines() {
    width = height = 512;
    separatingDistance = 3.5;
    saturationRatio = 1.6;
}

ofxCGALStreamlines::~ofxCGALStreamlines() {
    //
}

//-------------------------------------------------------------
void ofxCGALStreamlines::setSeparationDistance(float value) {
    separatingDistance = value;
}

float ofxCGALStreamlines::getSeparationDistance() {
    return separatingDistance;
}

void ofxCGALStreamlines::setSaturationRatio(float value) {
    saturationRatio = value;
}

float ofxCGALStreamlines::getSaturationRatio() {
    return saturationRatio;
}

const vector<ofPolyline> & ofxCGALStreamlines::getPolys() {
    return streamlines;
}

//-------------------------------------------------------------
void ofxCGALStreamlines::calc(const ofxCGALVectorField & vectorField) {
    
    unsigned int x_samples = vectorField.getWidth();
    unsigned int y_samples = vectorField.getHeight();
    Field regular_grid_2(x_samples, y_samples, width, height);
    
    for(int x=0; x<x_samples; x++) {
        for(int y=0; y<y_samples; y++) {
            const ofVec2f & vec = vectorField.getValueAt(x, y);
            regular_grid_2.set_field(x, y, Vector_2(vec.x, vec.y));
        }
    }

    //---------------------------------------------------------
    Runge_kutta_integrator runge_kutta_integrator;
    
    Strl Stream_lines(regular_grid_2, runge_kutta_integrator, separatingDistance, saturationRatio);
    
    //---------------------------------------------------------
    streamlines.clear();
    for(Strl_iterator sit = Stream_lines.begin(); sit != Stream_lines.end(); sit++) {
        
        streamlines.push_back(ofPolyline());
        ofPolyline & poly = streamlines.back();
        
        for(Point_iterator pit = sit->first; pit != sit->second; pit++) {
            Point_2 p = *pit;
            poly.addVertex(p.x(), p.y());
        }
    }
}

void ofxCGALStreamlines::draw() {
    ofSetColor(0);
    drawBorder();
    drawStreamlines();
    ofSetColor(255);
}

void ofxCGALStreamlines::drawBorder() {
    ofNoFill();
    ofRect(0, 0, width, height);
    ofFill();
}

void ofxCGALStreamlines::drawStreamlines() {
    for(int i=0; i<streamlines.size(); i++) {
        ofPolyline & poly = streamlines[i];
        poly.draw();
    }
}

