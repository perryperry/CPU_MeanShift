

//
//  main.cpp
//  ThesisSerialCamShift
//
//  Created by Matthew Perry on 1/27/16.
//  Copyright © 2016 Matthew Perry. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/videoio/videoio.hpp"
#include "opencv2/core/core.hpp"

#include "RegionOfInterest.hpp"
#include "UcharSerialCamShift.hpp"

using namespace cv;
using namespace std;

Point topLeft, bottomRight;

VideoWriter _outputVideo;

#define OUTPUTFILENAME "/home/EASTERN/mperry16/School/Thesis/UcharCPU_SerialMeanShift/out.mov"
#define MAXTHREADS 3


/*
 This method was taken from http://docs.opencv.org/2.4/doc/tutorials/highgui/video-write/video-write.html
 */
void openOutputVideo(cv::VideoCapture inputVideo)
{
    int ex = static_cast<int>(inputVideo.get(CV_CAP_PROP_FOURCC));     // Get Codec Type- Int form
    
    // Transform from int to char via Bitwise operators
    char EXT[] = {(char)(ex & 0XFF) , (char)((ex & 0XFF00) >> 8),(char)((ex & 0XFF0000) >> 16),(char)((ex & 0XFF000000) >> 24), 0};
    
    Size S = Size((int) inputVideo.get(CV_CAP_PROP_FRAME_WIDTH),    // Acquire input size
                  (int) inputVideo.get(CV_CAP_PROP_FRAME_HEIGHT));
    
    // Open the output
    
    _outputVideo.open(OUTPUTFILENAME, ex, inputVideo.get(CV_CAP_PROP_FPS), S, true);
    
    if (! _outputVideo.isOpened())
    {
        cout  << "Could not open the output video for write."<< endl;
    }
    else{
        cout << "#########################################" << endl;
        cout << "Input frame resolution: Width=" << S.width << "  Height=" << S.height
        << " of nr#: " << inputVideo.get(CV_CAP_PROP_FRAME_COUNT) << endl;
        cout << "Input codec type: " << EXT << endl;
        cout << "#########################################" << endl;
    }
}

void writeFrame(Mat frame)
{
    _outputVideo.write(frame);
}

int main(int argc, const char * argv[])
{
    
    if(argc != 3)
    {
        cout << argv << endl;
        cout << "Usage: <videofile> <x1 y1 x2 y2>" << endl;
        exit(-1);
    }
    
    VideoCapture cap(argv[1]);
    openOutputVideo(cap);
    
   
    int i = 0;
    int x, y, x2, y2;
    
    
    
    ifstream infile(argv[2]);
    //Read in windows from input file
    while (infile >> x >> y >> x2 >> y2)
    {
        cout << x <<  " " << y << " " << x2 << y2 << endl;
    }
    
    
    
    
    SerialCamShift camShift;
    
   
    topLeft = Point(x,y );
    bottomRight = Point(x2,y2 );
   
    
    Mat frame, hsv;
    
    double * histogram = (double * ) calloc(sizeof(double), BUCKETS);
    
    
    cap.read(frame);
  
    writeFrame(frame);
    
    RegionOfInterest roi(topLeft, bottomRight, cap.get(CV_CAP_PROP_FRAME_WIDTH), cap.get(CV_CAP_PROP_FRAME_HEIGHT));
    
    
    cvtColor(frame, hsv, CV_RGB2HSV);
    
    //This section for 1-D uchar
    std::vector<cv::Mat> hsv_channels;
    cv::split(hsv, hsv_channels);
    cv::Mat h_image = hsv_channels[0];
    int size = h_image.rows * h_image.cols;
    uchar * hueArray = h_image.data;
    int step = h_image.step;

    camShift.createHistogram(hueArray, step, &roi, &frame, &histogram);
    
    
    while(cap.read(frame))
    {
    
            cvtColor(frame, hsv, CV_RGB2HSV);
           
           Point lastPoint = Point(roi._centroid.x, roi._centroid.y);
        
           split(hsv, hsv_channels);
           h_image = hsv_channels[0];
           hueArray = h_image.data;
           step = h_image.step;
        
           camShift.meanshift(hueArray, step, &roi, histogram);
      
            roi.drawROI(&frame);
            writeFrame(frame);
     
    }//end while

    _outputVideo.release();
    free(histogram);
   
    return 0;
}
