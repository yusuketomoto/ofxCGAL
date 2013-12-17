//
//  ofxCGALBooleanOp.cpp
//  Created by Lukasz Karluk on 16/12/2013.
//

#include "ofxCGALBooleanOp.h"

#ifdef check
#undef check
#endif

// PI definition is conflicting with some CGAL internals
// so it needs to be undefined here, and defined again after the includes.
#undef PI

#include <CGAL/Gmpz.h>
#include <CGAL/Homogeneous.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Polyhedron_incremental_builder_3.h>
#include <CGAL/Nef_polyhedron_3.h>

#define PI 3.14159265358979323846

typedef CGAL::Gmpz NT;
typedef CGAL::Homogeneous<NT> Kernel;
typedef CGAL::Polyhedron_3<Kernel> Polyhedron;
typedef CGAL::Nef_polyhedron_3<Kernel> Nef_polyhedron;
typedef Polyhedron::HalfedgeDS HalfedgeDS;
typedef Kernel::Point_3 Point_3;

static ofMesh meshResult;
static int kPointScale = 100000;

//-------------------------------------------------------------
template <class HDS>
class PolyhedronBuilder : public CGAL::Modifier_base<HDS> {
public:
    
    const ofMesh & mesh;
    
    PolyhedronBuilder(const ofMesh & _mesh) : mesh(_mesh) {
        //
    }
    
    void operator()(HDS & hds) {
        
        CGAL::Polyhedron_incremental_builder_3<HDS> B(hds, true);
        
        int numOfVertices = mesh.getNumVertices();
        int numOfIndices = mesh.getNumIndices();
        int numOfFaces = numOfIndices / 3;
        
        B.begin_surface(numOfVertices,
                        numOfFaces);
        
        typedef typename HDS::Vertex Vertex;
        typedef typename Vertex::Point Point;
        
        const vector<ofVec3f> & vertices = mesh.getVertices();
        for(int i=0; i<numOfVertices; i++) {
            B.add_vertex(Point((int)(vertices[i].x * kPointScale),
                               (int)(vertices[i].y * kPointScale),
                               (int)(vertices[i].z * kPointScale)));
        }
        
        if(mesh.getMode() == OF_PRIMITIVE_TRIANGLES) {

            const vector<ofIndexType> & indices = mesh.getIndices();
            for(int i=0; i<numOfIndices; i+=3) {
                B.begin_facet();
                B.add_vertex_to_facet(indices[i+0]);
                B.add_vertex_to_facet(indices[i+1]);
                B.add_vertex_to_facet(indices[i+2]);
                B.end_facet();
            }
            
        } else if(mesh.getMode() == OF_PRIMITIVE_TRIANGLE_STRIP) {
            
            ofLogError("ofxCGALBooleanOp currently only works with ofMesh mode :: OF_PRIMITIVE_TRIANGLES");
            
        } else {
            
            ofLogError("ofxCGALBooleanOp currently only works with ofMesh mode :: OF_PRIMITIVE_TRIANGLES");
        }
        
        
        B.end_surface();
    }
};

//-------------------------------------------------------------
inline void convert(const ofMesh & mesh, Polyhedron & polyhedron) {
    PolyhedronBuilder<HalfedgeDS> builder(mesh);
    polyhedron.delegate(builder);
}

inline void convert(const Polyhedron & polyhedron, ofMesh & mesh) {
    map<Point_3, int> point_indices;
    int count = 0;
    
    for (auto it=polyhedron.vertices_begin(); it!=polyhedron.vertices_end(); ++it) {
        auto& p = it->point();
        float x = CGAL::to_double(p.x()) / (float)kPointScale;
        float y = CGAL::to_double(p.y()) / (float)kPointScale;
        float z = CGAL::to_double(p.z()) / (float)kPointScale;
        mesh.addVertex(ofVec3f(x, y, z));
        point_indices[p] = count++;
    }
    for (auto it=polyhedron.facets_begin(); it!=polyhedron.facets_end(); ++it) {
        mesh.addIndex(point_indices[it->halfedge()->vertex()->point()]);
        mesh.addIndex(point_indices[it->halfedge()->next()->vertex()->point()]);
        mesh.addIndex(point_indices[it->halfedge()->prev()->vertex()->point()]);
    }
}

//-------------------------------------------------------------
ofxCGALBooleanOp::ofxCGALBooleanOp() {
    meshResult.disableColors();
    meshResult.disableNormals();
    meshResult.disableTextures();
}

ofxCGALBooleanOp::~ofxCGALBooleanOp() {
    //
}

//-------------------------------------------------------------

ofMesh & ofxCGALBooleanOp::runOp(ofMesh & mesh1, ofMesh & mesh2, ofBoolOpType boolOpType) {

    vector<ofMesh *> meshes;
    meshes.push_back(&mesh1);
    meshes.push_back(&mesh2);
    runOp(meshes, boolOpType);
    
    return meshResult;
}

ofMesh & ofxCGALBooleanOp::runOp(vector<ofMesh *> meshes, ofBoolOpType boolOpType) {

    meshResult.clear();
    
    if(meshes.size() == 0) {
        return meshResult; // return empty mesh.
    }
    
    if(meshes.size() == 1) {
        meshResult = *meshes[0];
        return meshResult; // return first mesh.
    }
    
    ofMesh & mesh0 = *meshes[0];
    ofMesh & mesh1 = *meshes[1];
    
    Polyhedron polyhedron0, polyhedron1, polyhedronUnion;
    
    convert(mesh0, polyhedron0);
    convert(mesh1, polyhedron1);
    
    if(polyhedron0.is_valid() == false || polyhedron1.is_valid() == false) {
        ofLogError("ofxCGALBooleanOp :: input mesh is invalid.");
        return meshResult;
    }
    
    if(polyhedron0.is_closed() == false || polyhedron1.is_closed() == false) {
        ofLogError("ofxCGALBooleanOp :: input mesh is not closed.");
        return meshResult;
    }
 
    Nef_polyhedron nefPolyhedron0(polyhedron0);
    Nef_polyhedron nefPolyhedron1(polyhedron1);
    
    if(boolOpType == OF_BOOLEAN_OPERATOR_UNION) {
        nefPolyhedron0 += nefPolyhedron1;
    } else if(boolOpType == OF_BOOLEAN_OPERATOR_DIFFERENCE) {
        nefPolyhedron0 -= nefPolyhedron1;
    } else if(boolOpType == OF_BOOLEAN_OPERATOR_INTERSECTION) {
        nefPolyhedron0 *= nefPolyhedron1;
    } else if(boolOpType == OF_BOOLEAN_OPERATOR_COMPLEMENT) {
        nefPolyhedron0 != nefPolyhedron1;
    } else if(boolOpType == OF_BOOLEAN_OPERATOR_SYMMETRIC_DIFFERENCE) {
        nefPolyhedron0 ^= nefPolyhedron1;
    }
    nefPolyhedron0.convert_to_polyhedron(polyhedronUnion);
    
    convert(polyhedronUnion, meshResult);
    
    return meshResult;
}

