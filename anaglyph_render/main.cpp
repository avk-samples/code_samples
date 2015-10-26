#include <GL/glut.h>
#include <iostream>

#include "glh_linear.h"

#include "anaglyph_app.h"

// screen size
const int width = 1024;
const int height = 576;

// glut callback function
void display_func();
void reshape_func(int w, int h);
void idle_func();
void keyboard_func(unsigned char key, int x, int y);
void mouse_func(int button, int state, int x, int y);
void motion_func(int x, int y);

// create right click context menu
void createGLUTMenus();

// shared pointer of main application
AnaglyphAppPtr anaglyph_app;

int main(int argc, char **argv)
{
	//init glut
	glutInit(&argc, argv);
	glutInitWindowSize(width, height);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	glutCreateWindow("Anaglyph Renderer");

	// create shared pointer of application object
	anaglyph_app.reset(new AnaglyphApp());
	anaglyph_app->setup();

	// set glut callback functions
	glutDisplayFunc(display_func);
	glutReshapeFunc(reshape_func);
	glutIdleFunc(idle_func);
	glutKeyboardFunc(keyboard_func);
	glutMouseFunc(mouse_func);
	glutMotionFunc(motion_func);

	// context menu
	createGLUTMenus();
	
	// print out some information about program control
	std::cout << "Usage\n"
	    << "Left mouse button rotates object.\n"
	    << "Middle mouse button translates object.\n"
            << "Right mouse button opens context menu for some settings.\n"
            << "Key \'q\' quits application\n";
	
	// start event loop
	glutMainLoop();
}

/// function is called whenever the window size changes
/// @param w screen width
/// @param h screen height
void reshape_func(int w, int h)
{
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;
	if(w <= 0)
		w = 1;

	const float aspect_ratio = 1.0* w / h;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set the correct perspective.
	const float fovy = 45.0f; //< opening angle of 45 degree
	const float near_plane = 0.1f; //< near clipping plane
	const float far_plane = 1000.0f; //< far clipping plane
	gluPerspective( fovy, aspect_ratio, near_plane, far_plane );
	glMatrixMode(GL_MODELVIEW);
	// Set the viewport to be the entire window
		glViewport(0, 0, w, h);
	glLoadIdentity();
}


void display_func()
{
	anaglyph_app->display_func();
}


void idle_func()
{
  // trigger redraw
  glutPostRedisplay();
}

void keyboard_func(unsigned char key, int x, int y)
{
	if ((key == 27) || (key == 'q'))
		exit(0);
}

void mouse_func(int button, int state, int x, int y)
{
	  anaglyph_app->mouse_func(button, state, x, y);
}


void motion_func(int x, int y)
{
	anaglyph_app->motion_func(x, y);
}


enum MENU_ENTRIES {MENU_ANIMATION = 0, MENU_LIGHTING};
void handle_main_menu(int selection)
{
	switch(selection)
	{
	case MENU_ANIMATION:
		anaglyph_app->toggle_animation();
	break;
	case MENU_LIGHTING:
		anaglyph_app->toggle_lighting();
	break;
	default:
	break;
	}

}

void handle_separation_menu(int selection)
{
	anaglyph_app->set_separation_mode(selection);
}

void handle_draw_mode_menu(int selection)
{
	anaglyph_app->set_draw_mode(selection);
}

void handle_model_menu(int selection)
{
	anaglyph_app->set_model(selection);
}

void createGLUTMenus()
{
	  int draw_mode_menu = glutCreateMenu(handle_draw_mode_menu);
	  glutAddMenuEntry("Wireframe",AnaglyphApp::WIREFRAME);
	  glutAddMenuEntry("Solid",AnaglyphApp::SOLID);

	  int model_menu = glutCreateMenu(handle_model_menu);
	  glutAddMenuEntry("Teapot",AnaglyphApp::TEAPOT);
	  glutAddMenuEntry("Box",AnaglyphApp::BOX);
	  glutAddMenuEntry("Octahedron",AnaglyphApp::OCTAHEDRON);

	  int separation_menu = glutCreateMenu(handle_separation_menu);
	  glutAddMenuEntry("Red/Green",AnaglyphApp::RED_GREEN);
	  glutAddMenuEntry("Red/Cyan",AnaglyphApp::RED_CYAN);
	  glutAddMenuEntry("Mono",AnaglyphApp::MONO);

	  glutCreateMenu(handle_main_menu);
	  glutAddSubMenu("Model Type",model_menu);
	  glutAddSubMenu("Draw Mode",draw_mode_menu);
	  glutAddSubMenu("Eye Separation Filter",separation_menu);
	  glutAddMenuEntry("Toggle Animation",MENU_ANIMATION);
	  glutAddMenuEntry("Toggle Lighting",MENU_LIGHTING);
	  glutAttachMenu(GLUT_RIGHT_BUTTON);
}

