//
//  ofxCGALSkinSurface.cpp
//  Created by Lukasz Karluk on 17/12/2013.
//

#include "ofxCGALSkinSurface.h"

#ifdef check
#undef check
#endif

// PI definition is conflicting with some CGAL internals
// so it needs to be undefined here, and defined again after the includes.
#undef PI

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/make_skin_surface_mesh_3.h>

#define PI 3.14159265358979323846

typedef CGAL::Exact_predicates_inexact_constructions_kernel   K;
typedef CGAL::Skin_surface_traits_3<K>                        Traits;
typedef CGAL::Skin_surface_3<Traits>                          Skin_surface_3;
typedef Skin_surface_3::FT                                    FT;
typedef Skin_surface_3::Weighted_point                        Weighted_point;
typedef Weighted_point::Point                                 Bare_point;
typedef CGAL::Skin_surface_polyhedral_items_3<Skin_surface_3> Polyhedral_items;
typedef CGAL::Polyhedron_3<K, Polyhedral_items>               Polyhedron;
typedef K::Point_3                                            Point_3;

//-------------------------------------------------------------
ofxCGALSkinSurface::ofxCGALSkinSurface() {
    bSubdiv = false;
    shrinkFactor = 0.5;
}

ofxCGALSkinSurface::~ofxCGALSkinSurface() {
    //
}

//-------------------------------------------------------------
void ofxCGALSkinSurface::setSubdivEnable(bool value) {
    bSubdiv = value;
}

bool ofxCGALSkinSurface::getSubdivEnable() {
    return bSubdiv;
}

void ofxCGALSkinSurface::setShrinkFactor(float value) {
    shrinkFactor = ofClamp(value, 0.0, 1.0);
}

float ofxCGALSkinSurface::getShrinkFactor() {
    return shrinkFactor;
}

//-------------------------------------------------------------
void ofxCGALSkinSurface::clearPoints() {
    points.clear();
}

void ofxCGALSkinSurface::addPoint(ofVec3f & point, float radius) {
    points.push_back(ofxCGALSkinSurfacePoint(point, radius));
}

void ofxCGALSkinSurface::addPoints(vector<ofxCGALSkinSurfacePoint> & pointsToAdd) {
    for(int i=0; i<pointsToAdd.size(); i++) {
        points.push_back(pointsToAdd[i]);
    }
}

ofMesh & ofxCGALSkinSurface::makeSkinSurfaceMesh() {
    std::list<Weighted_point> l;
    FT shrinkfactor = shrinkFactor;
    
    for(int i=0; i<points.size(); i++) {
        float px = points[i].point.x;
        float py = points[i].point.y;
        float pz = points[i].point.z;
        float radius = points[i].radius;
        
        l.push_front(Weighted_point(Bare_point(px, py, pz), radius * radius));
    }
    
    Skin_surface_3 skin_surface(l.begin(), l.end(), shrinkfactor);
    
    Polyhedron p;
    CGAL::mesh_skin_surface_3(skin_surface, p);
    
    if(bSubdiv == true) {
        CGAL::subdivide_skin_surface_mesh_3(skin_surface, p);
    }
    
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

//-------------------------------------------------------------
void ofxCGALSkinSurface::drawPoints() {
    for(int i=0; i<points.size(); i++) {
        float px = points[i].point.x;
        float py = points[i].point.y;
        float pz = points[i].point.z;
        float radius = points[i].radius;
        
        ofDrawSphere(px, py, pz, radius);
    }
}

void ofxCGALSkinSurface::drawSkinSurfaceFaces() {
    mesh.drawFaces();
}

void ofxCGALSkinSurface::drawSkinSurfaceWireframe() {
    mesh.drawWireframe();
}

