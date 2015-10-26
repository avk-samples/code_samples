//
//  MyKalman.cpp
//  perifoveal
//
//  Created by Anette von Kapri on 10/25/15.
//  Copyright 2015 __MyCompanyName__. All rights reserved.
//

#include <iostream>

#include "MyKalman.h"


MyKalman::MyKalman()
{
    pos_x = -1;
    pos_y = -1;
    
    
    //init kalman filter
    KF = cv::KalmanFilter(6, 2, 0);
    cv::Mat_<float> state(6, 1);
    cv::Mat processNoise(6, 1, CV_32F);
    
    measurement = cv::Mat_<float>(2,1); 
    measurement.setTo(cv::Scalar(0));
    
    KF.statePre.at<float>(0) = pos_x;
    KF.statePre.at<float>(1) = pos_y;
    KF.statePre.at<float>(2) = 0;
    KF.statePre.at<float>(3) = 0;
    KF.statePre.at<float>(4) = 0;
    KF.statePre.at<float>(5) = 0;
    KF.transitionMatrix = *(cv::Mat_<float>(6, 6) << 1,0,1,0,0.75,0, 0,1,0,1,0,0.75, 0,0,1,0,0.75,0, 0,0,0,0.75,0,0.75, 0,0,0,0,0.75,0, 0,0,0,0,0,0.75);
    KF.measurementMatrix = *(cv::Mat_<float>(2, 6) << 1,0,1,0,0.5,0, 0,1,0,1,0,0.5);
    
    setIdentity(KF.measurementMatrix);
    setIdentity(KF.processNoiseCov, cv::Scalar::all(1e-4));
    setIdentity(KF.measurementNoiseCov, cv::Scalar::all(1e-1));
    setIdentity(KF.errorCovPost, cv::Scalar::all(.1));
    
    posv.clear();
    kalmanv.clear();
}

MyKalman::~MyKalman()
{
    posv.clear();
    kalmanv.clear();
}


cv::Point MyKalman::calc_kalman(const int x_pixel, const int y_pixel)
{
    cv::Point statePt;
    if((x_pixel == 0) && (y_pixel==0))
    {
        //delete all the history
        posv.clear();
        kalmanv.clear();
        
        statePt = cv::Point(0,0);
    }
    else
    {
        
        pos_x = x_pixel;
        pos_y = y_pixel;
        
        cv::Mat prediction = KF.predict();
        cv::Point predictPt(prediction.at<float>(0),prediction.at<float>(1));
        
        measurement(0) = pos_x;
        measurement(1) = pos_y;
        
        cv::Point measPt(measurement(0),measurement(1));
        posv.push_back(measPt);
        
        cv::Mat estimated = KF.correct(measurement);
        statePt= cv::Point(estimated.at<float>(0),estimated.at<float>(1));
        kalmanv.push_back(statePt);
    }
    
    return statePt;
}