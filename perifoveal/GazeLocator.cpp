//
//  GazeLocator.cpp
//  perifoveal
//
//  Created by Anette von Kapri on 10/25/15.
//  Copyright 2015 __MyCompanyName__. All rights reserved.
//

#include <iostream>

#include "GazeLocator.h"

GazeLocator::GazeLocator(const ScreenInfo &screen_info)
: screen(screen_info)
{
    calc_norm();
}
GazeLocator::~GazeLocator()
{
    
}



void GazeLocator::calc_norm()
{
    //calculate normal vectors for monitor
    glh::vec3 v_1_4 = screen.corner_4 - screen.corner_1;
    glh::vec3 v_1_2 = screen.corner_2 - screen.corner_1;
    norm = v_1_2.cross(v_1_4);
    
    plane = glh::plane(norm, screen.corner_1);
}

glh::vec3 GazeLocator::intersection(const glh::vec3 &_pos, const glh::vec3 &_dir)
{
    //ray defined as r(t) = t*head_dir + head_pos;
    
    const float t = -norm.dot(_pos-screen.corner_1)/(norm.dot(_dir));
    glh::vec3 res(t * _dir[0] + _pos[0],
                  t * _dir[1] + _pos[1],
                  t * _dir[2] + _pos[2]);
    
    return res;
}

bool GazeLocator::in_rectangle(const glh::vec3 &intersection)
{
    //     v1
    //   1--->4
    //   |\   |
    // v2| v  |
    //   v    |
    //   2----3
    //
    
    
    const glh::vec3 c = screen.corner_1;
    const glh::vec3 v1 = screen.corner_4 - screen.corner_1;
    const glh::vec3 v2 = screen.corner_2 - screen.corner_1;
    const glh::vec3 v = intersection - screen.corner_1;
    
    const float dot_vv1 = v.dot(v1);   // projected length of v on v1 * length of v1
    const float dot_v1v1 = v1.dot(v1); // length of v1 squared
    const float dot_vv2 = v.dot(v2);   // projected length of v on v2 * length of v2
    const float dot_v2v2 = v2.dot(v2); //length of v2 squared
    
    if( (0<= dot_vv1) && (dot_vv1 <= dot_v1v1) && (0<= dot_vv2) && (dot_vv2 <= dot_v2v2) )
    {
        return true;
    }
    else return false;
}


glh::vec2i GazeLocator::calc_focus_pixel(const glh::vec3 &_pos, const glh::vec3 &_dir, bool return_filtered = true)
{
    const glh::vec3 intersect = intersection(_pos, _dir);
    const bool within_monitor = in_rectangle(intersect);
    
    glh::vec2i pixel_pos;
    if (within_monitor)
    {
        //calculate pixel pos
        const glh::vec3 v1 = intersect - screen.corner_2;
        const glh::vec3 v2 = intersect - screen.corner_1;
        
        const float x_cm = (v1.cross(intersect - screen.corner_1)).length() 
                            / ((screen.corner_1 - screen.corner_2).length());
        const float y_cm = (v2.cross(intersect - screen.corner_4)).length()
                            / ((screen.corner_4 - screen.corner_1).length());
        
        pixel_pos[0] = (int) (x_cm/screen.monitor_cm_width * screen.monitor_pixel_width);
        pixel_pos[1] = (int) (y_cm/screen.monitor_cm_height * screen.monitor_pixel_height);   
    }
    else
    {
        pixel_pos[0] = 0;
        pixel_pos[1] = 0;
    }
    
    cv::Point point = filter.calc_kalman(pixel_pos[0], pixel_pos[1]);
    
    focus_pixel_raw = glh::vec2i(pixel_pos[0], pixel_pos[1]);
    focus_pixel_filtered = glh::vec2i(point.x, point.y);
    
    if(return_filtered) return focus_pixel_filtered;
    else return focus_pixel_raw;
    
}

