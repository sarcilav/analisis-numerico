#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <algorithm>
#define LISTA_CONVEX 1
#define LISTA_PUNTOS 2
#define RADIO_CENTRO 4
//#define PI 3.14159265
using namespace std;



typedef long long CoordType;


struct Point
{
  CoordType x,y;
  Point(){}
  Point(CoordType a, CoordType b): x(a), y(b){}
  bool operator < (const Point &p) const
  {
    return x<p.x || (x==p.x && y<p.y);
  }
  bool operator == (const Point &p) const
  {
    return x==p.x && y==p.y;
  }
};

// 2D cross product. Returns a positive value if OAB makes a
// counter-clockwise turn, negative for clockwise turn, and zero
// if the points are collinear.
CoordType cross(const Point &O, const Point &A, const Point &B){
  return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

static GLfloat angle_= 0.0, angle2_, fAspect;
static float xcam_=0.0f,ycam_=4.0f,zcam_=20.0f;
static float lx_=0.0f,ly_=0.0f,lz_=0.0f;
static GLfloat radio = 1.0;

vector<Point> puntos_;
vector<Point> convexHull_;

// Returns a list of points on the convex hull in
// counter-clockwise order. Note: the last point in the returned
// list is the same as the first one.
vector<Point> convexHull(vector<Point> P)
{
  int n = P.size(), k = 0;
  vector<Point> H(2*n);
  // Sort points lexicographically
  sort(P.begin(), P.end());
  // Build lower hull
  for (int i = 0; i < n; i++) 
    {
      while (k >= 2 && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
      H[k++] = P[i];
    }
  // Build upper hull
  for(int i = n-2, t = k+1; i >= 0; i--) 
    {
      while (k >= t && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
      H[k++] = P[i];
    }
  H.resize(k);
  return H;
}


void parametrosDeVisualizacion()
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(angle2_, fAspect, 0.1, 500);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(xcam_, ycam_, zcam_, 
	     lx_, ly_, lz_,
	   0.0f,1.0f,0.0f);
}

void plano()
{
  glColor3f(0.0,0.3, 0.0);
  glBegin(GL_QUADS);		      
  glVertex3f(-50.0,-50.0, 0.0);
  glVertex3f(-50.0,50.0, 0.0);
  glVertex3f(50.0,50.0, 0.0); 
  glVertex3f(50.0,-50.0, 0.0); 
  glEnd();
  glCallList(LISTA_PUNTOS);
  glCallList(LISTA_CONVEX);
}

vector<Point> pedir_puntos()
{
  vector<Point> puntosEntrada;
  int n = 0;
  printf("ingrese el numero de puntos que desea interpolar:\n");
  scanf("%d", &n);
  for(int i = 0; i < n; i++){
    CoordType p, q;
    scanf("%lld %lld", &p, &q);
    Point s(p, q);
    puntosEntrada.push_back(s);
    printf("leido (%lld, %lld) \n", s.x, s.y);
  }
  return puntosEntrada;
}


void movimientoCam(float direction) {
  xcam_ = xcam_ + direction*(lx_)*0.5;
  zcam_ = zcam_ + direction*(lz_)*0.5;
  glLoadIdentity();
  gluLookAt(xcam_, ycam_, zcam_, 
	    xcam_ + lx_,ycam_ + ly_,zcam_ + lz_,
	    0.0f,1.0f,0.0f);
}

void orientacionCam(float angle) 
{
  lx_ = sin(angle);
  lz_ = -cos(angle);
  glLoadIdentity();
  gluLookAt(xcam_, ycam_, zcam_, 
	    xcam_ + lx_,ycam_ + ly_,zcam_ + lz_,
	    0.0f,1.0f,0.0f);
}

void inputKeyMoverseMundo(int key, int x, int y) {
  switch (key) {
  case GLUT_KEY_LEFT : 
    angle_ -= 0.1f;
    orientacionCam(angle_);	  	  	  	  	  	  	  	       
    break;	  
  case GLUT_KEY_RIGHT :
    angle_ += 0.1f;
    orientacionCam(angle_);     
    break;
  case GLUT_KEY_UP : 
    movimientoCam(1);
    break;
  case GLUT_KEY_DOWN : 
    movimientoCam(-1);
    break; 
  default:
   cout << "Special Key: " << key << endl;
  }
  glutPostRedisplay();

}


void reshape(int w, int h)
{
  if (h == 0) h =1;
  glViewport (0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  fAspect = (GLfloat) w/(GLfloat) h;
  parametrosDeVisualizacion();
}

void init(void) 
{
  glClearColor (0.0, 0.0, 0.0, 0.0);
  glShadeModel(GL_FLAT);
  angle2_ = 45;
  glEnable(GL_MAP1_VERTEX_3);
  GLint i;
  GLfloat coseno, seno;
  vector<Point> entrada = pedir_puntos();
  vector<Point> convex = convexHull(entrada);
  // visualizacion convex_hull
  glNewList(LISTA_CONVEX, GL_COMPILE);
  glColor3f(1.0f, 1.0f, 1.0f);
  glLineWidth(3.);
  glBegin(GL_LINE_LOOP);
  for(i=0;i<convex.size();i++)
    {
      glVertex3f((float)(convex[i].x),(float)(convex[i].y), 0.0);
    }
  glEnd();
  glEndList();
  //visualización puntos
  glNewList(LISTA_PUNTOS, GL_COMPILE);
  glColor3f(1.0f, 1.0f, 0.0f);
  glPointSize(25.);
  glBegin(GL_POINTS);
  for(i=0;i<entrada.size();i++)
    {
      glVertex3f((float)(entrada[i].x),(float)(entrada[i].y), 0.0);
    }
  glEnd();
  glEndList();
  
}

//displaaaaaaaaaaaaaayyyyyyyyyyyyyyy

void display(void){

 glClear(GL_COLOR_BUFFER_BIT);
 plano();
 glutSwapBuffers();

}



int main(int argc, char** argv){
  
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize (600, 600); 
  glutInitWindowPosition (400, 20);
  glutCreateWindow("Visualizador convex hull");
  init ();
  glutDisplayFunc(display); 
  glutReshapeFunc(reshape); 
  glutSpecialFunc(inputKeyMoverseMundo);
  // iniciarVisualizacion();
  glutMainLoop();
  return 0;
 }
