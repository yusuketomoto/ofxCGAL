//
//  main.cpp
//  example
//
//  Created by Lukasz Karluk on 13/12/2013.
//
//

#include "ofPoissonSurfaceApp.h"
#include "ofSkinSurfaceApp.h"

enum AppID {
    PoissonSurfaceApp,
    SkinSurfaceApp
};

int main( ){
	ofSetupOpenGL(1024,768,OF_WINDOW);

    // select which app you would like to run below,
    // by uncommenting out the appID.
    
    AppID appID;
//    appID = PoissonSurfaceApp;
    appID = SkinSurfaceApp;
    
    switch (appID) {
        case PoissonSurfaceApp:
            ofRunApp(new ofPoissonSurfaceApp());
            break;
        case SkinSurfaceApp:
            ofRunApp(new ofSkinSurfaceApp());
            break;
        default:
            break;
    }
}
