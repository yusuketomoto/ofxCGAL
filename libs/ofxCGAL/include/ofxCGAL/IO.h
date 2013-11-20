#pragma once

#ifdef check
#undef check
#endif

#include "ofxCGAL/Utility.h"
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/IO/read_xyz_points.h>
#include <CGAL/IO/read_off_points.h>

namespace ofxCGAL {
    
template <typename T>
inline vector<T> loadXyz(const string& file_name)
{
    vector<T> points;
    ifstream stream(ofToDataPath(file_name).c_str());
    assert(stream);
    assert(CGAL::read_xyz_points(stream, back_inserter(points), CGAL::Identity_property_map<T>()));
    return points;
}

ofMesh loadXyz(const string& file_name);

}