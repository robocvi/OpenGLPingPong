//Punto extra: Ping Pong

//#include <windows.h> //the windows include file, required by all windows applications
#include <GLUT/glut.h> //the glut file for windows operations
                     // it also includes gl.h and glu.h for the openGL library calls
#include <math.h>

#define PI 3.1415926535898 

const double paddleWidth = 5.0;
const double paddleHeight = 20.0;
double xpos, ypos, ydir, xdir;         // x and y position for house to be drawn
double sx, sy, squash;          // xy scale factors
double rot, rdir;             // rotation 
int SPEED = 50;        // speed of timer call back in msecs
GLfloat T1[16] = {1.,0.,0.,0.,\
                  0.,1.,0.,0.,\
                  0.,0.,1.,0.,\
                  0.,0.,0.,1.};
GLfloat S[16] = {1.,0.,0.,0.,\
                 0.,1.,0.,0.,\
                 0.,0.,1.,0.,\
                 0.,0.,0.,1.};
GLfloat T[16] = {1.,0.,0.,0.,\
                 0., 1., 0., 0.,\
                 0.,0.,1.,0.,\
                 0.,0.,0.,1.};



#define PI 3.1415926535898 
GLint circle_points = 100; 
void MyCircle2f(GLfloat centerx, GLfloat centery, GLfloat radius){
  GLint i;
  GLdouble angle;
  glBegin(GL_POLYGON); 
  for (i = 0; i < circle_points; i++) {    
    angle = 2*PI*i/circle_points; 
    glVertex2f(centerx+radius*cos(angle), centery+radius*sin(angle)); 
  } 
  glEnd();
}

GLfloat RadiusOfBall = 3.;
void draw_ball() {
  glColor3f(0.6,0.3,0.);
  MyCircle2f(0.,0.,RadiusOfBall);
  
}

void draw_paddle(double x, double y) {
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(x - paddleWidth / 2, y - paddleHeight / 2);
    glVertex2f(x + paddleWidth / 2, y - paddleHeight / 2);
    glVertex2f(x + paddleWidth / 2, y + paddleHeight / 2);
    glVertex2f(x - paddleWidth / 2, y + paddleHeight / 2);
    glEnd();
}

double paddleY = 60.0;

void Display(void)
{
    // Swap the buffers
    glutSwapBuffers();

    // Clear all pixels with the specified clear color
    glClear(GL_COLOR_BUFFER_BIT);

    xpos += xdir * 1.02;
    ypos += ydir * 1.02;

    if (ypos >= 120.0 - RadiusOfBall || ypos <= RadiusOfBall)
    {
        ydir = -ydir;
    }

    if (xpos >= 160.0 - RadiusOfBall || xpos <= RadiusOfBall)
    {
        xdir = -xdir;
    }

    glLoadIdentity();

    glPushMatrix();
    glTranslatef(xpos, ypos, 0.);
    glTranslatef(0., -RadiusOfBall, 0.);
    glScalef(sx, sy, 1.);
    glTranslatef(0., RadiusOfBall, 0.);

    draw_ball();
    glPopMatrix();

    draw_paddle(20., paddleY); // Blanco

    draw_paddle(140., paddleY); // Blanco

    glutPostRedisplay();
}


void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();

   gluOrtho2D(0.0, 160.0, 0.0, 120.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity ();

}


void init(void){
  glClearColor(0.0,0.8,0.0,1.0);
  xpos = 80.; ypos = RadiusOfBall; xdir = 1; ydir = 1;
  sx = 1.; sy = 1.; squash = 0.9;
  rot = 0; 
}


int main(int argc, char* argv[])
{
  glutInit( & argc, argv );
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize (320, 240);   
  glutCreateWindow("Bouncing Ball");
  init();
  glutDisplayFunc(Display);
  glutReshapeFunc(reshape);
  glutMainLoop();

  return 1;
}