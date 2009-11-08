#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <algorithm>
#define LISTA_PUNTOS 1
#define LISTA_SPLINE 2
#define STEP 4

using namespace std;



typedef double CoordType;


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


vector<Point> spline(vector<Point> entrada)
{

  int n = entrada.size();
  vector<double> h, b, u, v;
  double *z;
  double *A, *B, *C, *D; //coeficientes de la función de spline resultante
  vector<Point> splined; //spline resultante
  z = new double[n+1]; //arreglo de resultados de la segunda derivada
  A = new double[n];
  B = new double[n];
  C = new double[n];
  D = new double[n];
  int i; //interador
  //creo la matriz tridiagonal que expresa la ecuación de la segunda derivada
  for(i = 0; i < n; ++i)
    {
    h.push_back(entrada[i+1].x-entrada[i].x);
    b.push_back(6*((entrada[i+1].y-entrada[i].y)/h[i]));
    }
  u.push_back(2*(h[0]+h[1]));
  v.push_back(b[1]-b[0]);
  //soluciono por gauss para vectores
  for(i = 1; i < n; ++i)
    {
      u.push_back( (2*(h[i] + h[i-1]) - (h[i-1]*h[i-1]))/u[i-1] );
      v.push_back((b[i]-b[i-1]-h[i-1]*v[i-1])/u[i-1]);       
    }
  // retorno el valor despejando gauss
  z[n]=0.0; //porque es una spline natural
  for(i = n-1; i >0; --i)
    z[i] = (v[i]-h[i]*z[i+1])/u[i];

  z[0] = 0.0; //porque es una spline natural

  //utilizo los resultados de la segunda derivada para conseguir los valores de los coeficientes
  for(i = 0; i < n; ++i)
    {
      A[i] = ((1/6)*h[i])* (z[i+1] - z[i]);
      B[i] = z[i] /2;
      C[i] = ((entrada[i+1].y - entrada[i].y)/h[i]) -(h[i]*z[i]/3) - (h[i]*z[i]/3) ;
    }

  //calculo ahora los valores de la spline
  //a partir del valor de los coeficientes con el método de horner
  //para estabilizar los cálculos
  for(i = 0; i < n; ++i)
    {
      double x = entrada[i].x;
      double sum = entrada[1].x/STEP;
      for(int j = 0; j < 4; ++j){
	double resultado = entrada[i].y + (x-entrada[i].x)*(C[i] + (x - entrada[i].x)*(B[i] + (x - entrada[i].x)*A[i]));
	Point p(x, resultado);
	splined.push_back(p);
	printf("entrada: %lf\t salida: %lf\n", x, resultado);
	x+= sum;
      }

    }
  return splined;
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
  glCallList(LISTA_SPLINE);
  glCallList(LISTA_PUNTOS);
}

vector<Point> pedir_puntos()
{
  vector<Point> puntosEntrada;
  int n = 0;
  printf("ingrese el numero de puntos que desea interpolar:\n");
  scanf("%d", &n);
  for(int i = 0; i < n; i++){
    CoordType p, q;
    scanf("%lf %lf", &p, &q);
    Point s(p, q);
    puntosEntrada.push_back(s);
    printf("leido (%lf, %lf) \n", s.x, s.y);
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
  vector<Point> splined = spline(entrada);
  // visualizacion convex_hull
  glNewList(LISTA_SPLINE, GL_COMPILE);
  glColor3f(1.0f, 1.0f, 1.0f);
  glLineWidth(3.);
  glBegin(GL_LINE_STRIP);
  for(i=0;i<splined.size();i++)
    {
      glVertex3f((splined[i].x),(splined[i].y), 0.0);
    }
  glEnd();
  glEndList();
  //visualización puntos
  glNewList(LISTA_PUNTOS, GL_COMPILE);
  glColor3f(1.0f, 1.0f, 0.0f);
  glPointSize(5.);
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
