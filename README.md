ofxCGAL
=======

CGAL 4.3 addon for openFrameworks

WIP

Requires: (for OSX)

- ofxOSXBoost - https://github.com/danoli3/ofxOSXBoost/ 
- Make sure to Add the Requirements of ofxOSXBoost to the project as well


### How To Link to an Xcode Project?

In Xcode Project Build Settings:

#### Add to Library Search Paths ( ```LIBRARY_SEARCH_PATHS``` )

``` $(SRCROOT)/../../../addons/ofxCGAL/libs/CGAL/lib/osx ```
``` $(SRCROOT)/../../../addons/ofxCGAL/libs/CGAL/lib/osx/CGAL ```



#### Add to Header Search Paths ( ```HEADER_SEARCH_PATHS``` )

``` $(SRCROOT)/../../../addons/ofxCGAL/src ```
``` $(SRCROOT)/../../../addons/ofxCGAL/libs/ofxCGAL/include ```
``` $(SRCROOT)/../../../addons/ofxCGAL/libs/CGAL/include ```
``` $(SRCROOT)/../../../addons/ofxCGAL/libs/CGAL/include/eigen3 ```


#### In the Target under Build Phases

Add to 'Link Binary With Libraries' add all the libraries found in the following folders ofx

- ```ofxCGAL/libs/CGAL/lib/osx/ ```
- ```ofxCGAL/libs/CGAL/lib/osx/CGAL/ ```




