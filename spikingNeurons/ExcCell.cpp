/*============================================================================*/
/*       1         2         3         4         5         6         7        */
/*3456789012345678901234567890123456789012345678901234567890123456789012345678*/
/*============================================================================*/
/*                                             .                              */
/*                                               RRRR WW  WW   WTTTTTTHH  HH  */
/*                                               RR RR WW WWW  W  TT  HH  HH  */
/*      FileName :  ExcCell.cpp					 RRRR   WWWWWWWW  TT  HHHHHH  */
/*                                               RR RR   WWW WWW  TT  HH  HH  */
/*      Module   :  					         RR  R    WW  WW  TT  HH  HH  */
/*                                                                            */
/*      Project  :  ViSTA                        Rheinisch-Westfaelische      */
/*                                               Technische Hochschule Aachen */
/*      Purpose  :                                                            */
/*                                                                            */
/*                                                 Copyright (c)  1998-2010   */
/*                                                 by  RWTH-Aachen, Germany   */
/*                                                 All rights reserved.       */
/*                                             .                              */
/*============================================================================*/
// $Id: ExcCell.cpp  $


#include <GL/gl.h>
#include <GL/glu.h>

#include "ExcCell.h"



ExcCell::ExcCell(const glh::vec3f &position, const float scale_factor)
    : Cell(position, scale_factor)
{
}
ExcCell::~ExcCell()
{
}



void ExcCell::draw(GLuint display_list, bool dark, GLuint shader)
{
    if(m_fire_rate > 0.008f)
    {
        //draw a blue pyramid
        glPushMatrix();
        glTranslatef(m_position[0],m_position[1],m_position[2]);
        
        
        //hard-coded colors: would be better as class variables
        
        float high_pot = 0.05f;
        
        if(dark) glColor3f((150.0f - m_fire_rate*150.0f/high_pot)/255.0f,
                           (200.0f - m_fire_rate*200.0f/high_pot)/255.0f,
                           1.0f);
        else glColor3f((150.0f - m_fire_rate*150.0f/high_pot)/255.0f,
                       (253.0f - m_fire_rate*(253.0f-100.0f)/high_pot)/255.0f,
                       (200.0f - m_fire_rate*(200.0f-15.0f)/high_pot)/255.0f);
        
        const float scale = m_fire_rate*m_scale_factor*30.0f;
        glScalef(scale, scale, scale); 
        
        glCallList(display_list);
        glPopMatrix();
    }
}


