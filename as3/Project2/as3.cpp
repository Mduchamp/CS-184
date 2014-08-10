/*#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include "Patch.h";

#define PI 3.14159265

using namespace std;

class Viewport {
  public:
    int w, h; // width and height
};


//****************************************************
// Global Variables
//****************************************************
Viewport    viewport;
Vector center;

void myReshape(int w, int h) {
  viewport.w = w;
  viewport.h = h;
  center = Vector(viewport.w / 2.0 , viewport.h / 2.0 , min(viewport.w, viewport.h) / 3.0);

  glViewport(0,0,viewport.w,viewport.h); // sets the rectangle that will be the window
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();                // loading the identity matrix for the screen

  //----------- setting the projection -------------------------
  // glOrtho sets left, right, bottom, top, zNear, zFar of the chord system


  // glOrtho(-1, 1 + (w-400)/200.0 , -1 -(h-400)/200.0, 1, 1, -1); // resize type = add
  // glOrtho(-w/400.0, w/400.0, -h/400.0, h/400.0, 1, -1); // resize type = center

  glOrtho(-1, 1, -1, 1, 1, -1);    // resize type = stretch

  //------------------------------------------------------------
}

void initScene(){
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Clear to black, fully transparent
  myReshape(viewport.w,viewport.h);
}

void myDisplay() {
  glClear(GL_COLOR_BUFFER_BIT);                // clear the color buffer (sets everything to black)
  glMatrixMode(GL_MODELVIEW);                  // indicate we are specifying camera transformations
  glLoadIdentity();                            // make sure transformation is "zero'd"
  glFlush();
  glutSwapBuffers();                           // swap buffers (we earlier set double buffer)
}

void myFrameMove() {
	MSG msg = {0};
	if(GetMessage(&msg, NULL, 0, 0) != 0) {
		if(msg.message == WM_HOTKEY) {
			if(WM_HOTKEY == 1) {
				glViewport(0,0,viewport.w,viewport.h);
			}
		}
	}
  /*Sleep(10);                                   //give ~10ms back to OS (so as not to waste the CPU)
  glutPostRedisplay(); // forces glut to call the display function (myDisplay())*/
/*}

int main(int argc, char *argv[]) {
  //This initializes glut
  glutInit(&argc, argv);

  //This tells glut to use a double-buffered window with red, green, and blue channels 
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

  // Initalize theviewport size
  viewport.w = 400;
  viewport.h = 400;

  //The size and position of the window
  glutInitWindowSize(viewport.w, viewport.h);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Assignment 3");

  initScene();                                 // quick function to set up scene

  glutDisplayFunc(myDisplay);                  // function to run when its time to draw something
  glutReshapeFunc(myReshape);                  // function to run when the window gets resized
  glutIdleFunc(myFrameMove);                   // function to run when not handling any other task
  glutMainLoop();                              // infinite loop that will keep drawing and resizing and whatever else

  return 0;
}*/