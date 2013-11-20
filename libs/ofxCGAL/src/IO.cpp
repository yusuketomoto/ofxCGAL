#include "ofxCGAL/IO.h"

namespace ofxCGAL {

ofMesh loadXyz(const string& file_name)
{
    vector<Point_3> points = loadXyz<Point_3>(file_name);
    ofMesh m = toOf(points);
    return m;
}

}
