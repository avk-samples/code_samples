/*============================================================================*/
/*       1         2         3         4         5         6         7        */
/*3456789012345678901234567890123456789012345678901234567890123456789012345678*/
/*============================================================================*/
/*                                             .                              */
/*                                               RRRR WW  WW   WTTTTTTHH  HH  */
/*                                               RR RR WW WWW  W  TT  HH  HH  */
/*      FileName :  InhCell.cpp					 RRRR   WWWWWWWW  TT  HHHHHH  */
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
// $Id: InhCell.cpp  $

#include <GL/gl.h>
#include <GL/glu.h>

#include "InhCell.h"




InhCell::InhCell(const glh::vec3f &position, const float scale_factor)
: Cell(position, scale_factor)
{
}

InhCell::~InhCell()
{}



void InhCell::draw(GLuint display_list, bool dark, GLuint shader)
{
    if(m_fire_rate > 0.008f)
    {
        //draw a red sphere
        glPushMatrix();
        glTranslatef(m_position[0],m_position[1],m_position[2]);
        
        //hard-coded colors: would be better as class variables
        float high_pot = 0.05f;
        
        if(dark) glColor3f((218.0f + m_fire_rate*(255.0f-218.0f)/high_pot)/255.0f,
                           (144.0f - m_fire_rate*144.0f/high_pot)/255.0f,
                           1.0f);
        else glColor3f(1.0f,
                       (133.0f - m_fire_rate*133.0f/high_pot)/255.0f,
                       (180.0f - m_fire_rate*180.0f/high_pot)/255.0f);
        
        
        const float scale = m_fire_rate*m_scale_factor*0.8f*30.0f;
        glScalef(scale, scale, scale);
        
        
        glCallList(display_list);
        glPopMatrix();
    }
    //else dont draw anything...
    
}

