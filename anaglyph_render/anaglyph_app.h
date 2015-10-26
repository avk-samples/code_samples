/// @author: Anette von Kapri

#ifndef ANAGLYPH_APP_H_
#define ANAGLYPH_APP_H_

// shared pointer
#include <boost/shared_ptr.hpp>

// vector and matrix math
#include "glh_linear.h"


/// @class AnaglyphApp
/// class for rendering OpenGL with anaglyph stereo
class AnaglyphApp
{
public:
	/// available models
	enum MODEL_TYPES { TEAPOT = 0, BOX,  OCTAHEDRON}; 
	enum DRAW_MODES { WIREFRAME = 0, SOLID};
	enum SEPARATION_MODES {RED_GREEN = 0, RED_CYAN, MONO};

	/// constructor
	AnaglyphApp(); 
	///destructor
	virtual ~AnaglyphApp(); 

	/// setup
	void setup(); 

	/// is called once per frame
	void display_func();
	
	/// callback function for mouse button actions
	/// @param button : which buttons are pressed or released
	/// @param state : up or down
	/// @param x : x position of mouse
	/// @param y : y position of mouse
	void mouse_func(int button, int state, int x, int y);
	
	/// callback function for mouse movements
	/// @param x : x position of mouse
	/// @param y : y position of mouse
	void motion_func(int x, int y);
	

	/// choose between different left/right eye separation filters
	/// @param eye_separation: choose from SEPARATION_MODES
	void set_separation_mode(int eye_separation){ m_eye_separation = eye_separation; };
	
	/// set draw mode which is used for scene rendering
	/// @param draw_mode: choose from DRAW_MODES
	void set_draw_mode(int draw_mode);
	
	/// set model which is used for scene rendering
	/// @param model: choose from MODEL_TYPES
	void set_model(int model) { m_model = model; };

	/// enable/disable rotation animation
	void toggle_animation(){ m_animation = !m_animation; };
	
	/// enable/disable lighting
	void toggle_lighting();

protected:
	void gl_setup();

	void draw_scene();
	void draw_teapot();
	void draw_box();
	void draw_octahedron();

	float m_eye_offset; //< offset between left and right eye in stereo mode
	float m_last_time;

	glh::matrix4 m_camera_rot;
	glh::vec3 m_camera_trans;
	glh::vec2 m_last_mouse_pos;

	int m_button_state;

	int m_model;
	GLenum  m_draw_mode;
	int m_eye_separation;

	bool m_animation;
	float m_rotation; //< degrees of rotation per second
	bool m_lighting;
	
	glh::vec3 m_rot_axis;
	float m_rotation_lag; 
	glh::vec3 m_trans_vec;
	float m_translation_lag;
};
typedef boost::shared_ptr<AnaglyphApp> AnaglyphAppPtr;
// ANAGLYPH_APP_H_
#endif
