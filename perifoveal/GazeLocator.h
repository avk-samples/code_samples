//
//  GazeLocator.h
//  perifoveal
//
//  Created by Anette von Kapri on 10/25/15.
//  Copyright 2015 __MyCompanyName__. All rights reserved.
//

#ifndef perifoveal_GazeLocator_h
#define perifoveal_GazeLocator_h

// for cross product calc
// plane intersection etc.
// I chose this library because it is header only and its API closely
// resembles GLSL shader code
#include "glh_linear.h"

#include "MyKalman.h"



struct ScreenInfo {
    // measured corner points of each monitor in [cm]
    // relative to Kinect sensor
    // 1---4 
    // | 1 | 
    // 2---3 
    glh::vec3 corner_1;
    glh::vec3 corner_2;
    glh::vec3 corner_3;
    glh::vec3 corner_4;
    
    int monitor_pixel_width;
    int monitor_pixel_height;
    float monitor_cm_width;
    float monitor_cm_height;
};


class GazeLocator {
  
public:
    GazeLocator(const ScreenInfo &screen_info);
    ~GazeLocator();
    
    /// calculate the pixel position on screen where the user is looking at
    /// _pos is the user head position
    /// _dir is the user head direction
    /// return {0, 0} if user is not focusing on monitor area
    glh::vec2i calc_focus_pixel(const glh::vec3 &_pos, const glh::vec3 &_dir, bool return_filtered = true);
    
    const glh::vec2i& get_last_focus_pixel_raw() const;
    const glh::vec2i& get_last_focus_pixel_filtered() const;
    
    
private:
    ///calculate normal vector for monitor
    void calc_norm();
    ///calculate the interaction point of the plane and a ray
    glh::vec3 intersection(const glh::vec3 &_pos, const glh::vec3 &_dir);
    ///is the intersection point on the plane within the monitor area
    bool in_rectangle(const glh::vec3 &intersection);
    
    glh::vec2i focus_pixel_raw;
    glh::vec2i focus_pixel_filtered;
    
    
    ScreenInfo screen;
    MyKalman filter;
    
    glh::vec3 norm;
    glh::plane plane;
    
};


#endif
