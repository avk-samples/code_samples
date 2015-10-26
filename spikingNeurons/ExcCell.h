/*============================================================================*/
/*       1         2         3         4         5         6         7        */
/*3456789012345678901234567890123456789012345678901234567890123456789012345678*/
/*============================================================================*/
/*                                             .                              */
/*                                               RRRR WW  WW   WTTTTTTHH  HH  */
/*                                               RR RR WW WWW  W  TT  HH  HH  */
/*      FileName :  ExcCell.h			 		 RRRR   WWWWWWWW  TT  HHHHHH  */
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
// $Id: ExcCell.h  $

#ifndef EXCCELL_H_
#define EXCCELL_H_

#include <boost/shared_ptr.hpp>

#include "Cell.h"

/**
 * @class ExcCell
 * \brief excitatoric cell,
 * is drawn blue and has a pyramidal form
 */
class ExcCell : public Cell
{
public:
	ExcCell(const glh::vec3f &position, const float scale_factor);
	virtual ~ExcCell();


	/// draw blue and pyramidal
	virtual void draw(GLuint display_list, bool dark, GLuint shader);

protected:

};
typedef boost::shared_ptr<ExcCell> ExcCellPtr;


// EXCCELL_H_
#endif
