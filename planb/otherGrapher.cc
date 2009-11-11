/*
 *  Sebastian Arcila Valenzuela
 *  2009
 */
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
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


struct Cubic
{
  float a,b,c ,d;
  Cubic ( ) { }
  Cubic(float A, float B, float C, float D){
    a = A;
    b = B;
    c = C;
    d = D;
  }


  /** evaluate cubic */
  float eval(float u) {
    return (((d*u) + c)*u + b)*u + a;
  }

};


struct polygon
{
  vector <float > X;
  vector <float > Y;
  polygon ( ) { }
  void addPoint ( float xx, float yy)
  {
    X.push_back ( xx ) ;
    Y.push_back ( yy ) ;
  }
};


vector<Cubic> calcular_cubicas(const int & n, const vector<float> & xx) {
  float gamma [n+1], delta [n+1], D [n+1];
  int i;
  gamma[0] = 1.0f/2.0f;
  for ( i = 1; i < n; i++) {
    gamma[i] = 1/(4-gamma[i-1]);
  }
  gamma[n] = 1/(2-gamma[n-1]);

  delta[0] = 3*(xx[1]-xx[0])*gamma[0];
  for ( i = 1; i < n; i++) {
    delta[i] = (3*(xx[i+1]-xx[i-1])-delta[i-1])*gamma[i];
  }
  delta[n] = (3*(xx[n]-xx[n-1])-delta[n-1])*gamma[n];

  D[n] = delta[n];
  for ( i = n-1; i >= 0; i--) {
    D[i] = delta[i] - gamma[i]*D[i+1];
  }
  vector<Cubic> C (n);
  for ( i = 0; i < n; i++) {
    C[i] = Cubic(xx[i], D[i], 3*(xx[i+1] - xx[i]) - 2*D[i] - D[i+1],
                     2*(xx[i] - xx[i+1]) + D[i] + D[i+1]);
  }
  return C;
}
polygon doit(){
  int STEPS = 12;
  polygon p ;
  if (x.size() > 2) {
    vector<Cubic> X = calcular_cubicas(x.size()-1, x);
    vector<Cubic> Y = calcular_cubicas(y.size()-1, y);
    p.addPoint(X[0].eval(0),Y[0].eval(0));
    for (int i = 0; i < X.size(); i++) {
      for (int j = 1; j <= STEPS; j++) {
        float u = j / (float) STEPS;
        p.addPoint(X[i].eval(u),Y[i].eval(u));
      }
    }
  }
  return p;
}


void draw_spline()
{
  polygon p = doit();
  //DEBUG
  /*
  for(int i=0;i<p.X.size();++i)
    {
      printf("%f %f ; ",p.X[i],p.Y[i]);
    }
  puts("");
  puts("------");
  */
  glBegin(GL_LINES);
  {
    for(int i=0;i<p.X.size();++i)
      {
        glVertex2f(p.X[i],p.Y[i]);
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
  if(button == GLUT_LEFT_BUTTON)
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

