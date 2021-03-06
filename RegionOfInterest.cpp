//
//  RegionOfInterest.cpp
//  ThesisSerialCamShift
//
//  Created by Matthew Perry on 1/28/16.
//  Copyright © 2016 Matthew Perry. All rights reserved.
//

#include "RegionOfInterest.hpp"

RegionOfInterest::RegionOfInterest(Point topL, Point botR, int frameWidth, int frameHeight)
{
    _topLeft = topL;
    _bottomRight = botR;
    _width = botR.x - topL.x;
    _height = botR.y - topL.y;
    _frameWidth = frameWidth;
    _frameHeight = frameHeight;
    _centroid = calcCentroid(topL, _width, _height);
}

int RegionOfInterest::getTotalPixels(){
    return _width * _height;
}

void RegionOfInterest::setCentroid(Point centroid)
{
    _centroid = centroid;
    _topLeft = calcTopLeft(centroid, _width, _height);
    _bottomRight = calcBottomRight(centroid, _width, _height);
}

void RegionOfInterest::setROI(Point centroid, int width, int height)
{
    _centroid = centroid;
    _width =  width;
    _height =  height;
    _topLeft = calcTopLeft(centroid, width, height);
    _bottomRight = calcBottomRight(centroid, width, height);
}

Point RegionOfInterest::calcCentroid(Point topLeft, int w, int h)
{
    int cx = topLeft.x + (w / 2);
    int cy = topLeft.y + (h / 2);
    
    return Point(cx, cy);
    
}


Point RegionOfInterest::calcTopLeft(Point centroid, int ww, int wh)
{
    int topLeft_x = centroid.x - (ww / 2);
    int topLeft_y = centroid.y - (wh / 2);
    if(topLeft_x < 0) topLeft_x = 0;
    if(topLeft_y < 0) topLeft_y = 0;
    
    return Point(topLeft_x, topLeft_y);
    
}

Point RegionOfInterest::calcBottomRight(Point centroid, int ww, int wh)
{
    int bottomRight_x = centroid.x + (ww / 2);
    int bottomRight_y = centroid.y + (wh / 2);
    if(bottomRight_x > _frameWidth - 1) bottomRight_x = _frameWidth- 1;
    if(bottomRight_y > _frameHeight - 1) bottomRight_y = _frameHeight -1;
    
    return Point(bottomRight_x, bottomRight_y);
}

int RegionOfInterest::getFrameHeight(){
    return _frameHeight;
}

int RegionOfInterest::getFrameWidth(){
    return _frameWidth;
}

Point RegionOfInterest::getTopLeft()
{
    return _topLeft;
}

Point RegionOfInterest::getBottomRight()
{
    return _bottomRight;
}

void RegionOfInterest::drawROI(Mat * frame)
{
    rectangle(*frame, _topLeft, _bottomRight, Scalar( 0, 0, 255 ), THICKNESS, 8, 0);
    circle( *frame, _centroid, 5.0, Scalar( 0, 255, 255 ), -1, 8, 0 );
}
