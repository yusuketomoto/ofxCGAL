#pragma once

#ifdef check
#undef check
#endif

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>



namespace ofxCGAL
{
    // types
    typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
    typedef Kernel::Point_3 Point_3;
    
    

}