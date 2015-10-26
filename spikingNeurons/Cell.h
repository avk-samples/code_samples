/*============================================================================*/
/*       1         2         3         4         5         6         7        */
/*3456789012345678901234567890123456789012345678901234567890123456789012345678*/
/*============================================================================*/
/*                                             .                              */
/*                                               RRRR WW  WW   WTTTTTTHH  HH  */
/*                                               RR RR WW WWW  W  TT  HH  HH  */
/*      FileName :  Cell.h						 RRRR   WWWWWWWW  TT  HHHHHH  */
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
// $Id: Cell.h  $

#ifndef CELL_H_
#define CELL_H_


#include <vector>
#include <boost/shared_ptr.hpp>

/// for display_list
#include <GL/glu.h>

#include "glh_linear.h"


/**
 * \brief
 * @class Cell
 * either excitatoric or inhibitoric (is drawn differently)
 */
class Cell
{
public:
	Cell(const glh::vec3f &position, const float scale_factor);
	virtual ~Cell();
    
    
    /// implemented in derived classes to define drawing behavior
    virtual void draw(GLuint display_list, bool dark, GLuint shader) = 0;
    
    
    /// update online estimation of m_fire_rate with exponential kernel
    /// add one_tauth if spiking
    /// otherwise exponential decay in time
	void update(const double sim_time, double last_sim_time, const float one_tauth);
    
	/// push_back spike in #m_spikes
	void add_spike(const float spike);
    
    void set_scale(const float scale_factor);
    
    void reset_spike_index();
    
    ///calculate the fire_rate at end_time
    ///if you know the fire_rate at a different time
    ///if no skiking occurs between start_time and end_time, fire_rate decays
    ///if spiking occurs fire_rate increases by one_tauth
    float calc_fire_rate(const float one_tauth, const float fire_rate_start,
                         const float start_time, const float end_time);
    
    ///calculate fire_rate at time
    float calc_fire_rate(const float one_tauth, const double time);
    
protected:
	glh::vec3f m_position; ///< position in space, relative to layer
	std::vector<float> m_spikes; ///< time moments for spikes of cells
	bool m_spiking; ///< tells if Cell is currently spiking
    
    float m_scale_factor; ///< for drawing
    
    float m_fire_rate; ///< membrane_potential calculated with exponential kernel
    
    int m_spike_index; ///< to fasten up the calc_fire_rate, save latest index
    
};
typedef boost::shared_ptr<Cell> CellPtr;


// CELL_H_
#endif
