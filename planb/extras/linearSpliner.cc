/*
 *  Sebastian Arcila Valenzuela
 *  2009
 */
#ifdef __APPLE__                                                                                                       
#include<GLUT/GLUT.h>                                                                                                  
#include<OpenGL/OpenGL.h>                                                                                              
#else                                                                                                                  
#include <GL/gl.h>                                                                                                     
#include <GL/glu.h>                                                                                                    
#include <GL/glut.h>                                                                                                  
#endif
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <vector>
using namespace std;

vector <float> x;
vector <float> y;
void init()
{
  GLfloat a[] = { 0.0, 0.0, 0.0, 1.0 };
  GLfloat d[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat s[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat p[] = { 0.0, 3.0, 2.0, 0.0 };
  GLfloat lma[] = { 0.4, 0.4, 0.4, 1.0 };
  GLfloat lv[] = { 0.0 };

  glClearColor(0.0, 0.1, 0.1, 0.0);
  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_SMOOTH);

  glLightfv(GL_LIGHT0, GL_AMBIENT, a);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, d);
  glLightfv(GL_LIGHT0, GL_POSITION, p);
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lma);
  glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, lv);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

}

void draw_spline()
{

  glBegin(GL_LINES);
  {
    int N = x.size();
    for(int i=0;i<N;++i)
      {
        glVertex2f(x[i],y[i]);
        if(i!=N-1)
        glVertex2f(x[(i+1)%N],y[(i+1)%N]);
      }
  }
  glEnd();
}

void display()
{

  GLfloat ma[] = { 0.7, 0.7, 0.7, 1.0 };
  GLfloat md[] = { 0.1, 0.5, 0.8, 1.0 };
  GLfloat ms[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat ls[] = { 5.0 };

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glPushMatrix();
  {
    glMaterialfv(GL_FRONT, GL_AMBIENT, ma);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, md);
    glMaterialfv(GL_FRONT, GL_SPECULAR, ms);
    glMaterialfv(GL_FRONT, GL_SHININESS, ls);
    draw_spline();
  }
  glPopMatrix();
  glutSwapBuffers();
}
void mouse_click(int button, int state, int X, int Y)
{
  if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN  )
    {

      Y = 300 - Y -1;
      X =X -500;
      float xx = X;
      float yy = Y;
      xx/=500;
      yy/=300;
      x.push_back(xx);
      y.push_back(yy);
    }
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize (1000, 600);
  glutCreateWindow(argv[0]);

  init();
  glutMouseFunc(mouse_click);

  glutDisplayFunc(&display);

  glutIdleFunc(display);


  glutMainLoop();

  return 0;
}

