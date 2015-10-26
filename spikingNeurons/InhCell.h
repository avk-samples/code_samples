/*============================================================================*/
/*       1         2         3         4         5         6         7        */
/*3456789012345678901234567890123456789012345678901234567890123456789012345678*/
/*============================================================================*/
/*                                             .                              */
/*                                               RRRR WW  WW   WTTTTTTHH  HH  */
/*                                               RR RR WW WWW  W  TT  HH  HH  */
/*      FileName :  InhCell.h					 RRRR   WWWWWWWW  TT  HHHHHH  */
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
// $Id: InhCell.h  $


#ifndef INHCELL_H_
#define INHCELL_H_

#include <boost/shared_ptr.hpp>

#include "Cell.h"


/**
 * @class InhCell
 * \brief inhibitoric cell,
 * is drawn red and has a circular form
 */
class InhCell : public Cell
{
public:
	InhCell(const glh::vec3f &position, const float scale_factor);
	virtual ~InhCell();


	/// is drawn red and circular
    virtual void draw(GLuint display_list, bool dark, GLuint shader);




protected:

};
typedef boost::shared_ptr<InhCell> InhCellPtr;


// INHCELL_H_
#endif
