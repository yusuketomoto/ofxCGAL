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


#pragma mark - toOf
inline ofMesh toOf(const vector<Point_3>& points)
{
    ofMesh mesh;
    convert(points, mesh);
    return mesh;
}


}
