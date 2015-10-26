//
//  MyKalman.h
//  perifoveal
//
//  Created by Anette von Kapri on 10/25/15.
//  Copyright 2015 __MyCompanyName__. All rights reserved.
//

#ifndef perifoveal_MyKalman_h
#define perifoveal_MyKalman_h

///kalman stuff
#include <opencv2/opencv.hpp>
#include <opencv2/video/tracking.hpp>

#include <vector>



class MyKalman 
{
    
public:
    ///sets up all the OpenCV kalman filter things
    MyKalman();
    ~MyKalman();
    
    ///calculates the filtered point based on the kalman filter history
    cv::Point calc_kalman(const int x_pixel, const int y_pixel);

protected:
    int pos_x, pos_y;
    
    std::vector<cv::Point> posv, kalmanv;
    
    cv::KalmanFilter KF;
    cv::Mat_<float> measurement;
    
};

#endif
