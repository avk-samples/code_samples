/*============================================================================*/
/*       1         2         3         4         5         6         7        */
/*3456789012345678901234567890123456789012345678901234567890123456789012345678*/
/*============================================================================*/
/*                                             .                              */
/*                                               RRRR WW  WW   WTTTTTTHH  HH  */
/*                                               RR RR WW WWW  W  TT  HH  HH  */
/*      FileName :  Cell.cpp					 RRRR   WWWWWWWW  TT  HHHHHH  */
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
// $Id: Cell.cpp  $


#include "Cell.h"



Cell::Cell(const glh::vec3f &position, const float scale_factor)
: m_position(position), m_scale_factor(scale_factor), m_spiking(false)
, m_fire_rate(0.0f), m_spike_index(0)
{}

Cell::~Cell()
{}



void Cell::update(const double sim_time, double last_sim_time, const float one_tauth)
{
    ///@assumption: time is going forward
    //if loop starts new, reset m_fire_rate to 0
    if((sim_time - last_sim_time) < 0.0)
    {
        m_fire_rate = 0.0f;
        ///@todo: should be first sim_time: here it is 0.0
        last_sim_time = 0.0f;
        m_spike_index = 0;
    }
    
    m_fire_rate = calc_fire_rate(one_tauth, m_fire_rate, last_sim_time, sim_time);
}

void Cell::add_spike(const float spike)
{
	m_spikes.push_back(spike);
}

void Cell::set_scale(const float scale_factor)
{
    m_scale_factor = scale_factor;
}

void Cell::reset_spike_index()
{
    m_spike_index = 0;
}

float Cell::calc_fire_rate(const float one_tauth, const float fire_rate_start,
                           const float start_time, const float end_time)
{
    float fire_rate = fire_rate_start;
    float start_time_changeable = start_time;
    
    const int spikes_size = m_spikes.size();
    int i;
    
    
	for(i=m_spike_index; i<spikes_size; i++)
	{
        
        if(m_spikes[i] > start_time_changeable)
        {
            //spike occurred between last_sim_time and sim_time
            if(m_spikes[i] <= end_time)
            {
                //multiply with 1000.0 because spike and last_sim_time is saved in secs not msecs
                fire_rate *= powf(1.0f - one_tauth, (m_spikes[i] - start_time_changeable)); //decay
                fire_rate += one_tauth;
                
                start_time_changeable = m_spikes[i];
            }
            else break; // no additional spike
        }
	}
    
    m_spike_index = i;
    
	//decay since last spike
	fire_rate *= powf(1.0f - one_tauth, (end_time - start_time_changeable)); //decay
    
	return fire_rate;
}

float Cell::calc_fire_rate(const float one_tauth, const double time)
{
    m_spike_index = 0;
    return calc_fire_rate(one_tauth, 0.0f, 0.0, time);
}

