#pragma once
#include "ofMain.h"
#include "ofxCGAL.h"

namespace ofxCGAL
{
    
#pragma mark - convert
template<class T1, class T2>
void convert(const T1&, T2&);
    
template <>
inline void convert(const vector<Point_3>& points, ofMesh& mesh)
{
    mesh.clear();
    for (auto& p : points) mesh.addVertex(ofVec3f(p.x(), p.y(), p.z()));
}

template <>
inline void convert(const PointVectorList& point_vectors, ofMesh& mesh)
{
    mesh.clear();
    for (auto& p : point_vectors) {
        mesh.addVertex(ofVec3f(p.first.x(), p.first.y(), p.first.z()));
        mesh.addNormal(ofVec3f(p.second.x(), p.second.y(), p.second.z()));
    }
}

template <>
inline void convert(const ofMesh& mesh, PointList& points)
{
    points.clear();
    for (auto& p : mesh.getVertices()) points.push_back(Point_3(p.x, p.y, p.z));
}

template <>
inline void convert(const ofMesh& mesh, PointVectorList& point_vectors)
{
    int n = mesh.getNumVertices();
    for (int i=0; i<n; i++) {
        auto& pos = mesh.getVertices()[i];
        auto& norm = mesh.getNormals()[i];
        
        PointVectorPair point_vector;
        point_vector.first = Point_3(pos.x, pos.y, pos.z);
        point_vector.second = Vector_3(norm.x, norm.y, norm.z);
        
        point_vectors.push_back(point_vector);
    }
}

template <>
inline void convert(const PointVectorList& point_vectors, PointWNList& point_with_normals)
{
    int n = point_vectors.size();
    point_with_normals.resize(n);
    for (int i=0; i<n; i++) {
        point_with_normals[i].position() = point_vectors[i].first;
        point_with_normals[i].normal() = point_vectors[i].second;
    }
}
    
template <>
inline void convert(const Polyhedron_3& polyhedron, ofMesh& mesh)
{
    mesh.clear();
    
    map<Point_3, int> point_indices;
    int count = 0;
    
    for (auto it=polyhedron.vertices_begin(); it!=polyhedron.vertices_end(); ++it) {
        auto& p = it->point();
        mesh.addVertex(ofVec3f(p.x(), p.y(), p.z()));
        point_indices[p] = count++;
    }
    for (auto it=polyhedron.facets_begin(); it!=polyhedron.facets_end(); ++it) {
        mesh.addIndex(point_indices[it->halfedge()->vertex()->point()]);
        mesh.addIndex(point_indices[it->halfedge()->next()->vertex()->point()]);
        mesh.addIndex(point_indices[it->halfedge()->prev()->vertex()->point()]);
    }
}

#pragma mark - toOf
inline ofMesh toOf(const vector<Point_3>& points)
{
    ofMesh mesh;
    convert(points, mesh);
    return mesh;
}

inline ofMesh toOf(const PointVectorList& point_vectors)
{
    ofMesh mesh;
    convert(point_vectors, mesh);
    return mesh;
}

inline ofMesh toOf(const Polyhedron_3& polyhedron)
{
    ofMesh mesh;
    convert(polyhedron, mesh);
    return mesh;
}

#pragma mark - toCGAL
template <typename T>
inline T toCGAL(const ofMesh& mesh)
{
    T points;
    convert(mesh, points);
    return points;
}
    
}
