//
//  RegionOfInterest.hpp
//  ThesisSerialCamShift
//
//  Created by Matthew Perry on 1/28/16.
//  Copyright © 2016 Matthew Perry. All rights reserved.
//

#ifndef RegionOfInterest_hpp
#define RegionOfInterest_hpp

#include <stdio.h>
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/videoio/videoio.hpp"
#include "opencv2/core/core.hpp"



using namespace cv;
using namespace std;

#define THICKNESS 3

class RegionOfInterest{
public:
    RegionOfInterest(Point topR, Point botL, int fWidth, int fHeight);
    void drawROI(Mat * frame);
    void setCentroid(Point centroid);
    void setROI(Point centroid, int width, int height);
    Point getTopLeft();
    Point getBottomRight();
    int getTotalPixels();
    int getFrameWidth();
    int getFrameHeight();
    Point _centroid;
    
private:
    
    Point _topLeft;
    Point _bottomRight;
    int _width;
    int _height;
    int _frameWidth;
    int _frameHeight;
    Point calcBottomRight(Point centroid, int w, int h);
    Point calcTopLeft(Point centroid, int ww, int wh);
    Point calcCentroid(Point topLeft, int w, int h);
    
};
#endif /* RegionOfInterest_hpp */
