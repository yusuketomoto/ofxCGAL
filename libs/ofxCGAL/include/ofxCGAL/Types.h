#pragma once

#ifdef check
#undef check
#endif

#include <CGAL/trace.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
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

#include <CGAL/jet_smooth_point_set.h>
#include <CGAL/grid_simplify_point_set.h>
#include <CGAL/IO/write_xyz_points.h>
#include <CGAL/mst_orient_normals.h>
#include <CGAL/pca_estimate_normals.h>
#include <CGAL/property_map.h>
#include <CGAL/remove_outliers.h>

namespace ofxCGAL
{
    // types
    typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
    typedef Kernel::FT FT;
    
    typedef Kernel::Point_3 Point_3;
    typedef std::vector<Point_3> PointList;
    
    typedef Kernel::Vector_3 Vector_3;
    typedef std::pair<Point_3, Vector_3> PointVectorPair;
    typedef std::vector<PointVectorPair> PointVectorList;
    
    typedef CGAL::Point_with_normal_3<Kernel> Point_with_normal;
    typedef std::vector<Point_with_normal> PointWNList;
//    typedef std::vector<PointWN> PointWNList; // Cloud of points 3D with normal
    
    typedef Kernel::Sphere_3 Sphere_3;
    typedef CGAL::Polyhedron_3<Kernel> Polyhedron_3;
    typedef CGAL::Poisson_reconstruction_function<Kernel> Poisson_reconstruction_function;
    typedef CGAL::Surface_mesh_default_triangulation_3 STr;
    typedef CGAL::Surface_mesh_complex_2_in_triangulation_3<STr> C2t3;
    typedef CGAL::Implicit_surface_3<Kernel, Poisson_reconstruction_function> Surface_3;

    

}