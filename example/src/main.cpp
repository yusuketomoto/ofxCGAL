//
//  main.cpp
//  example
//
//  Created by Lukasz Karluk on 13/12/2013.
//
//

#include "ofPoissonSurfaceApp.h"
#include "ofSkinSurfaceApp.h"
#include "ofBooleanUnionApp.h"
#include "ofStreamlinesApp.h"

enum AppID {
    PoissonSurfaceApp,
    SkinSurfaceApp,
    BooleanUnionApp,
    StreamlinesApp
};

int main( ){
	ofSetupOpenGL(1024,768,OF_WINDOW);

    // select which app you would like to run below,
    // by uncommenting out the appID.
    
    AppID appID;
//    appID = PoissonSurfaceApp;
//    appID = SkinSurfaceApp;
//    appID = BooleanUnionApp;
    appID = StreamlinesApp;
    
    switch (appID) {
        case PoissonSurfaceApp:
            ofRunApp(new ofPoissonSurfaceApp());
            break;
        case SkinSurfaceApp:
            ofRunApp(new ofSkinSurfaceApp());
            break;
        case BooleanUnionApp:
            ofRunApp(new ofBooleanUnionApp());
            break;
        case StreamlinesApp:
            ofRunApp(new ofStreamlinesApp());
            break;
        default:
            break;
    }
}
