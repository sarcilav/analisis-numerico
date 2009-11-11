// This code was created by Jeff Molofee '99 (ported to Linux/GLUT by Richard Campbell '99)
// used as basic template
#ifdef __APPLE__
#include<GLUT/GLUT.h>
#include<OpenGL/OpenGL.h>
#else
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glut.h>
#endif
#include <unistd.h>     // Header file for sleeping.
#include <cstdlib>

/* ascii code for the escape key */
#define ESCAPE 27

/* The number of our GLUT window */
int window; 

/*window size and position */
int width=800,height=600,initx=40,inity=40;

/* A general OpenGL initialization function.  Sets all of the initial parameters. */
void InitGL(int Width, int Height)	        // We call this right after our OpenGL window is created.
{
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);		// This Will Clear The Background Color To Black
  glClearDepth(1.0);				// Enables Clearing Of The Depth Buffer
  glDepthFunc(GL_LESS);				// The Type Of Depth Test To Do
  glEnable(GL_DEPTH_TEST);			// Enables Depth Testing
  glShadeModel(GL_SMOOTH);			// Enables Smooth Color Shading

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();				// Reset The Projection Matrix

  gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);	// Calculate The Aspect Ratio Of The Window

  glMatrixMode(GL_MODELVIEW);
}

void drawPoints(double x[],double y[])
{
  glColor3f(1,1,1);
  ///////////
  int N=(sizeof(x)/sizeof(x[0]));
  glBegin(GL_POLYGON);  
  for(int i=0;i<N;++i){
    glVertex2f(x[i],y[i]);
  }
  glEnd();
  //  glTranslate(0.0,0.0,2.0);
  ///////////
}

/* The function called when our window is resized (which shouldn't happen, because we're fullscreen) */
void ReSizeGLScene(int Width, int Height)
{
  if (Height==0)				// Prevent A Divide By Zero If The Window Is Too Small
    Height=1;

  glViewport(0, 0, Width, Height);		// Reset The Current Viewport And Perspective Transformation

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);
  glMatrixMode(GL_MODELVIEW);
}

/* The main drawing function. */
void DrawGLScene()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear The Screen And The Depth Buffer
  glLoadIdentity();				// Reset The View
  double x[]={0,1,2,3,2,1,0};
  double y[]={1,1,1,3,3,3,3};
  drawPoints(x,y);
  // since this is double buffered, swap the buffers to display what just got drawn.
  glutSwapBuffers();
}

/* The function called whenever a key is pressed. */
void keyPressed(unsigned char key, int x, int y) 
{
  /* avoid thrashing this procedure */
  usleep(100);

  /* If escape is pressed, kill everything. */
  if (key == ESCAPE) 
    { 
      /* shut down our window */
      glutDestroyWindow(window); 
	
      /* exit the program...normal termination. */
      exit(0);               
    }
}

int main(int argc, char **argv) 
{  
  /* Initialize GLUT state - glut will take any command line arguments that pertain to it or 
     X Windows - look at its documentation at http://reality.sgi.com/mjk/spec3/spec3.html */  
  glutInit(&argc, argv);  

  /* Select type of Display mode:   
     Double buffer 
     RGBA color
     Alpha components supported 
     Depth buffer */  
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);  

  /* get a w x h window */
  glutInitWindowSize(width, height);  

  /* the window starts at the upper left corner of the screen */
  glutInitWindowPosition(initx, inity);  

  /* Open a window */  
  window = glutCreateWindow("myTemplate based on Jeff Molofee's GL Code Tutorial ... NeHe '99");  

  /* Register the function to do all our OpenGL drawing. */
  glutDisplayFunc(&DrawGLScene);  

  /* Go fullscreen.  This is as soon as possible. */
  //  glutFullScreen();

  /* Even if there are no events, redraw our gl scene. */
  glutIdleFunc(&DrawGLScene);

  /* Register the function called when our window is resized. */
  glutReshapeFunc(&ReSizeGLScene);

  /* Register the function called when the keyboard is pressed. */
  glutKeyboardFunc(&keyPressed);

  /* Initialize our window. */
  InitGL(width, height);
  
  /* Start Event Processing Engine */  
  glutMainLoop();  

  return 1;
}
