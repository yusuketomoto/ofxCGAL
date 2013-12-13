//
//  ofSkinSurfaceApp.h
//  Created by Lukasz Karluk on 13/12/13.
//

#include "ofMain.h"
#include "ofxCGAL.h"

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/make_skin_surface_mesh_3.h>

using namespace ofxCGAL;

typedef CGAL::Exact_predicates_inexact_constructions_kernel   K;
typedef CGAL::Skin_surface_traits_3<K>                        Traits;
typedef CGAL::Skin_surface_3<Traits>                          Skin_surface_3;
typedef Skin_surface_3::FT                                    FT;
typedef Skin_surface_3::Weighted_point                        Weighted_point;
typedef Weighted_point::Point                                 Bare_point;
typedef CGAL::Skin_surface_polyhedral_items_3<Skin_surface_3> Polyhedral_items;
typedef CGAL::Polyhedron_3<K, Polyhedral_items>               Polyhedron;

class ofSkinSurfaceApp : public ofBaseApp {
public:
    
    void setup() {
        ofSetFrameRate(30);
        ofSetSphereResolution(10);
        
        bDebug = false;
        bReset = true;
    }
    
    void update() {
        if(bReset == false) {
            return;
        }
        bReset = false;
        
        points.clear();
        pointWeights.clear();
        
        int numOfPoints = 20;
        for(int i=0; i<numOfPoints; i++) {
            
            points.push_back(ofVec3f());
            points.back().x = ofRandom(-2, 2);
            points.back().y = ofRandom(-2, 2);
            points.back().z = ofRandom(-2, 2);
            
            pointWeights.push_back(ofRandom(0.1, 1.0));
        }
        
        //----------------------------------------------------------------
        std::list<Weighted_point> l;
        FT shrinkfactor = 0.5;
        
        for(int i=0; i<points.size(); i++) {
            float px = points[i].x;
            float py = points[i].y;
            float pz = points[i].z;
            float weight = pointWeights[i];
            
            l.push_front(Weighted_point(Bare_point(px, py, pz), weight));
        }
        
        Skin_surface_3 skin_surface(l.begin(), l.end(), shrinkfactor);
        
        Polyhedron p;
        CGAL::mesh_skin_surface_3(skin_surface, p);
        
        CGAL::subdivide_skin_surface_mesh_3(skin_surface, p);
        
        //----------------------------------------------------------------
        mesh.clear();
        
        map<Point_3, int> point_indices;
        int count = 0;
        
        for (auto it=p.vertices_begin(); it!=p.vertices_end(); ++it) {
            auto& p = it->point();
            mesh.addVertex(ofVec3f(p.x(), p.y(), p.z()));
            point_indices[p] = count++;
        }
        for (auto it=p.facets_begin(); it!=p.facets_end(); ++it) {
            mesh.addIndex(point_indices[it->halfedge()->vertex()->point()]);
            mesh.addIndex(point_indices[it->halfedge()->next()->vertex()->point()]);
            mesh.addIndex(point_indices[it->halfedge()->prev()->vertex()->point()]);
        }
    }
    
    void draw() {
        cam.begin();
        
        float scale = 100;
        ofScale(scale, scale, scale);
        
        if(bDebug == true) {
            ofSetColor(ofColor::red);
            for(int i=0; i<points.size(); i++) {
                float px = points[i].x;
                float py = points[i].y;
                float pz = points[i].z;
                float weight = sqrt(pointWeights[i]);
                
                ofNoFill();
                ofDrawSphere(px, py, pz, weight);
                ofFill();
            }
        }
        
        ofSetColor(ofColor::white);
        mesh.drawWireframe();
        
        cam.end();
        
        ofDrawBitmapString(ofToString(ofGetFrameRate()) + " fps", 20, 20);
    }
    
    void keyPressed(int key) {
        if(key == 'd' || key == 'D') {
            bDebug = !bDebug;
        }
        if(key == 'r' || key == 'R') {
            bReset = true;
        }
    }
    
protected:
    
    ofEasyCam cam;
    ofMesh mesh;
    vector<ofVec3f> points;
    vector<float> pointWeights;
    
    bool bDebug;
    bool bReset;
};
