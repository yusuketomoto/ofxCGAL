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

#include <CGAL/trace.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/IO/Polyhedron_iostream.h>
#include <CGAL/Surface_mesh_default_triangulation_3.h>
#include <CGAL/make_surface_mesh.h>
#include <CGAL/Implicit_surface_3.h>
#include <CGAL/IO/output_surface_facets_to_polyhedron.h>
#include <CGAL/Poisson_reconstruction_function.h>
#include <CGAL/Point_with_normal_3.h>
#include <CGAL/property_map.h>
#include <CGAL/IO/read_xyz_points.h>
#include <CGAL/compute_average_spacing.h>

namespace ofxCGAL {
    
    typedef Kernel::FT FT;
    typedef CGAL::Point_with_normal_3<Kernel> Point_with_normal;
    typedef Kernel::Sphere_3 Sphere_3;
    typedef std::vector<Point_with_normal> PointList;
    typedef CGAL::Polyhedron_3<Kernel> Polyhedron_3;
    typedef CGAL::Poisson_reconstruction_function<Kernel> Poisson_reconstruction_function;
    typedef CGAL::Surface_mesh_default_triangulation_3 STr;
    typedef CGAL::Surface_mesh_complex_2_in_triangulation_3<STr> C2t3;
    typedef CGAL::Implicit_surface_3<Kernel, Poisson_reconstruction_function> Surface_3;
    
    
    void test(ofMesh& m1, ofMesh& m2);
    
    void test1(ofMesh& m1, ofMesh& m2);
}