//Example2_4.cpp : A bouncing ball 

//#include <windows.h> //the windows include file, required by all windows applications
#include <GLUT/glut.h> //the glut file for windows operations
                     // it also includes gl.h and glu.h for the openGL library calls
#include <math.h>

#define PI 3.1415926535898 

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
// Draw the ball, centered at the origin
void draw_ball() {
  glColor3f(0.6,0.3,0.);
  MyCircle2f(0.,0.,RadiusOfBall);
  
}

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

    T[12] = xpos;
    T[13] = ypos;
    glLoadMatrixf(T);

    // Translate ball back to center
    T1[13] = -RadiusOfBall;
    glMultMatrixf(T1);

    // Scale the ball about its bottom
    S[0] = sx;
    S[5] = sy;
    glMultMatrixf(S);

    // Translate ball up so bottom is at the origin
    T1[13] = RadiusOfBall;
    glMultMatrixf(T1);

    // Draw the ball
    draw_ball();

    // Post redisplay to keep animating
    glutPostRedisplay();
}


void reshape (int w, int h)
{
   // on reshape and on startup, keep the viewport to be the entire size of the window
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();

   // keep our logical coordinate system constant
   gluOrtho2D(0.0, 160.0, 0.0, 120.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity ();

}


void init(void){
  //set the clear color to be white
  glClearColor(0.0,0.8,0.0,1.0);
  // initial position set to 0,0
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