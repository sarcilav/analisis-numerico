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
  x.push_back(-0.5),  x.push_back(-0.4),x.push_back(-0.3), x.push_back(0.2), x.push_back(0.7),x.push_back(0.1);
  y.push_back(0.5),  y.push_back(-0.4),y.push_back(0.3), y.push_back(0.2), y.push_back(0.7),y.push_back(0.4);
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
  float w [n+1], v[n+1], yy[n+1], D [n+1];
  float z, F, G, H;
  int k;
  w[1] = v[1] = z = 1.0f/4.0f;
  yy[0] = z * 3 * (xx[1] - xx[n]);
  H = 4;
  F = 3 * (xx[0] - xx[n-1]);
  G = 1;
  for ( k = 1; k < n; k++) {
    v[k+1] = z = 1/(4 - v[k]);
    w[k+1] = -z * w[k];
    yy[k] = z * (3*(xx[k+1]-xx[k-1]) - yy[k-1]);
    H = H - G * w[k];
    F = F - G * yy[k-1];
    G = -v[k] * G;
  }
  H = H - (G+1)*(v[n]+w[n]);
  yy[n] = F - (G+1)*yy[n-1];

  D[n] = yy[n]/H;
  D[n-1] = yy[n-1] - (v[n]+w[n])*D[n]; /* This equation is WRONG! in my copy of Spath */
  for ( k = n-2; k >= 0; k--) {
    D[k] = yy[k] - v[k+1]*D[k+1] - w[k+1]*D[n];
  }


  /* now compute the coefficients of the cubics */
  vector<Cubic> C (n+1);
  for ( k = 0; k < n; k++) {
    C[k] =  Cubic(xx[k], D[k], 3*(xx[k+1] - xx[k]) - 2*D[k] - D[k+1],
                     2*(xx[k] - xx[k+1]) + D[k] + D[k+1]);
  }

  C[n] = Cubic(xx[n], D[n], 3*(xx[0] - xx[n]) - 2*D[n] - D[0],
               2*(xx[n] - xx[0]) + D[n] + D[0]);
  return C;
}


polygon doit(){
  int STEPS = 20;
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

int I=0;
void draw_spline()
{
  polygon p = doit();
  glBegin(GL_LINES);
  {

    int N = p.X.size();
    for(int i=0;i<I;++i)
      {
        glVertex2f(p.X[i],p.Y[i]);
        glVertex2f(p.X[(i+1)%N],p.Y[(i+1)%N]);
      }
    I = (I+1)%N;
  }
  glEnd();
}

void display()
{

  GLfloat ma[] = { 0.7, 0.7, 0.7, 1.0 };
  GLfloat md[] = { 0.1, 0.5, 0.8, 1.0 };
  GLfloat ms[] = { 0.2, 0.9, 0.3, 1.0 };
  GLfloat ls[] = { 3.0 };

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


int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize (1000, 600);
  glutCreateWindow(argv[0]);

  init();

  glutDisplayFunc(&display);

  glutIdleFunc(display);


  glutMainLoop();

  return 0;
}

