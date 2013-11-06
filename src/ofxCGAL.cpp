#include "ofxCGAL.h"

namespace ofxCGAL {
    
void test(ofMesh& m1, ofMesh& m2)
{
    // Reads a .xyz point set file in points[].
    // The Identity_property_map property map can be omitted here as it is the default value.
    string file_name = "oni.xyz";
    
    vector<Point_3> points;
    points = loadXyz<Point_3>(file_name);
    
    // Removes outliers using erase-remove idiom.
    // The Identity_property_map property map can be omitted here as it is the default value.
    const double removed_percentage = 5.0; // percentage of points to remove
    const int nb_neighbors = 24; // considers 24 nearest neighbor points
    
    m1 = toOf(points);
    
    points.erase(CGAL::remove_outliers(points.begin(), points.end(),
                                       CGAL::Identity_property_map<Point_3>(),
                                       nb_neighbors, removed_percentage),
                 points.end());
    // Optional: after erase(), use Scott Meyer's "swap trick" to trim excess capacity
    std::vector<Point_3>(points).swap(points);
    
    m2 = toOf(points);

}
    
    
//    inline vector<PointList> loadXyz(const string& file_name)
//    {
//        vector<PointList> points;
//        ifstream stream(ofToDataPath(file_name).c_str());
//        assert(stream);
//        assert(CGAL::read_xyz_points_and_normals(stream,
//                                                 back_inserter(points),
//                                                 CGAL::make_normal_of_point_with_normal_pmap(PointList::value_type())));
//        return points;
//    }
    
void test1(ofMesh& m1, ofMesh& m2)
{
    string file_name = "kitten.xyz";
    
    // Poisson options
    FT sm_angle = 20.0; // Min triangle angle in degrees.
    FT sm_radius = 30; // Max triangle size w.r.t. point set average spacing.
    FT sm_distance = 0.375; // Surface Approximation error w.r.t. point set average spacing.
    // Reads the point set file in points[].
    // Note: read_xyz_points_and_normals() requires an iterator over points
    // + property maps to access each point's position and normal.
    // The position property map can be omitted here as we use iterators over Point_3 elements.
    PointList points;
    
    std::ifstream stream(ofToDataPath(file_name).c_str());
    if (!stream ||
        !CGAL::read_xyz_points_and_normals(
                                           stream,
                                           std::back_inserter(points),
                                           CGAL::make_normal_of_point_with_normal_pmap(PointList::value_type())))
    {
        std::cerr << "Error: cannot read file data/kitten.xyz" << std::endl;
        return EXIT_FAILURE;
    }
    
    m1.clear();
    for (auto& p : points) {
        m1.addVertex(ofVec3f(p.x(), p.y(), p.z()));
        m1.addNormal(ofVec3f(p.normal().x(), p.normal().y(), p.normal().z()));
    }
    
    // Creates implicit function from the read points using the default solver.
    // Note: this method requires an iterator over points
    // + property maps to access each point's position and normal.
    // The position property map can be omitted here as we use iterators over Point_3 elements.
    Poisson_reconstruction_function function(points.begin(), points.end(),
                                             CGAL::make_normal_of_point_with_normal_pmap(PointList::value_type()) );
    // Computes the Poisson indicator function f()
    // at each vertex of the triangulation.
    if ( ! function.compute_implicit_function() )
        return EXIT_FAILURE;
    // Computes average spacing
    FT average_spacing = CGAL::compute_average_spacing(points.begin(), points.end(),
                                                       6 /* knn = 1 ring */);
    // Gets one point inside the implicit surface
    // and computes implicit function bounding sphere radius.
    Point_3 inner_point = function.get_inner_point();
    Sphere_3 bsphere = function.bounding_sphere();
    FT radius = std::sqrt(bsphere.squared_radius());
    // Defines the implicit surface: requires defining a
    // conservative bounding sphere centered at inner point.
    FT sm_sphere_radius = 5.0 * radius;
    FT sm_dichotomy_error = sm_distance*average_spacing/1000.0; // Dichotomy error must be << sm_distance
    Surface_3 surface(function,
                      Sphere_3(inner_point,sm_sphere_radius*sm_sphere_radius),
                      sm_dichotomy_error/sm_sphere_radius);
    // Defines surface mesh generation criteria
    CGAL::Surface_mesh_default_criteria_3<STr> criteria(sm_angle,  // Min triangle angle (degrees)
                                                        sm_radius*average_spacing,  // Max triangle size
                                                        sm_distance*average_spacing); // Approximation error
    // Generates surface mesh with manifold option
    STr tr; // 3D Delaunay triangulation for surface mesh generation
    C2t3 c2t3(tr); // 2D complex in 3D Delaunay triangulation
    CGAL::make_surface_mesh(c2t3,                                 // reconstructed mesh
                            surface,                              // implicit surface
                            criteria,                             // meshing criteria
                            CGAL::Manifold_with_boundary_tag());  // require manifold mesh
    if(tr.number_of_vertices() == 0)
        return EXIT_FAILURE;
    // saves reconstructed surface mesh
    std::ofstream out(ofToDataPath("kitten_poisson-20-30-0.375.off").c_str());
    Polyhedron_3 output_mesh;
    CGAL::output_surface_facets_to_polyhedron(c2t3, output_mesh);
    out << output_mesh;
    
    m2.clear();
    
    map<Point_3, int> point_indices;
    int count = 0;
    
    for (auto it=output_mesh.vertices_begin(); it!=output_mesh.vertices_end(); ++it) {
        auto& p = it->point();
        m2.addVertex(ofVec3f(p.x(), p.y(), p.z()));
        point_indices[p] = count++;
    }
    for (auto it=output_mesh.facets_begin(); it!=output_mesh.facets_end(); ++it) {
        m2.addIndex(point_indices[it->halfedge()->vertex()->point()]);
        m2.addIndex(point_indices[it->halfedge()->next()->vertex()->point()]);
        m2.addIndex(point_indices[it->halfedge()->prev()->vertex()->point()]);
    }
    
    return EXIT_SUCCESS;

}
    
}