#pragma once
#define CGAL_EIGEN3_ENABLED

#include "ofMain.h"

#ifdef check
#undef check
#endif

#include "ofxCGAL/Types.h"
#include "ofxCGAL/IO.h"
#include "ofxCGAL/Utility.h"

#include <CGAL/property_map.h>

// outlier removal
#include <CGAL/remove_outliers.h>


namespace ofxCGAL {
    
    void removeOutliers(PointList& points, float removed_percentage, int nb_neighbors);
    void simplifyCloud(PointList& points, float cell_size);
    void smoothCloud(PointList& points, int nb_neighbors, int iter=1);
    void estimateNormals(const PointList& points, PointVectorList& point_vectors, int nb_neighbors);
    void orientNormals(PointVectorList& point_vectors, int nb_neighbors, bool trim=false);
    
    FT computeAverageSpacing(PointList& points, int nb_neighbors=6);
    
    void removeOutlierTest(ofMesh& m1, ofMesh& m2);
    void poissonReconstructionTest(ofMesh& m1, ofMesh& m2);
}