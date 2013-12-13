//
//  ofSkinSurfaceApp.h
//  Created by Lukasz Karluk on 13/12/13.
//

#include "ofMain.h"
#include "ofxCGAL.h"

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/make_skin_surface_mesh_3.h>

using namespace ofxCGAL;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_3                                          Bare_point;
typedef CGAL::Weighted_point<Bare_point,K::RT>              Weighted_point;
typedef CGAL::Polyhedron_3<K>                               Polyhedron;

class ofSkinSurfaceApp : public ofBaseApp {
public:
    
    void setup() {
        std::list<Weighted_point> l;
        double shrinkfactor = 0.5;
        
        l.push_front(Weighted_point(Bare_point( 1,-1,-1), 1.25));
        l.push_front(Weighted_point(Bare_point( 1, 1, 1), 1.25));
        l.push_front(Weighted_point(Bare_point(-1, 1,-1), 1.25));
        l.push_front(Weighted_point(Bare_point(-1,-1, 1), 1.25));
        
        Polyhedron p;
        
        CGAL::make_skin_surface_mesh_3(p, l.begin(), l.end(), shrinkfactor);
        
        mesh = toOf(p);
    }
    
    void update() {
        //
    }
    
    void draw() {
        cam.begin();
        float scale = 100;
        ofScale(scale, scale, scale);
        mesh.drawWireframe();
        cam.end();
    }
    
protected:
    
    ofEasyCam cam;
    ofMesh mesh;
};
