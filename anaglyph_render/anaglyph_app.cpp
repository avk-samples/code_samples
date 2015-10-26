// @author: Anette von Kapri

#include <GL/glu.h>
#include <GL/glut.h>

#include "glh_linear.h"
#include "anaglyph_app.h"

AnaglyphApp::AnaglyphApp()
{
	m_camera_rot = glh::matrix4();
	m_camera_trans= glh::vec3(0.0f, 0.0f, 1.25f);

	m_eye_offset = 0.03f;
	m_button_state = -1;
	
	m_model = TEAPOT;
	m_draw_mode = GL_FILL;
	m_eye_separation = RED_CYAN;

	m_animation = true;
	m_rotation = 20.0f;
	m_lighting = true;
}

AnaglyphApp::~AnaglyphApp()
{

}

void AnaglyphApp::setup()
{
	m_last_time = glutGet(GLUT_ELAPSED_TIME)/1000.0f;

	gl_setup();
}


void AnaglyphApp::draw_scene()
{
	glPushMatrix();
		glTranslatef(m_camera_trans[0], m_camera_trans[1], m_camera_trans[2]);
		glMultMatrixf(m_camera_rot.get_value());

		glColor3f(1.0f,1.0f,1.0f);

		if(m_model == TEAPOT)
		{
			draw_teapot();
		}
		else if(m_model == BOX)
		{
			draw_box();
		}
		else //if(m_model == OCTAHEDRON)
		{
			draw_octahedron();
		}
	glPopMatrix();
}

void AnaglyphApp::display_func()
{
	// compute frame time
	const float time = glutGet(GLUT_ELAPSED_TIME)/1000.0f;
	const float frame_time = time - m_last_time;
	m_last_time = time;
	
	//animation: rotate model around y-axis
	if(m_animation && (m_button_state == -1))
	{
		const float rotation = frame_time*m_rotation;
		const glh::vec3 y_axis(0.0f, 1.0f, 0.0f);
		const glh::quaternion q_rot( y_axis, glh::to_radians(rotation));
		glh::matrix4 rot;
		q_rot.get_value(rot);

		m_camera_rot.mult_left(rot);
	}
	
	m_rotation_lag-= frame_time*5.0f;
	if(m_rotation_lag > 0.0f)
	{
		glh::quaternion quat(m_rot_axis, glh::to_radians(m_rotation_lag));

		glh::matrix4 rot;
		quat.get_value(rot);

		m_camera_rot = m_camera_rot.mult_left(rot);
	}
	
	m_translation_lag -= 0.1f*frame_time;
	if(m_translation_lag > 0.0f)
	{
		m_camera_trans += m_trans_vec*m_translation_lag;
	}

	// GL_COLOR_BUFFER_BIT stores GL_DRAW_BUFFER setting
	// GL_COLOR_BUFFER_BIT stores color mode write masks
	glPushAttrib(GL_COLOR_BUFFER_BIT);

	// clear color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// set transformations in modelview matrix to identiy
	glLoadIdentity();

	if(m_eye_separation == MONO)
	{
		glPushMatrix();
			gluLookAt(0.0f, 0.0f, 5.0f,
					0.0f, 0.0f,-1.0f,
					0.0f, 1.0f, 0.0f);
			draw_scene();
		glPopMatrix();
	}
	else
	{
		//left eye
		if(m_eye_separation == RED_GREEN)
		{
			glColorMask(GL_TRUE,GL_FALSE,GL_FALSE,GL_TRUE);
		}
		else //if(m_eye_separation == RED_CYAN)
		{
			glColorMask(GL_TRUE,GL_FALSE,GL_FALSE,GL_TRUE);
		}
		glPushMatrix();
			gluLookAt(-m_eye_offset, 0.0f, 5.0f,
					0.0f,0.0f,-1.0f,
					0.0f,1.0f,0.0f);
					
			
			draw_scene();
			
		glPopMatrix();

		// make sure all OpenGL draw calls are finished before proceeding to right eye
		glFlush();

		//right eye
		glClear(GL_DEPTH_BUFFER_BIT);
		if(m_eye_separation == RED_GREEN)
		{
			glColorMask(GL_FALSE,GL_TRUE,GL_FALSE,GL_TRUE);
		}
		else //if(m_eye_separation == RED_CYAN)
		{
			glColorMask(GL_FALSE,GL_TRUE,GL_TRUE,GL_TRUE);
		}
		glPushMatrix();
			gluLookAt(m_eye_offset, 0.0f, 5.0f,
			0.0f,0.0f,-1.0f,
			0.0f,1.0f,0.0f);
		draw_scene();
		glPopMatrix();
	}

	glFlush();


	glPopAttrib(); // GL_COLOR_BUFFER_BIT

	// swap front and back buffers
	glutSwapBuffers();
}

void AnaglyphApp::mouse_func(int button, int state, int x, int y)
{
	m_last_mouse_pos[0] = x;
	m_last_mouse_pos[1] = y;

	if (state == GLUT_DOWN)
		m_button_state = button;
	else if (state == GLUT_UP)
		m_button_state = -1;

	//translate in z-dir if wheel is used
	if ( button == 3)//GLUT_WHEEL_UP)
		m_camera_trans[2] -= 0.1f;
	else if ( button == 4)//GLUT_WHEEL_DOWN)
		m_camera_trans[2] += 0.1f;

}

void AnaglyphApp::motion_func(int x, int y)
{
	//left button: rotate
	if(m_button_state == GLUT_LEFT_BUTTON)
	{
		const float dx = x - m_last_mouse_pos[0];
		const float dy = y - m_last_mouse_pos[1];
		
		m_rot_axis = glh::vec3(dy/5.0f, dx/5.0f, 0.0f);
		const float length = m_rot_axis.length();
		if((length > 4.0f) || (m_rotation_lag < length))
		{
			m_rotation_lag = length;
			glh::quaternion quat(m_rot_axis, glh::to_radians(m_rotation_lag));

			glh::matrix4 rot;
			quat.get_value(rot);

			m_camera_rot = m_camera_rot.mult_left(rot);
		}
	}

	//middle button: translate in x- and y-dir
	else if(m_button_state == GLUT_MIDDLE_BUTTON)
	{
		const float dx = x - m_last_mouse_pos[0];
		const float dy = y - m_last_mouse_pos[1];

		glh::vec3 trans_vec(dx/250.0f, -dy/250.0f, 0.0f);
		
		const float trans_vec_length = trans_vec.length();
		if((trans_vec_length > 0.025f) || (m_translation_lag < trans_vec_length))
		{
		  m_trans_vec = trans_vec;
		  m_translation_lag = m_trans_vec.length();

		  m_camera_trans += m_trans_vec;
		  m_trans_vec.normalize();
		}
	}

	m_last_mouse_pos[0] = x;
	m_last_mouse_pos[1] = y;
}

void AnaglyphApp::set_draw_mode(int draw_mode)
{
	if(draw_mode == WIREFRAME)
	{
		m_draw_mode = GL_LINE;
	}
	else //if(draw_mode == SOLID)
	{
		m_draw_mode = GL_FILL;
	}
	glPolygonMode(GL_FRONT_AND_BACK, m_draw_mode);
}


void AnaglyphApp::toggle_lighting()
{
	m_lighting = !m_lighting;
	if(m_lighting)
		glEnable(GL_LIGHTING);
	else
		glDisable(GL_LIGHTING);
}


void AnaglyphApp::gl_setup()
{
	// define the color we use to clearscreen
	 glClearColor(0.0,0.0,0.0,0.0);

	 // use z buffer
	 glEnable(GL_DEPTH_TEST);

	 // no smoothing of lines, points and polygons for better eye separation
	 glDisable(GL_LINE_SMOOTH);
	 glDisable(GL_POINT_SMOOTH);
	 glDisable(GL_POLYGON_SMOOTH);
	 // no dithering of colors for better eye separation
	 glDisable(GL_DITHER);

	 // light setting
	 glEnable(GL_LIGHTING);
	 glEnable(GL_LIGHT0);
	 const glh::vec4 ambient(0.6f,0.6f,0.6f,1.0f);
	 glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambient);

	 // interior of objects should be visible
	 glDisable(GL_CULL_FACE);

	 glPolygonMode(GL_FRONT_AND_BACK,m_draw_mode);
}

void AnaglyphApp::draw_teapot()
{
	glutSolidTeapot(1.0f);
}

void AnaglyphApp::draw_box()
{
	glutSolidCube(1.0f);
}

void AnaglyphApp::draw_octahedron()
{
	glutSolidOctahedron();
}

